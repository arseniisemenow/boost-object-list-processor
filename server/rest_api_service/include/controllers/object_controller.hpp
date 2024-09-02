#pragma once

#include "../context.hpp"
#include "../serializers/object_serializer.hpp"
#include "../services/object_service.hpp"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <cstdlib>

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class ObjectController {

 public:
    explicit ObjectController(IObjectService &service)
        : object_service_(service) {}

    void GetObjects(Context &ctx);
    void CreateObject(Context &ctx);
    void GetObjectById(Context &ctx);
    void DeleteObjectById(Context &ctx);

 private:
    IObjectService &object_service_;
};
