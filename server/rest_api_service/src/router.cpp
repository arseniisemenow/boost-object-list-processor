#include "../include/router.hpp"

void Router::AddRoute(http::verb method, const std::string &path_pattern,
                      std::function<void(Context &)> handler) {
    routes_.push_back({method, path_pattern, handler});
}

bool Router::Route(Context &ctx) {
  const auto &req = ctx.GetRequest();
  std::string target = std::string(req.target());

  // Adjust for any potential prefix_ mismatch or trailing slash
  if (!prefix_.empty() && target.find(prefix_) == 0) {
    target.erase(0, prefix_.size());
  }
  if (!target.empty() && target.back() == '/') {
    target.pop_back();
  }

  for (const auto &routeInfo : routes_) {
    if (req.method() != routeInfo.method)
      continue;

    std::vector<std::string> target_segments = SplitPath(target);
    std::vector<std::string> pattern_segments = SplitPath(routeInfo.pathPattern);

    if (target_segments.size() != pattern_segments.size())
      continue;

    bool match = true;
    for (size_t i = 0; i < pattern_segments.size(); ++i) {
      if (pattern_segments[i].front() == '{' && pattern_segments[i].back() == '}') {
        std::string paramName =
              pattern_segments[i].substr(1, pattern_segments[i].length() - 2);
        ctx.SetParam(paramName, target_segments[i]);
      } else if (pattern_segments[i] != target_segments[i]) {
        match = false;
        break;
      }
    }

    if (match) {
      routeInfo.handler(ctx);
      return true;
    }
  }
  return false; // There is no matching Route found
}

void Router::SetPrefix(const std::string &prefix) {
  this->prefix_ = prefix;
  // Ensure the prefix_ is correctly formatted
  if (!this->prefix_.empty() && this->prefix_.back() != '/') {
    this->prefix_ += '/';
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