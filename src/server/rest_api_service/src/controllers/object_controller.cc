#include "controllers/object_controller.hpp"
#include <nlohmann/json.hpp>
#include "aux/object_group_handler/object_group_handler.hpp"

void ObjectController::GetObjects(Context &ctx) {
    auto &res = ctx.GetResponse();

    //todo: add limit and offset
    try {
        auto group_by = ctx.GetParam("group_by");
        auto min_count = std::atoi(ctx.GetParam("min_count").c_str());
        auto objects = object_service_.GetAllObjects();

        std::map<std::string, std::vector<Object>> grouped_objects;

        if (group_by == "distance") {
            grouped_objects = GroupByDistance(objects);
        } else if (group_by == "name") {
            grouped_objects = GroupByName(objects);
        } else if (group_by == "type") {
            grouped_objects = GroupByType(objects, min_count);
        } else if (group_by == "time") {
            grouped_objects = GroupByCreationTime(objects);
        } else {
            grouped_objects["all"] = objects;
        }

        nlohmann::json json_result;

        for (const auto &group : grouped_objects) {
            nlohmann::json json_array = nlohmann::json::array();
            for (const auto &object : group.second) {
                json_array.push_back(ObjectSerializer::ToJson(object));
            }
            json_result[group.first] = json_array;
        }

        std::string json_string = json_result.dump();
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
        auto json = nlohmann::json::parse(req.body());
        auto object = ObjectSerializer::FromJson(json);
        object_service_.AddObject(object);

        res.result(http::status::created);
        res.body() = R"({"success": "Object created."})";
        res.set(http::field::content_type, "application/json");
    } catch (const std::invalid_argument &e) {
        res.result(http::status::bad_request);
        res.body() = R"({"error": ")" + std::string(e.what()) + R"("})";
        res.set(http::field::content_type, "application/json");
    } catch (const nlohmann::json::parse_error &e) {
        res.result(http::status::bad_request);
        res.body() = R"({"error": "Invalid JSON payload."})";
        res.set(http::field::content_type, "application/json");
    } catch (const std::exception &e) {
        res.result(http::status::internal_server_error);
        res.body() = R"({"error": ")" + std::string(e.what()) + R"("})";
        res.set(http::field::content_type, "application/json");
    }
}

void ObjectController::GetObjectById(Context &ctx) {
    auto &res = ctx.GetResponse();

    try {
        unsigned int id = std::atoi(ctx.GetParam("id").c_str());
        auto object = object_service_.GetObjectById(id);
        if (object.GetCreationTime()) {
            std::string jsonString = ObjectSerializer::ToJson(object).dump();
            res.result(http::status::ok);
            res.body() = jsonString;
            res.set(http::field::content_type, "application/json");
        } else {
            res.result(http::status::not_found);
            res.body() = R"({"error": "Object not found."})";
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
            res.result(http::status::no_content);
        } else {
            res.result(http::status::not_found);
            res.body() = R"({"error": "Object not found."})";
            res.set(http::field::content_type, "application/json");
        }
    } catch (const std::exception &e) {
        res.result(http::status::internal_server_error);
    }
}
