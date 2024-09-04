#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "context.hpp"
#include "router.hpp"
#include <boost/asio.hpp>
#include <boost/beast.hpp>

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class Server {
 public:
    Server(short port, Router &router)
        : port_(port), router_(router) {}
    void Session(tcp::socket socket);
    [[noreturn]] void Run();
    [[nodiscard]] short GetPort() const;

 private:
    short port_;
    Router &router_;
    asio::io_context io_context_{1};
};

#endif// SERVER_HPP_