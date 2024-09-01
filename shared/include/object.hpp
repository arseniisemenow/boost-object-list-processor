#ifndef OBJECT_LIST_PROCESSOR_INCLUDE_OBJECT_HPP_
#define OBJECT_LIST_PROCESSOR_INCLUDE_OBJECT_HPP_

#include <iostream>
#include <string>
#include <unordered_map>
#include <variant>

class Object {
 public:
    using Metadata =
        std::unordered_map<std::string, std::variant<int, double, std::string>>;
//todo: implement the rule of five
    Object() = default;
    Object(const std::string &name, double x, double y, const std::string &type,
           double creation_time);

    [[nodiscard]] std::string GetName() const;
    [[nodiscard]] double GetX() const;
    [[nodiscard]] double GetY() const;
    [[nodiscard]] std::string GetType() const;
    [[nodiscard]] double GetCreationTime() const;
    [[nodiscard]] Metadata &GetMetadata();

 private:
    std::string name_;
    double x_;
    double y_;
    std::string type_;
    double creation_time_;
    Metadata metadata_;
};
#endif// OBJECT_LIST_PROCESSOR_INCLUDE_OBJECT_HPP_