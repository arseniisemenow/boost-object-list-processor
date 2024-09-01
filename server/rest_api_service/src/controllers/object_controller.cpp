#include "../include/controllers/object_controller.hpp"

void ObjectController::GetObjects(Context &ctx) {
  auto &res = ctx.GetResponse();

  try {
    auto persons = object_service_.GetAllObjects();
    boost::json::array jsonArray;
    for (const auto &person : persons) {
      jsonArray.push_back(ObjectSerializer::ToJson(person));
    }
    std::string jsonString = boost::json::serialize(jsonArray);
    res.result(http::status::ok);
    res.body() = jsonString;
    res.set(http::field::content_type, "application/json");
  } catch (const std::exception &e) {
    res.result(http::status::internal_server_error);
    res.body() = "{\"error\": \"Failed to serialize objects_.\"}";
    res.set(http::field::content_type, "application/json");
  }
}

void ObjectController::ObjectPerson(Context &ctx) {
  auto &req = ctx.GetRequest();
  auto &res = ctx.GetResponse();

  try {
    auto json = boost::json::parse(req.body());
    auto object = ObjectSerializer::FromJson(json.as_object());
    object_service_.AddObject(object);
    res.result(http::status::created);
    res.body() = "{\"success\": \"Person created.\"}";
    res.set(http::field::content_type, "application/json");
  } catch (const std::exception &e) {
    res.result(http::status::bad_request);
    res.body() = "Invalid JSON payload";
  }
}

void ObjectController::GetObjectById(Context &ctx) {
  auto &res = ctx.GetResponse();

  try {
    unsigned int id = std::atoi(ctx.GetParam("id").c_str());
    auto object = object_service_.GetObjectById(id);

    if (object) {
      std::string jsonString =
          boost::json::serialize(ObjectSerializer::ToJson(object.value()));
      res.result(http::status::ok);
      res.body() = jsonString;
      res.set(http::field::content_type, "application/json");
    } else {
      res.result(http::status::not_found);
      res.body() = "{\"error\": \"Person not found.\"}";
      res.set(http::field::content_type, "application/json");
    }
  } catch (const std::exception &e) {
    res.result(http::status::internal_server_error);
    res.body() = "{\"error\": \"Failed to serialize objects_.\"}";
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
      res.body() = "{\"error\": \"Person not found.\"}";
      res.set(http::field::content_type, "application/json");
    }
  } catch (const std::exception &e) {
    res.result(http::status::internal_server_error);
  }
}
