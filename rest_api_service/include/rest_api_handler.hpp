#ifndef REST_API_HANDLER_HPP
#define REST_API_HANDLER_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>

class RestApiHandler {
 public:
    RestApiHandler(boost::asio::io_context& ioc, const std::string& address, unsigned short port);

    void start();

 private:
    void do_accept();
    void on_accept(boost::beast::error_code ec, boost::asio::ip::tcp::socket socket);
    void handle_request(boost::beast::http::request<boost::beast::http::string_body> req,
                        boost::asio::ip::tcp::socket& socket);

    boost::asio::ip::tcp::acceptor acceptor_;
};

#endif // REST_API_HANDLER_HPP
