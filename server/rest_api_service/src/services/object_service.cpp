#include "../include/services/object_service.hpp"
#include "shared/include/models/object.hpp"
#include <iostream>
#include <pqxx/pqxx>

ObjectService::ObjectService(const std::string &connection_string)
    : connection_string_(connection_string) {
    try {
        pqxx::connection conn(connection_string_);

        // Prepare the SQL statements
        conn.prepare("insert_object", "INSERT INTO objects (name, x, y, type, creation_time) VALUES ($1, $2, $3, $4, $5)");
        conn.prepare("select_object_by_id", "SELECT id, name, x, y, type, creation_time FROM objects WHERE id = $1");
        conn.prepare("delete_object_by_id", "DELETE FROM objects WHERE id = $1");
        conn.prepare("migrate_table", "DROP TABLE IF EXISTS objects; CREATE TABLE IF NOT EXISTS objects (id SERIAL PRIMARY KEY, name VARCHAR(255) NOT NULL, x DOUBLE PRECISION NOT NULL, y DOUBLE PRECISION NOT NULL, \"type\" VARCHAR(100) NOT NULL, creation_time TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP);");
        MigrateTable();
    } catch (const std::exception &e) {
        //todo: change to another error
        std::cerr << "Error object service contructor: " << e.what() << std::endl;
        throw std::invalid_argument("Error object service constructor");
    }
}

void ObjectService::AddObject(const Object &object) {
    try {
        pqxx::connection conn(connection_string_);
        pqxx::work work(conn);
        pqxx::result result = work.exec_params("INSERT INTO objects (name, x, y, type) VALUES ($1, $2, $3, $4)",
                                               object.GetName(),
                                               object.GetX(),
                                               object.GetY(),
                                               object.GetType());
        work.commit();
    } catch (const pqxx::pqxx_exception &e) {
        std::cerr << e.base().what() << std::endl;
        const pqxx::sql_error *s=dynamic_cast<const pqxx::sql_error*>(&e.base());
        if (s) std::cerr << "Query was: " << s->query() << std::endl;
    }
}

std::vector<Object> ObjectService::GetAllObjects() {
    std::vector<Object> objects;

    try {
        pqxx::connection conn(connection_string_);
        pqxx::work work(conn);

        pqxx::result result = work.exec("SELECT id, name, x, y, type, creation_time FROM objects");


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

/*
 * Not the mose grace migration way
 */
bool ObjectService::MigrateTable() {
    try {
        pqxx::connection conn(connection_string_);
        pqxx::work work(conn);
        pqxx::result result = work.exec("DROP TABLE IF EXISTS objects; CREATE TABLE IF NOT EXISTS objects (id SERIAL PRIMARY KEY, name VARCHAR(255) NOT NULL, x DOUBLE PRECISION NOT NULL, y DOUBLE PRECISION NOT NULL, \"type\" VARCHAR(100) NOT NULL, creation_time TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP);");
        work.commit();
    } catch (const pqxx::pqxx_exception &e) {
        std::cerr << e.base().what() << std::endl;
        const pqxx::sql_error *s=dynamic_cast<const pqxx::sql_error*>(&e.base());
        if (s) std::cerr << "Query was: " << s->query() << std::endl;
    }

    return false;
}