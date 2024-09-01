#ifndef OBJECT_LIST_PROCESSOR_SERVER_REST_API_SERVICE_INCLUDE_SESSION_HPP_
#define OBJECT_LIST_PROCESSOR_SERVER_REST_API_SERVICE_INCLUDE_SESSION_HPP_

#include "postgres_database_manager.hpp"
#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <nlohmann/json.hpp>

namespace http = boost::beast::http;
using json = nlohmann::json;

class Session : public std::enable_shared_from_this<Session> {
 public:
    Session(boost::asio::ip::tcp::socket socket, PostgresDatabaseManager &db_manager)
        : socket_(std::move(socket)), db_manager_(db_manager) {}

    void start() {
        read_request();
    }

 private:
    boost::asio::ip::tcp::socket socket_;
    boost::beast::flat_buffer buffer_;
    http::request<http::string_body> req_;
    PostgresDatabaseManager &db_manager_;

    void read_request() {
        auto self = shared_from_this();
        http::async_read(socket_, buffer_, req_,
                         [self](boost::beast::error_code ec, std::size_t bytes_transferred) {
                             boost::ignore_unused(bytes_transferred);
                             if (!ec) {
                                 self->handle_request();
                             }
                         });
    }

    void handle_request() {
        // Route handling
        if (req_.method() == http::verb::post && req_.target() == "/objects") {
            handle_post_object();
        } else if (req_.method() == http::verb::get && req_.target() == "/objects") {
            handle_get_objects();
        } else {
            handle_bad_request("Invalid request method or target");
        }
    }

    void handle_post_object() {
        try {
            // Parse JSON request body using nlohmann::json
            auto body = json::parse(req_.body());

            // Extract data from JSON and insert it into the database
            Object object;// Assuming Object is a struct or class with proper fields
            object.SetName(body.at("name").get<std::string>());
            object.SetX(body.at("x").get<double>());
            object.SetY(body.at("y").get<double>());
            object.SetType(body.at("type").get<std::string>());
            //            object.timestamp = body.at("timestamp").get<std::time_t>();

            db_manager_.InsertObject(object);

            // Send success response
            send_json_response(R"({"status": "success"})");
        } catch (std::exception &e) {
            handle_bad_request("Failed to parse request body: " + std::string(e.what()));
        }
    }

    void handle_get_objects() {
        // Query all objects from the database
        std::vector<Object> objects = db_manager_.GetAllObjects();

        // Convert to JSON array using nlohmann::json
        json json_objects = json::array();
        for (const auto &object : objects) {
            json json_obj = {
                {"name", object.GetName()},
                {"x", object.GetX()},
                {"y", object.GetY()},
                {"type", object.GetType()},
                {"timestamp", object.GetCreationTime()}};
            json_objects.push_back(json_obj);
        }

        send_json_response(json_objects.dump());
    }

    void handle_bad_request(const std::string &message) {
        http::response<http::string_body> res{http::status::bad_request, req_.version()};
        res.set(http::field::content_type, "application/json");
        res.body() = json{{"error", message}}.dump();
        res.prepare_payload();
        send_response(res);
    }

    void send_json_response(const std::string &body) {
        http::response<http::string_body> res{http::status::ok, req_.version()};
        res.set(http::field::content_type, "application/json");
        res.body() = body;
        res.prepare_payload();
        send_response(res);
    }

    void send_response(http::response<http::string_body> res) {
        auto self = shared_from_this();
        http::async_write(socket_, res,
                          [self](boost::beast::error_code ec, std::size_t bytes_transferred) {
                              boost::ignore_unused(bytes_transferred);
                              self->socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);
                          });
    }
};

#endif//OBJECT_LIST_PROCESSOR_SERVER_REST_API_SERVICE_INCLUDE_SESSION_HPP_
