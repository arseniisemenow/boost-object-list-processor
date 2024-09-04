#include "aux/object_group_handler/object_group_handler.hpp"

#include <algorithm>
#include <cmath>

double CalculateDistance(double x, double y) {
    return std::sqrt(x * x + y * y);
}

std::string GetDistanceGroup(double distance) {
    if (distance <= 100) return "Up to 100 units";
    if (distance <= 1000) return "Up to 1000 units";
    if (distance <= 10000) return "Up to 10000 units";
    return "Too far";
}

std::string GetNameGroup(const std::string &name) {
    char first_char = static_cast<char>(std::toupper(name[0]));
    if (std::isalpha(first_char)) return {1, first_char};
    return "#";
}

std::string GetTimeGroup(const std::time_t &creation_time) {
    std::tm *tm = std::localtime(&creation_time);
    std::time_t now = std::time(nullptr);
    std::tm *now_tm = std::localtime(&now);

    // Example conditions for grouping, you may need to refine these
    if (tm->tm_yday == now_tm->tm_yday && tm->tm_year == now_tm->tm_year)
        return "Today";
    else if (tm->tm_yday == now_tm->tm_yday + 1 && tm->tm_year == now_tm->tm_year)
        return "Tomorrow";
    else if (tm->tm_yday <= now_tm->tm_yday + 7 && tm->tm_year == now_tm->tm_year)
        return "This Week";
    else if (tm->tm_mon == now_tm->tm_mon && tm->tm_year == now_tm->tm_year)
        return "This Month";
    else if (tm->tm_year == now_tm->tm_year)
        return "This Year";
    return "Earlier";
}

std::map<std::string, std::vector<Object>> GroupByDistance(const std::vector<Object> &objects) {
    std::map<std::string, std::vector<Object>> distance_groups;

    for (const auto &object : objects) {
        double distance = CalculateDistance(object.GetX(), object.GetY());
        std::string group = GetDistanceGroup(distance);
        distance_groups[group].push_back(object);
    }

    // Sort each group by distance
    for (auto &[group_name, group_objects] : distance_groups) {
        std::sort(group_objects.begin(), group_objects.end(), [](const Object &a, const Object &b) {
            return CalculateDistance(a.GetX(), a.GetY()) < CalculateDistance(b.GetX(), b.GetY());
        });
    }

    return distance_groups;
}

std::map<std::string, std::vector<Object>> GroupByName(const std::vector<Object> &objects) {
    std::map<std::string, std::vector<Object>> name_groups;

    for (const auto &object : objects) {
        std::string group = GetNameGroup(object.GetName());
        name_groups[group].push_back(object);
    }

    // Sort each group by name
    for (auto &[group_name, group_objects] : name_groups) {
        std::sort(group_objects.begin(), group_objects.end(), [](const Object &a, const Object &b) {
            return a.GetName() < b.GetName();
        });
    }

    return name_groups;
}

std::map<std::string, std::vector<Object>> GroupByType(const std::vector<Object> &objects, int min_count) {
    if (min_count <= 0) {
        min_count = 3;
    }
    std::map<std::string, std::vector<Object>> type_groups;
    std::map<std::string, int> type_count;

    for (const auto &object : objects) {
        type_count[object.GetType()]++;
    }

    for (const auto &object : objects) {
        std::string type = object.GetType();
        if (type_count[type] < min_count) {
            type_groups["other"].push_back(object);
        } else {
            type_groups[type].push_back(object);
        }
    }

    // Sort each group by name
    for (auto &[group_name, group_objects] : type_groups) {
        std::sort(group_objects.begin(), group_objects.end(), [](const Object &a, const Object &b) {
            return a.GetName() < b.GetName();
        });
    }

    return type_groups;
}

std::map<std::string, std::vector<Object>> GroupByCreationTime(const std::vector<Object> &objects) {
    std::map<std::string, std::vector<Object>> time_groups;

    for (const auto &object : objects) {
        std::string group = GetTimeGroup(object.GetCreationTime());
        time_groups[group].push_back(object);
    }

    // Sort each group by creation time
    for (auto &[group_name, group_objects] : time_groups) {
        std::sort(group_objects.begin(), group_objects.end(), [](const Object &a, const Object &b) {
            return a.GetCreationTime() < b.GetCreationTime();
        });
    }

    return time_groups;
}
