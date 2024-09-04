#ifndef OBJECT_SERIALIZER_HPP_
#define OBJECT_SERIALIZER_HPP_

#include "shared/include/models/object.hpp"
#include <nlohmann/json.hpp>

class ObjectSerializer {
 public:
    static nlohmann::json ToJson(const Object &object);
    static Object FromJson(const nlohmann::json &json);
    static nlohmann::json MetadataToJson(const Object::Metadata &metadata);
    static Object::Metadata JsonToMetadata(const nlohmann::json &json_metadata);

};
#endif// OBJECT_SERIALIZER_HPP_