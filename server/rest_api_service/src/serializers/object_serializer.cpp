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
    std::string name = obj.at("name").get<std::string>();
    double x = obj.at("x").get<double>();
    double y = obj.at("y").get<double>();
    std::string type = obj.at("type").get<std::string>();
    double creation_time = obj.at("creation_time").get<unsigned long>();
    return Object{name, x, y, type, creation_time};
}
