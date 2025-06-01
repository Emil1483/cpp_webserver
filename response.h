#pragma once

#include <string>
#include <map>
#include <string_view>

struct Response {
    std::string status;
    std::map<std::string, std::string> headers;
    std::string body;

    std::string toString() const;
};

namespace StatusCodes {
    // 1xx Informational
    inline const std::string continue_                       = "100 Continue";
    inline const std::string switching_protocols             = "101 Switching Protocols";
    inline const std::string processing                      = "102 Processing";
    inline const std::string early_hints                     = "103 Early Hints";

    // 2xx Success
    inline const std::string ok                              = "200 OK";
    inline const std::string created                         = "201 Created";
    inline const std::string accepted                        = "202 Accepted";
    inline const std::string non_authoritative_information   = "203 Non-Authoritative Information";
    inline const std::string no_content                      = "204 No Content";
    inline const std::string reset_content                   = "205 Reset Content";
    inline const std::string partial_content                 = "206 Partial Content";
    inline const std::string multi_status                    = "207 Multi-Status";
    inline const std::string already_reported                = "208 Already Reported";
    inline const std::string im_used                         = "226 IM Used";

    // 3xx Redirection
    inline const std::string multiple_choices                = "300 Multiple Choices";
    inline const std::string moved_permanently               = "301 Moved Permanently";
    inline const std::string found                           = "302 Found";
    inline const std::string see_other                       = "303 See Other";
    inline const std::string not_modified                    = "304 Not Modified";
    inline const std::string use_proxy                       = "305 Use Proxy";
    inline const std::string unused                          = "306 (Unused)";
    inline const std::string temporary_redirect              = "307 Temporary Redirect";
    inline const std::string permanent_redirect              = "308 Permanent Redirect";

    // 4xx Client Errors
    inline const std::string bad_request                     = "400 Bad Request";
    inline const std::string unauthorized                    = "401 Unauthorized";
    inline const std::string payment_required                = "402 Payment Required";
    inline const std::string forbidden                       = "403 Forbidden";
    inline const std::string not_found                       = "404 Not Found";
    inline const std::string method_not_allowed              = "405 Method Not Allowed";
    inline const std::string not_acceptable                  = "406 Not Acceptable";
    inline const std::string proxy_authentication_required   = "407 Proxy Authentication Required";
    inline const std::string request_timeout                 = "408 Request Timeout";
    inline const std::string conflict                        = "409 Conflict";
    inline const std::string gone                            = "410 Gone";
    inline const std::string length_required                 = "411 Length Required";
    inline const std::string precondition_failed             = "412 Precondition Failed";
    inline const std::string payload_too_large               = "413 Payload Too Large";
    inline const std::string uri_too_long                    = "414 URI Too Long";
    inline const std::string unsupported_media_type          = "415 Unsupported Media Type";
    inline const std::string range_not_satisfiable           = "416 Range Not Satisfiable";
    inline const std::string expectation_failed              = "417 Expectation Failed";
    inline const std::string im_a_teapot                     = "418 I'm a teapot";
    inline const std::string misdirected_request             = "421 Misdirected Request";
    inline const std::string unprocessable_entity            = "422 Unprocessable Entity";
    inline const std::string locked                          = "423 Locked";
    inline const std::string failed_dependency               = "424 Failed Dependency";
    inline const std::string too_early                       = "425 Too Early";
    inline const std::string upgrade_required                = "426 Upgrade Required";
    inline const std::string precondition_required           = "428 Precondition Required";
    inline const std::string too_many_requests               = "429 Too Many Requests";
    inline const std::string request_header_fields_too_large = "431 Request Header Fields Too Large";
    inline const std::string unavailable_for_legal_reasons   = "451 Unavailable For Legal Reasons";

    // 5xx Server Errors
    inline const std::string internal_server_error           = "500 Internal Server Error";
    inline const std::string not_implemented                 = "501 Not Implemented";
    inline const std::string bad_gateway                     = "502 Bad Gateway";
    inline const std::string service_unavailable             = "503 Service Unavailable";
    inline const std::string gateway_timeout                 = "504 Gateway Timeout";
    inline const std::string http_version_not_supported      = "505 HTTP Version Not Supported";
    inline const std::string variant_also_negotiates         = "506 Variant Also Negotiates";
    inline const std::string insufficient_storage            = "507 Insufficient Storage";
    inline const std::string loop_detected                   = "508 Loop Detected";
    inline const std::string not_extended                    = "510 Not Extended";
    inline const std::string network_authentication_required = "511 Network Authentication Required";
}
