#include "../include/serializers/object_serializer.hpp"

// Add this function to convert Metadata to JSON.
nlohmann::json ObjectSerializer::MetadataToJson(const Object::Metadata &metadata) {
    nlohmann::json json_metadata;

    for (const auto &[key, value] : metadata) {
        std::visit([&json_metadata, &key](auto &&arg) {
            json_metadata[key] = arg;
        },
                   value);
    }

    return json_metadata;
}

// Add this function to convert JSON to Metadata.
Object::Metadata ObjectSerializer::JsonToMetadata(const nlohmann::json &json_metadata) {
    Object::Metadata metadata;

    for (const auto &[key, value] : json_metadata.items()) {
        if (value.is_number_integer()) {
            metadata[key] = value.get<int>();
        } else if (value.is_number_float()) {
            metadata[key] = value.get<double>();
        } else if (value.is_string()) {
            metadata[key] = value.get<std::string>();
        } else {
            throw std::runtime_error("Unsupported metadata type in JSON.");
        }
    }

    return metadata;
}

nlohmann::json ObjectSerializer::ToJson(const Object &object) {
    nlohmann::json json;
    json["name"] = object.GetName();
    json["x"] = object.GetX();
    json["y"] = object.GetY();
    json["type"] = object.GetType();
    json["creation_time"] = Object::TimeTToString(object.GetCreationTime());
    json["metadata"] = MetadataToJson(object.GetMetadata());// Serialize metadata
    return json;
}

Object ObjectSerializer::FromJson(const nlohmann::json &json) {
    Object object{};
    auto name = json.at("name").get<std::string>();
    auto x = json.at("x").get<double>();
    auto y = json.at("y").get<double>();
    auto type = json.at("type").get<std::string>();

    object.SetName(name);
    object.SetX(x);
    object.SetY(y);
    object.SetType(type);

    auto metadata = JsonToMetadata(json.at("metadata"));
    object.SetMetadata(metadata);

    return Object{name, x, y, type};
}
