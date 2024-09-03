#include "../include/services/object_service.hpp"
#include "shared/include/models/object.hpp"
#include "../include/serializers/object_serializer.hpp"
#include <iostream>
#include <pqxx/pqxx>
#include <utility>

ObjectService::ObjectService(std::string connection_string)
    : connection_string_(std::move(connection_string)) {
    try {
        pqxx::connection conn(connection_string_);
        MigrateTable();//fixme: Using for testing purpose. Better use Flyway migrating utility
    } catch (const pqxx::pqxx_exception &e) {
        LogSqlError(e);
    }
}

void ObjectService::AddObject(const Object &object) {
    try {
        pqxx::connection conn(connection_string_);
        pqxx::work work(conn);


        nlohmann::json metadata_json = ObjectSerializer::MetadataToJson(object.GetMetadata());
        std::string metadata_str = metadata_json.dump();

        pqxx::result result = work.exec_params("INSERT INTO objects (name, x, y, type, metadata) VALUES ($1, $2, $3, $4, $5)",
                                               object.GetName(),
                                               object.GetX(),
                                               object.GetY(),
                                               object.GetType(),
                                               metadata_str);
        work.commit();
    } catch (const pqxx::pqxx_exception &e) {
        LogSqlError(e);
    }
}

std::vector<Object> ObjectService::GetAllObjects() {
    std::vector<Object> objects;

    try {
        pqxx::connection conn(connection_string_);
        pqxx::work work(conn);

        pqxx::result result = work.exec("SELECT id, name, x, y, type, creation_time, metadata FROM objects");

        for (const auto &row : result) {
            Object object;
            object.SetName(row["name"].as<std::string>());
            object.SetX(row["x"].as<double>());
            object.SetY(row["y"].as<double>());
            object.SetType(row["type"].as<std::string>());
            object.SetCreationTime(Object::StringToTimeT(row["creation_time"].as<std::string>()));
            object.SetMetadata(ObjectSerializer::JsonToMetadata(row["metadata"].as<std::string>()));

            objects.insert(objects.cbegin(), object);
        }
        work.commit();

    } catch (const pqxx::pqxx_exception &e) {
        LogSqlError(e);
    }

    return objects;
}

Object ObjectService::GetObjectById(unsigned int id) {
    Object object{};

    try {
        pqxx::connection conn(connection_string_);
        pqxx::work work(conn);

        pqxx::result result = work.exec_params("SELECT id, name, x, y, type, creation_time FROM objects WHERE id = $1", id);

        for (const auto &row : result) {
            object.SetName(row["name"].as<std::string>());
            object.SetX(row["x"].as<double>());
            object.SetY(row["y"].as<double>());
            object.SetType(row["type"].as<std::string>());
            object.SetCreationTime(Object::StringToTimeT(row["creation_time"].as<std::string>()));
            nlohmann::json metadata_json = nlohmann::json::parse(row["metadata"].as<std::string>());
            object.SetMetadata(ObjectSerializer::JsonToMetadata(metadata_json));
        }

        work.commit();
    } catch (const pqxx::pqxx_exception &e) {
        LogSqlError(e);
    }

    return object;
}

bool ObjectService::DeleteObjectById(unsigned int id) {
    try {
        pqxx::connection conn(connection_string_);
        pqxx::work work(conn);

        pqxx::result result = work.exec_params("DELETE FROM objects WHERE id = $1", id);
        work.commit();
        return true;
    } catch (const pqxx::pqxx_exception &e) {
        LogSqlError(e);
    }
    return false;
}
void ObjectService::LogSqlError(const pqxx::pqxx_exception &e) {
    std::cerr << e.base().what() << std::endl;
    auto p_sql_error = dynamic_cast<const pqxx::sql_error *>(&e.base());
    if (p_sql_error) std::cerr << "Query was: " << p_sql_error->query() << std::endl;
}

void ObjectService::MigrateTable() {
    try {
        pqxx::connection conn(connection_string_);
        pqxx::work work(conn);
        pqxx::result result = work.exec("DROP TABLE IF EXISTS objects; CREATE TABLE IF NOT EXISTS objects (id SERIAL PRIMARY KEY, name VARCHAR(255) NOT NULL, x DOUBLE PRECISION NOT NULL, y DOUBLE PRECISION NOT NULL, \"type\" VARCHAR(100) NOT NULL, creation_time TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP, metadata JSONB);");
        work.commit();
    } catch (const pqxx::pqxx_exception &e) {
        LogSqlError(e);
    }
}