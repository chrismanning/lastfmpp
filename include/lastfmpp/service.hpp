/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_SERVICE_HPP
#define LASTFM_SERVICE_HPP

#include <string>
#include <memory>
#include <vector>

#include <pplx/pplxtasks.h>

#include <jbson/document.hpp>

#include <lastfmpp/lastfmpp.hpp>
#include <lastfmpp/params.hpp>

namespace lastfmpp {

struct user;
struct track;
struct tag;
struct artist;

class LASTFM_EXPORT service {
  public:
    explicit service(std::string_view api_key, std::string_view shared_secret);

    ~service();

    std::string_view api_key() const;
    std::string_view shared_secret() const;

    pplx::task<jbson::document> get(std::string_view method, params_t params);

    template <typename TransformerT, typename ReturnT = std::result_of_t<TransformerT(jbson::document)>>
    pplx::task<ReturnT> get(std::string_view method, params_t params, TransformerT&& transform);

  private:
    struct impl;
    std::unique_ptr<impl> pimpl;
};

template <typename TransformerT, typename ReturnT>
pplx::task<ReturnT> service::get(std::string_view method, params_t params, TransformerT&& transform) {
    return get(method, std::move(params)).then(transform);
}

} // namespace lastfm

#endif // LASTFM_SERVICE_HPP
