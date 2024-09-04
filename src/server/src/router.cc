#include <utility>

#include "../include/router.hpp"

void Router::AddRoute(const http::verb method, const std::string &path_pattern,
                      std::function<void(Context &)> handler) {
    routes_.push_back({method, path_pattern, std::move(handler)});
}

bool Router::Route(Context &ctx) {
    const auto &req = ctx.GetRequest();
    std::string target = std::string(req.target());

    // Split the target into the path and the query string
    std::string::size_type query_pos = target.find('?');
    std::string path = target.substr(0, query_pos);  // Path without query string
    std::string query_string = (query_pos != std::string::npos) ? target.substr(query_pos + 1) : "";

    // Store query parameters in the context
    ctx.SetQueryParams(query_string);

    if (!prefix_.empty() && path.find(prefix_) == 0) {
        path.erase(0, prefix_.size());
    }
    if (!path.empty() && path.back() == '/') {
        path.pop_back();
    }

    for (const auto &route_info : routes_) {
        if (req.method() != route_info.method)
            continue;

        std::vector<std::string> target_segments = SplitPath(path);
        std::vector<std::string> pattern_segments = SplitPath(route_info.pathPattern);

        if (target_segments.size() != pattern_segments.size())
            continue;

        bool match = true;
        for (size_t i = 0; i < pattern_segments.size(); ++i) {
            if (pattern_segments[i].front() == '{' && pattern_segments[i].back() == '}') {
                std::string param_name =
                    pattern_segments[i].substr(1, pattern_segments[i].length() - 2);
                ctx.SetParam(param_name, target_segments[i]);
            } else if (pattern_segments[i] != target_segments[i]) {
                match = false;
                break;
            }
        }

        if (match) {
            route_info.handler(ctx);
            return true;
        }
    }
    return false; // No matching route found
}

void Router::SetPrefix(const std::string &prefix) {
    prefix_ = prefix;
    // Ensure the prefix_ is correctly formatted
    if (!prefix_.empty() && prefix_.back() != '/') {
        prefix_ += '/';
    }
}

std::vector<std::string> Router::SplitPath(const std::string &path) {
    std::vector<std::string> segments;
    size_t start = 0, end = 0;
    while ((end = path.find('/', start)) != std::string::npos) {
        if (end != start) {
            segments.push_back(path.substr(start, end - start));
        }
        start = end + 1;
    }
    if (start < path.size()) {
        segments.push_back(path.substr(start));
    }
    return segments;
}