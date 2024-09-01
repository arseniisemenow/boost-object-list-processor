#include "rest_api_handler.hpp"
#include "postgres_database_manager.hpp"
// todo: add this dir to the cmakelists

#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <iostream>
#include <nlohmann/json.hpp>

namespace http = boost::beast::http;
using json = nlohmann::json;

RestApiHandler::RestApiHandler(boost::asio::io_context &io_context,
                               const std::string &address,
                               unsigned short port)
    : acceptor_(io_context, {boost::asio::ip::make_address(address), port}),
      session_()db_manager_("postgres://user:password@localhost/dbname") {}

void RestApiHandler::start() {
    do_accept();
}

void RestApiHandler::do_accept() {
    acceptor_.async_accept(
        [this](boost::beast::error_code ec, boost::asio::ip::tcp::socket socket) {
            on_accept(ec, std::move(socket));
        });
}

void RestApiHandler::on_accept(boost::beast::error_code error_code, boost::asio::ip::tcp::socket socket) {
    if (!error_code) {
        std::make_shared<Session>(std::move(socket), db_manager_)->start();
        sess
    }
    do_accept();
}
