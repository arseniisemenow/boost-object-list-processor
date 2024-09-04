#pragma once

#include "shared/include/models/object.hpp"
#include <pqxx/except>
#include <vector>

class IObjectService {
 public:
    virtual void AddObject(const Object &object) = 0;
    virtual std::vector<Object> GetAllObjects() = 0;
    virtual Object GetObjectById(unsigned int id) = 0;
    virtual bool DeleteObjectById(unsigned int id) = 0;
    virtual bool DeleteAllObjects() = 0;
};

class ObjectService : public IObjectService {

 public:
    explicit ObjectService(std::string connection_string);

    void AddObject(const Object &Object) override;
    std::vector<Object> GetAllObjects() override;
    Object GetObjectById(unsigned int id) override;
    bool DeleteObjectById(unsigned int id) override;
    bool DeleteAllObjects() override;

    void MigrateTable();

 private:
    std::string connection_string_;
    static void LogSqlError(const pqxx::pqxx_exception &e);
};