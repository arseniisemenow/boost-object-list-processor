#include "../include/serializers/object_serializer.hpp"

nlohmann::json ObjectSerializer::ToJson(const Object &object) {
    nlohmann::json obj;
    obj["name"] = object.GetName();
    obj["x"] = object.GetX();
    obj["y"] = object.GetY();
    obj["type"] = object.GetType();
    obj["creation_time"] = object.GetCreationTime();
    return obj;
}

Object ObjectSerializer::FromJson(const nlohmann::json &obj) {
    auto name = obj.at("name").get<std::string>();
    auto x = obj.at("x").get<double>();
    auto y = obj.at("y").get<double>();
    auto type = obj.at("type").get<std::string>();
    return Object{name, x, y, type};
}
