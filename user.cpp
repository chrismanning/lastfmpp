/**************************************************************************
**  Copyright (C) 2012 Christian Manning
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/

#include <string>
#include <thread>
#include <mutex>
using std::mutex; using std::unique_lock; using std::lock_guard;
#include <functional>
namespace ph = std::placeholders;
#include <future>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
using namespace boost::property_tree::xml_parser;
#include <boost/lexical_cast.hpp>

#include <network/uri.hpp>

#include <melosic/common/thread.hpp>
#include <melosic/melin/logging.hpp>

#include "user.hpp"
#include "service.hpp"

namespace LastFM {

struct User::impl {
    impl(std::weak_ptr<Service> lastserv) : impl(lastserv, "", "") {}
    impl(std::weak_ptr<Service> lastserv, const std::string& username) : impl(lastserv, username, "") {}
    impl(std::weak_ptr<Service> lastserv, const std::string& username, const std::string& sessionKey)
        : lastserv(lastserv),
          username(username),
          sessionKey(sessionKey),
          logject(logging::keywords::channel = "LastFM::User")
    {}

private:
    bool getInfo_impl(std::shared_ptr<Service> lastserv) {
        if(!lastserv)
            return false;
        TRACE_LOG(logject) << "In getInfo";
        Method method = lastserv->prepareMethodCall("user.getInfo");
        method.addParameter()
                .addMember("user", username)
                .addMember("api_key", lastserv->apiKey());
        std::string reply(std::move(lastserv->postMethod(method)));
        if(reply.empty())
            return false;

        boost::property_tree::ptree ptree;
        std::stringstream ss(reply);
        read_xml(ss, ptree, trim_whitespace);

        if(ptree.get<std::string>("lfm.<xmlattr>.status", "failed") != "ok") {
            //TODO: handle error
            return false;
        }

        ptree = ptree.get_child("lfm.user");
        lock_guard<Mutex> l(mu);
        url = network::uri(ptree.get<std::string>("url"));
        gender = boost::lexical_cast<char>(ptree.get<std::string>("gender", ""));
        age = boost::lexical_cast<uint8_t>(ptree.get<std::string>("age", "0"));
        country = ptree.get<std::string>("country", "");
        registered = boost::lexical_cast<std::time_t>(ptree.get<std::string>("registered", "0"));

        return true;
    }

public:
    std::future<bool> getInfo() {
        std::shared_ptr<Service> lastserv = this->lastserv.lock();
        if(!lastserv) {
            std::promise<bool> p;
            p.set_value(false);
            return p.get_future();
        }
        return lastserv->getThreadManager()->enqueue(&impl::getInfo_impl, this, lastserv);
    }

private:
    bool authenticate_impl(std::shared_ptr<Service> lastserv) {
        return static_cast<bool>(lastserv);
    }

public:
    std::future<bool> authenticate() {
        std::shared_ptr<Service> lastserv = this->lastserv.lock();
        if(!lastserv) {
            std::promise<bool> p;
            p.set_value(false);
            return p.get_future();
        }
        return lastserv->getThreadManager()->enqueue(&impl::authenticate_impl, this, lastserv);
    }

    const std::string& getSessionKey() {
        lock_guard<Mutex> l(mu);
        return sessionKey;
    }
    void setSessionKey(const std::string& sk) {
        lock_guard<Mutex> l(mu);
        TRACE_LOG(logject) << "Set session key";
        sessionKey = sk;
    }

private:
    std::weak_ptr<Service> lastserv;
    std::string username;
    std::string sessionKey;
    Melosic::Logger::Logger logject;
    network::uri url;
    char gender = 0;
    uint8_t age = 0;
    std::string country;
    std::time_t registered;

    typedef mutex Mutex;
    Mutex mu;
};

User::User() : pimpl(nullptr) {}

User::User(std::weak_ptr<Service> lastserv, const std::string& username) : pimpl(new impl(lastserv, username)) {}

User::~User() {}

std::future<bool> User::getInfo() {
    return pimpl->getInfo();
}

User::User(std::weak_ptr<Service> lastserv, const std::string& username, const std::string& sessionKey)
    : pimpl(new impl(lastserv, username, sessionKey))
{}

User::User(User&& b) : pimpl(std::move(b.pimpl)) {}

User& User::operator=(User&& b) {
    pimpl = std::move(b.pimpl);
    return *this;
}

const std::string& User::getSessionKey() const {
    return pimpl->getSessionKey();
}

void User::setSessionKey(const std::string& sk) {
    pimpl->setSessionKey(sk);
}

User::operator bool() {
    return static_cast<bool>(pimpl);
}

}//namespace LastFM
