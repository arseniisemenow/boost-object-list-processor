#include "../include/context.hpp"

const http::request<http::string_body> &Context::GetRequest() {
    return request_;
}

http::response<http::string_body> &Context::GetResponse() { return response_; }

void Context::SetResponseResult(http::status status, const std::string &body) {
    response_.result(status);
    response_.body() = body;
    response_.prepare_payload();// Ensure headers like Content-Length are set
}

void Context::SetParam(const std::string &key, const std::string &value) {
    params_[key] = value;
}

std::string Context::GetParam(const std::string &key) const {
    auto it = params_.find(key);
    if (it != params_.end()) {
        return it->second;
    }
    return "";// or throw, based on how to handle missing params
}