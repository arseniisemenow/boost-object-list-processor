#pragma once

#include "context.hpp"
#include "router.hpp"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <vector>

namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;   // from <boost/beast/http.hpp>
namespace asio = boost::asio;    // from <boost/asio.hpp>
using tcp = asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

#define GET (http::verb::get)
#define POST (http::verb::post)
#define PUT (http::verb::put)
#define PATCH (http::verb::patch)
#define DELETE (http::verb::delete_)

class Server {
public:
  Server(short port, Router& router)
      : port_(port), router_(router) {}
  void Session(tcp::socket socket);
  void Run();
  short GetPort();

  private:
  short port_;
  Router &router_;
  asio::io_context io_context_{1};


};