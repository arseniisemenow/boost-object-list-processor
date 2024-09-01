#include "rest_api_handler.hpp"
#include "postgres_database_manager.hpp"
//todo: add this dir to the cmakelists

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <boost/json.hpp>
#include <iostream>

namespace http = boost::beast::http;
//namespace json = boost::json;

// Session Class to handle individual connections
class Session : public std::enable_shared_from_this<Session> {
 public:
    Session(boost::asio::ip::tcp::socket socket, PostgresDatabaseManager& db_manager)
        : socket_(std::move(socket)), db_manager_(db_manager) {}

    void start() {
        read_request();
    }

 private:
    boost::asio::ip::tcp::socket socket_;
    boost::beast::flat_buffer buffer_;
    http::request<http::string_body> req_;
    PostgresDatabaseManager& db_manager_;

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
            // Parse JSON request body
            auto body = json::parse(req_.body());
            // Extract data from JSON and insert into the database
            Object object;  // Create your object and populate it with data from the body
            // Assuming Object is a struct or class with proper fields
            object.name = json::value_to<std::string>(body.at("name"));
            object.x = json::value_to<double>(body.at("x"));
            object.y = json::value_to<double>(body.at("y"));
            object.type = json::value_to<std::string>(body.at("type"));
            object.timestamp = json::value_to<std::time_t>(body.at("timestamp"));

            db_manager_.InsertObject(object);

            // Send success response
            send_json_response(R"({"status": "success"})");
        } catch (std::exception& e) {
            handle_bad_request("Failed to parse request body");
        }
    }

    void handle_get_objects() {
        // Query all objects from the database
        std::vector<Object> objects = db_manager_.GetAllObjects();

        // Convert to JSON array
        json::array json_objects;
        for (const auto& object : objects) {
            json::object json_obj;
            json_obj["name"] = object.name;
            json_obj["x"] = object.x;
            json_obj["y"] = object.y;
            json_obj["type"] = object.type;
            json_obj["timestamp"] = object.timestamp;
            json_objects.push_back(json_obj);
        }

        send_json_response(json::serialize(json_objects));
    }

    void handle_bad_request(const std::string& message) {
        http::response<http::string_body> res{http::status::bad_request, req_.version()};
        res.set(http::field::content_type, "application/json");
        res.body() = R"({"error": ")" + message + R"("})";
        res.prepare_payload();
        send_response(res);
    }

    void send_json_response(const std::string& body) {
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




RestApiHandler::RestApiHandler(boost::asio::io_context& ioc, const std::string& address, unsigned short port)
    : acceptor_(ioc, {boost::asio::ip::make_address(address), port}), db_manager_("postgres://user:password@localhost/dbname") {}

void RestApiHandler::start() {
    do_accept();
}

void RestApiHandler::do_accept() {
    acceptor_.async_accept(
        [this](boost::beast::error_code ec, boost::asio::ip::tcp::socket socket) {
            on_accept(ec, std::move(socket));
        });
}

void RestApiHandler::on_accept(boost::beast::error_code ec, boost::asio::ip::tcp::socket socket) {
    if (!ec) {
        std::make_shared<Session>(std::move(socket), db_manager_)->start();
    }
    do_accept();
}

