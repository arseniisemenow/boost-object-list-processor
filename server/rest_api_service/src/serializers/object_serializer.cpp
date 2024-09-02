#include "../include/serializers/object_serializer.hpp"

nlohmann::json ObjectSerializer::ToJson(const Object &object) {
    nlohmann::json json;
    json["name"] = object.GetName();
    json["x"] = object.GetX();
    json["y"] = object.GetY();
    json["type"] = object.GetType();
    json["creation_time"] = object.GetCreationTime();
    return json;
}

Object ObjectSerializer::FromJson(const nlohmann::json &json) {
    auto name = json.at("name").get<std::string>();
    auto x = json.at("x").get<double>();
    auto y = json.at("y").get<double>();
    auto type = json.at("type").get<std::string>();
    return Object{name, x, y, type};
}
