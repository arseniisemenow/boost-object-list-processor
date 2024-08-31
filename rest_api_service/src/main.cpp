#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include "rest_api_handler.hpp"

int main() {
    try {
        boost::asio::io_context ioc;

        RestApiHandler api_handler(ioc, "0.0.0.0", 8080);
        api_handler.start();

        ioc.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
