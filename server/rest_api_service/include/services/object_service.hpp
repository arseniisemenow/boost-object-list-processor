#pragma once

#include "shared/include/models/object.hpp"
#include <vector>

class IObjectService {
 public:
    virtual void AddObject(const Object &object) = 0;
    virtual std::vector<Object> GetAllObjects() = 0;
    virtual std::optional<Object> GetObjectById(unsigned int id) = 0;
    virtual bool DeleteObjectById(unsigned int id) = 0;
};

class ObjectService : public IObjectService {

 public:
    explicit ObjectService(const std::string &connection_string);

    void AddObject(const Object &Object) override;
    std::vector<Object> GetAllObjects() override;
    std::optional<Object> GetObjectById(unsigned int id) override;
    bool DeleteObjectById(unsigned int id) override;

 private:
    std::string connection_string_;// PostgreSQL connection string
    void InitializeDatabase();     // Helper function to prepare SQL statements
};