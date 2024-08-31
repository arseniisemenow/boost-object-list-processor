#include "rest_api_handler.hpp"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <iostream>

RestApiHandler::RestApiHandler(boost::asio::io_context& ioc, const std::string& address, unsigned short port)
    : acceptor_(ioc, {boost::asio::ip::make_address(address), port}) {}

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
        // Handle the HTTP request here
        boost::beast::http::request<boost::beast::http::string_body> req;
        handle_request(std::move(req), socket);
    }

    do_accept();
}

void RestApiHandler::handle_request(boost::beast::http::request<boost::beast::http::string_body> req,
                                    boost::asio::ip::tcp::socket& socket) {
    // Process the request and interact with the database here

    // Test  response
    boost::beast::http::response<boost::beast::http::string_body> res{
        boost::beast::http::status::ok, req.version()};
    res.set(boost::beast::http::field::server, "Boost.Beast");
    res.set(boost::beast::http::field::content_type, "application/json");
    res.body() = R"({"message": "Hello, world!"})";
    res.prepare_payload();

    boost::beast::http::write(socket, res);
}
