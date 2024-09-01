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
 public:
    // Getters
    [[nodiscard]] std::string GetName() const { return name_; }
    [[nodiscard]] double GetX() const { return x_; }
    [[nodiscard]] double GetY() const { return y_; }
    [[nodiscard]] std::string GetType() const { return type_; }
    [[nodiscard]] double GetCreationTime() const { return creation_time_; }
    [[nodiscard]] Metadata& GetMetadata() { return metadata_; }

    // Setters
    void SetName(const std::string& name) { name_ = name; }
    void SetX(double x) { x_ = x; }
    void SetY(double y) { y_ = y; }
    void SetType(const std::string& type) { type_ = type; }
    void SetCreationTime(double creation_time) { creation_time_ = creation_time; }
    void SetMetadata(const Metadata& metadata) { metadata_ = metadata; }



 private:
    std::string name_;
    double x_;
    double y_;
    std::string type_;
    double creation_time_;
    Metadata metadata_;
};
#endif// OBJECT_LIST_PROCESSOR_INCLUDE_OBJECT_HPP_