#pragma once

#include "context.hpp"
#include <boost/beast.hpp>
#include <functional>
#include <map>
#include <memory>
#include <regex>
#include <string>

namespace http = boost::beast::http;

class Router {

 public:
    void AddRoute(const http::verb method, const std::string &path_pattern,
                  std::function<void(Context &)> handler);
    bool Route(Context &ctx);
    void SetPrefix(const std::string &prefix);

 private:
    struct RouteInfo {
        http::verb method;
        std::string pathPattern;
        std::function<void(Context &)> handler;
    };
    std::vector<RouteInfo> routes_;
    std::string prefix_;

 private:
    static std::vector<std::string> SplitPath(const std::string &path);
};
