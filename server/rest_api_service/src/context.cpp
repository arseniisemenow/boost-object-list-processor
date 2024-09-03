#include "../include/context.hpp"

const http::request<http::string_body> &Context::GetRequest() {
    return request_;
}

http::response<http::string_body> &Context::GetResponse() { return response_; }

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

// Parse and store query string parameters
void Context::SetQueryParams(const std::string &query_string) {
    size_t start = 0, end;
    while ((end = query_string.find('&', start)) != std::string::npos) {
        auto param = query_string.substr(start, end - start);
        size_t equal_pos = param.find('=');
        if (equal_pos != std::string::npos) {
            params_[param.substr(0, equal_pos)] = param.substr(equal_pos + 1);
        }
        start = end + 1;
    }
    // Last parameter (or the only one)
    auto param = query_string.substr(start);
    size_t equal_pos = param.find('=');
    if (equal_pos != std::string::npos) {
        params_[param.substr(0, equal_pos)] = param.substr(equal_pos + 1);
    }
}