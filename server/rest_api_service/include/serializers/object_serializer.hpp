#ifndef OBJECT_SERIALIZER_HPP_
#define OBJECT_SERIALIZER_HPP_

#include "models/object.hpp"
#include <nlohmann/json.hpp>

class ObjectSerializer {
 public:
    static nlohmann::json ToJson(const Object &object);
    static Object FromJson(const nlohmann::json &obj);
};
#endif// OBJECT_SERIALIZER_HPP_