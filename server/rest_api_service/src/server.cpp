#include "../include/server.hpp"

void Server::Session(tcp::socket socket) {
  try {
    beast::flat_buffer buffer;
    http::request<http::string_body> req;
    http::read(socket, buffer, req);
    http::response<http::string_body> res;
    auto ctx = Context(req, res);

    // Delegate the routing to the Router instance
    if (!router_.Route(ctx)) {
      // If no Route matches, respond with Not Found
      res.result(http::status::not_found);
      res.body() = "Resource not found";
    }
    if (res.body().length() != 0)
      res.prepare_payload();

    http::write(socket, res);
  } catch (std::exception const &e) {
    std::cerr << "Session error: " << e.what() << std::endl;
  }
}

void Server::Run() {
  tcp::acceptor acceptor{
      io_context_, {tcp::v4(), static_cast<uint16_t>(port_)}};
  for (;;) {
    tcp::socket socket{io_context_};
    acceptor.accept(socket);
    std::thread(&Server::Session, this, std::move(socket)).detach();
  }
}

short Server::GetPort() { return port_; }
