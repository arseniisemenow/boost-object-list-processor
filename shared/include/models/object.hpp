#pragma once

#include <boost/asio.hpp>
#include <string>
#include <variant>

class Object {
 public:
    using Metadata =
        std::unordered_map<std::string, std::variant<int, double, std::string>>;
    Object() = default;
    Object(const std::string& name, double x, double y, const std::string& type, time_t creation_time)
        : name_(name), x_(x), y_(y), type_(type), creation_time_(creation_time) {}
    Object(const std::string& name, double x, double y, const std::string& type)
        : name_(name), x_(x), y_(y), type_(type) {}
 public:
    // Getters
    [[nodiscard]] std::string GetName() const { return name_; }
    [[nodiscard]] double GetX() const { return x_; }
    [[nodiscard]] double GetY() const { return y_; }
    [[nodiscard]] std::string GetType() const { return type_; }
    [[nodiscard]] time_t GetCreationTime() const { return creation_time_; }
    [[nodiscard]] Metadata& GetMetadata() { return metadata_; }

    // Setters
    void SetName(const std::string& name) { name_ = name; }
    void SetX(double x) { x_ = x; }
    void SetY(double y) { y_ = y; }
    void SetType(const std::string& type) { type_ = type; }
    void SetCreationTime(time_t creation_time) { creation_time_ = creation_time; }
    void SetMetadata(const Metadata& metadata) { metadata_ = metadata; }

 private:
    std::string name_;
    double x_;
    double y_;
    std::string type_;
    time_t creation_time_;
    Metadata metadata_;
};