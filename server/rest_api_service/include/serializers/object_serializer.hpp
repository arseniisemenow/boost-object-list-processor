#pragma once

#include "models/object.hpp"
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>

class ObjectSerializer {
 public:
    static nlohmann::json ToJson(const Object &object);
    static Object FromJson(const nlohmann::json &obj);
};
