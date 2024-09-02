#include "../include/controllers/object_controller.hpp"
#include <nlohmann/json.hpp>

void ObjectController::GetObjects(Context &ctx) {
    auto &res = ctx.GetResponse();

    try {
        auto objects = object_service_.GetAllObjects();
        nlohmann::json json_array = nlohmann::json::array();

        for (const auto &object : objects) {
            json_array.push_back(ObjectSerializer::ToJson(object));
        }

        std::string json_string = json_array.dump(); // Serialize to JSON string
        res.result(http::status::ok);
        res.body() = json_string;
        res.set(http::field::content_type, "application/json");
    } catch (const std::exception &e) {
        res.result(http::status::internal_server_error);
        res.body() = R"({"error": "Failed to serialize objects."})";
        res.set(http::field::content_type, "application/json");
    }
}

void ObjectController::CreateObject(Context &ctx) {
    auto &req = ctx.GetRequest();
    auto &res = ctx.GetResponse();

    try {
        auto json = nlohmann::json::parse(req.body());  // Parse the request body as JSON
        auto object = ObjectSerializer::FromJson(json); // Convert JSON to Object
        object_service_.AddObject(object);

        res.result(http::status::created);
        res.body() = R"({"success": "Person created."})";
        res.set(http::field::content_type, "application/json");
    } catch (const std::exception &e) {
        res.result(http::status::bad_request);
        res.body() = R"({"error": "Invalid JSON payload."})";
        res.set(http::field::content_type, "application/json");
    }
}

void ObjectController::GetObjectById(Context &ctx) {
    auto &res = ctx.GetResponse();

    try {
        unsigned int id = std::atoi(ctx.GetParam("id").c_str());
        auto object = object_service_.GetObjectById(id);

        if (object) {
            std::string jsonString = ObjectSerializer::ToJson(object.value()).dump(); // Convert Object to JSON string
            res.result(http::status::ok);
            res.body() = jsonString;
            res.set(http::field::content_type, "application/json");
        } else {
            res.result(http::status::not_found);
            res.body() = R"({"error": "Person not found."})";
            res.set(http::field::content_type, "application/json");
        }
    } catch (const std::exception &e) {
        res.result(http::status::internal_server_error);
        res.body() = R"({"error": "Failed to serialize objects."})";
        res.set(http::field::content_type, "application/json");
    }
}

void ObjectController::DeleteObjectById(Context &ctx) {
    auto &res = ctx.GetResponse();

    try {
        unsigned int id = std::atoi(ctx.GetParam("id").c_str());

        if (object_service_.DeleteObjectById(id)) {
            res.result(http::status::no_content); // No content status for successful deletion
        } else {
            res.result(http::status::not_found);
            res.body() = R"({"error": "Person not found."})";
            res.set(http::field::content_type, "application/json");
        }
    } catch (const std::exception &e) {
        res.result(http::status::internal_server_error);
    }
}
