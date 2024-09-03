#ifndef OBJECT_LIST_PROCESSOR_SHARED_INCLUDE_OBJECT_GROUP_HANDLER_OBJECT_GROUP_HANDLER_HPP_
#define OBJECT_LIST_PROCESSOR_SHARED_INCLUDE_OBJECT_GROUP_HANDLER_OBJECT_GROUP_HANDLER_HPP_

#include "shared/include/models/object.hpp"
#include <ctime>
#include <map>
#include <vector>

double CalculateDistance(double x, double y);

std::string GetDistanceGroup(double distance);

std::string GetNameGroup(const std::string &name);

std::string GetTimeGroup(const std::time_t &creation_time);

std::map<std::string, std::vector<Object>> GroupByDistance(const std::vector<Object> &objects);

std::map<std::string, std::vector<Object>> GroupByName(const std::vector<Object> &objects);

std::map<std::string, std::vector<Object>> GroupByType(const std::vector<Object> &objects, int min_count);

std::map<std::string, std::vector<Object>> GroupByCreationTime(const std::vector<Object> &objects);

#endif//OBJECT_LIST_PROCESSOR_SHARED_INCLUDE_OBJECT_GROUP_HANDLER_OBJECT_GROUP_HANDLER_HPP_
