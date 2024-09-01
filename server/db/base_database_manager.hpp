#ifndef OBJECT_LIST_PROCESSOR_DB_BASE_DATABASE_MANAGER_HPP_
#define OBJECT_LIST_PROCESSOR_DB_BASE_DATABASE_MANAGER_HPP_

#include <stdio.h>
#include "object.hpp"


/*
 * Base interface
 */
class BaseDatabaseManager {
 public:
  BaseDatabaseManager(const std::string& connection_string){
  };
  virtual void InsertObject(const Object& object);
  virtual std::vector<Object> GetAllObjects();
  virtual void CreateTables();
};

#endif// OBJECT_LIST_PROCESSOR_DB_BASE_DATABASE_MANAGER_HPP_
