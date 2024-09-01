#ifndef OBJECT_LIST_PROCESSOR_DB_POSTGRES_DATABASE_MANAGER_HPP_
#define OBJECT_LIST_PROCESSOR_DB_POSTGRES_DATABASE_MANAGER_HPP_

#include "base_database_manager.hpp"
#include <pqxx/pqxx>

class PostgresDatabaseManager : public BaseDatabaseManager {
 public:
    explicit PostgresDatabaseManager(const std::string &connection_string) : BaseDatabaseManager(connection_string), conn_(connection_string) {}

    void InsertObject(const Object &object) override {
        try {
            pqxx::work W(conn_);
            std::string query = "INSERT INTO objects (name, x, y, type, creation_time) VALUES (" +
                W.quote(object.GetName()) + ", " +
                W.quote(object.GetX()) + ", " +
                W.quote(object.GetY()) + ", " +
                W.quote(object.GetType()) + ", " +
                W.quote(object.GetCreationTime()) + ");";
            W.exec(query);
            W.commit();
            std::cout << "Object inserted successfully." << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error inserting object: " << e.what() << std::endl;
        }
    }
    std::vector<Object> GetAllObjects() override {
        std::vector<Object> objects;
        try {
            pqxx::work W(conn_);
            pqxx::result R = W.exec("SELECT name, x, y, type, creation_time FROM objects");

            for (const auto& row : R) {
                objects.emplace_back(row[0].c_str(), row[1].as<double>(), row[2].as<double>(), row[3].c_str(), row[4].as<double>());
            }

            std::cout << "Objects retrieved successfully." << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error retrieving objects: " << e.what() << std::endl;
        }

        return objects;
    }
    void CreateTables() override {
        try {
            pqxx::work worker(conn_);
            worker.exec("CREATE TABLE IF NOT EXISTS objects ("
                        "id SERIAL PRIMARY KEY, "
                        "name VARCHAR(100), "
                        "x DOUBLE PRECISION, "
                        "y DOUBLE PRECISION, "
                        "type VARCHAR(50), "
                        "creation_time DOUBLE PRECISION)");
            worker.commit();
            std::cout << "Tables created successfully." << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "Error creating tables: " << e.what() << std::endl;
        }
    }

 private:
    pqxx::connection conn_;
};

#endif// OBJECT_LIST_PROCESSOR_DB_POSTGRES_DATABASE_MANAGER_HPP_
