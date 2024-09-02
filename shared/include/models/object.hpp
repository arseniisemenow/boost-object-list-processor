#pragma once

#include <boost/asio.hpp>
#include <iomanip>
#include <string>
#include <variant>

class Object {
 public:
    using Metadata =
        std::unordered_map<std::string, std::variant<int, double, std::string>>;
    Object() = default;
    Object(const std::string &name, double x, double y, const std::string &type, std::time_t timestamp)
        : name_(name), x_(x), y_(y), type_(type), timestamp_(timestamp) {}
    Object(const std::string &name, double x, double y, const std::string &type)
        : name_(name), x_(x), y_(y), type_(type) {}

 public:
    // Getters
    [[nodiscard]] std::string GetName() const { return name_; }
    [[nodiscard]] double GetX() const { return x_; }
    [[nodiscard]] double GetY() const { return y_; }
    [[nodiscard]] std::string GetType() const { return type_; }
    [[nodiscard]] std::time_t GetCreationTime() const { return timestamp_; }
    [[nodiscard]] Metadata GetMetadata() const { return metadata_; }

    // Setters
    void SetName(const std::string &name) { name_ = name; }
    void SetX(double x) { x_ = x; }
    void SetY(double y) { y_ = y; }
    void SetType(const std::string &type) { type_ = type; }
    void SetCreationTime(const std::time_t &timestamp) { timestamp_ = timestamp; }
    void SetMetadata(const Metadata &metadata) { metadata_ = metadata; }

    [[nodiscard]] static std::time_t StringToTimeT(const std::string &timestamp) {
        std::tm tm = {};
        std::istringstream ss(timestamp);
        ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");

        if (ss.fail()) {
            throw std::runtime_error("Failed to parse timestamp");
        }

        return std::mktime(&tm);
    }

    [[nodiscard]] static std::string TimeTToString(std::time_t time) {
        std::tm *tm = std::localtime(&time);

        std::ostringstream ss;
        ss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");

        return ss.str();
    }

 private:
    std::string name_;
    double x_;
    double y_;
    std::string type_;
    std::time_t timestamp_;
    Metadata metadata_;

 private:
};