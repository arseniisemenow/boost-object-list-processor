#pragma once

#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <map>

namespace http = boost::beast::http;

class Context {

 public:
    // Constructor
    Context(const http::request<http::string_body> &req,
            http::response<http::string_body> &res)
        : request_(req), response_(res) {}

    const http::request<http::string_body> &GetRequest();
    http::response<http::string_body> &GetResponse();

    void SetResponseResult(http::status status, const std::string &body);
    std::string GetParam(const std::string &key) const;
    void SetParam(const std::string &key, const std::string &value);

 private:
    const http::request<http::string_body> &request_;
    http::response<http::string_body> &response_;
    std::map<std::string, std::string> params_;
};
