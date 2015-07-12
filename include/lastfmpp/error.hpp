/**************************************************************************
** Copyright (C) 2015 Christian Manning
**
** This software may be modified and distributed under the terms
** of the MIT license.  See the LICENSE file for details.
**************************************************************************/

#ifndef LASTFM_ERROR
#define LASTFM_ERROR

#include <system_error>

namespace lastfmpp {

enum class api_error {
    unknown_error = 1,
    invalid_service = 2,
    invalid_method = 3,
    auth_failed = 4,
    invalid_format = 5,
    invalid_params = 6,
    invalid_resource = 7,
    operation_failed = 8,
    invalid_session_key = 9,
    invalid_api_key = 10,
    service_offline = 11,
    subsribers_only = 12,
    invalid_method_signature = 13,
    unauthorized_token = 14,
    item_not_streamable = 15,
    service_unavailable = 16,
    login_required = 17,
    trail_expired = 18,
    not_enough_content = 20,
    not_enough_members = 21,
    not_enough_fans = 22,
    not_enough_neighbours = 23,
    no_peak_radio = 24,
    radio_not_found = 25,
    api_key_suspended = 26,
    request_deprecated = 27,
    rate_limit_exceeded = 29,
};

std::error_code make_error_code(api_error err);

struct api_exception : std::system_error {
    explicit api_exception(api_error);
};

} // namespace lastfm

namespace std {
template <> struct is_error_code_enum<lastfmpp::api_error> : public true_type {};
}

#endif // LASTFM_ERROR
