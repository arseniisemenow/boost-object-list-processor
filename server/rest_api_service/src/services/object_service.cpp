#include "../include/services/object_service.hpp"
#include "include/models/object.hpp"

void ObjectService::AddObject(const Object &Object) {
    objects_.push_back(Object);
}

std::vector<Object> ObjectService::GetAllObjects() { return objects_; }

std::optional<Object> ObjectService::GetObjectById(unsigned int id) {
//  for (auto &Object : objects_) {
//    if (Object.getId() == id)
//      return Object;
//  }
  return std::nullopt;
}

bool ObjectService::DeleteObjectById(unsigned int id) {
//  for (auto it = objects_.begin(); it != objects_.end();) {
//    if (it->getId() == id) {
//      it = objects_.erase(it);
//      return true;
//    } else {
//      ++it;
//    }
//  }
  return false;
}