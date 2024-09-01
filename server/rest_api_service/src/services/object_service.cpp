#include "../include/services/object_service.hpp"
#include "include/models/object.hpp"
#include <pqxx/pqxx>

ObjectService::ObjectService(const std::string &connection_string)
    : connection_string_(connection_string) {
    try {
        pqxx::connection conn(connection_string_);

        // Prepare the SQL statements
        conn.prepare("insert_object", "INSERT INTO objects (name, x, y, type, creation_time) VALUES ($1, $2, $3, $4, $5)");
        conn.prepare("select_object_by_id", "SELECT id, name, x, y, type, creation_time FROM objects WHERE id = $1");
        conn.prepare("delete_object_by_id", "DELETE FROM objects WHERE id = $1");

    } catch (const std::exception &e) {
        //todo: change to another error
//        std::cerr << "Error preparing statements: " << e.what() << std::endl;
    }
}

void ObjectService::AddObject(const Object &object) {
    try {
        pqxx::connection conn(connection_string_);
        pqxx::work txn(conn);

        txn.exec_prepared("insert_object",
                          object.GetName(),
                          object.GetX(),
                          object.GetY(),
                          object.GetType(),
                          object.GetCreationTime());

        txn.commit();
    } catch (const std::exception &e) {
        //todo: change to another error
//        std::cerr << "Error adding object: " << e.what() << std::endl;
    }
}

std::vector<Object> ObjectService::GetAllObjects() {
    std::vector<Object> objects;

    try {
        pqxx::connection conn(connection_string_);
        pqxx::work txn(conn);

        pqxx::result result = txn.exec("SELECT id, name, x, y, type, creation_time FROM objects");

        for (const auto &row : result) {
            Object object;
            object.SetName(row["name"].as<std::string>());
            object.SetX(row["x"].as<double>());
            object.SetY(row["y"].as<double>());
            object.SetType(row["type"].as<std::string>());
            object.SetCreationTime(row["creation_time"].as<std::time_t>());

            objects.push_back(object);
        }

    } catch (const std::exception &e) {
        //todo: change
//        std::cerr << "Error fetching objects: " << e.what() << std::endl;
    }

    return objects;
}


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