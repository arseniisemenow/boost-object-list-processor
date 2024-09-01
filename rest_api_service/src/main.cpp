#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include "rest_api_handler.hpp"

int main() {
    try {
        boost::asio::io_context io_context;

        RestApiHandler api_handler(io_context, "0.0.0.0", 8080);
        api_handler.start();

        io_context.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
