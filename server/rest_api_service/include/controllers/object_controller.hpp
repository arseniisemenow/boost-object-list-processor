#pragma once

#include "../context.hpp"
#include "../serializers/object_serializer.hpp"
#include "../services/object_service.hpp"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/json.hpp>
#include <cstdlib>

namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;   // from <boost/beast/http.hpp>
namespace asio = boost::asio;    // from <boost/asio.hpp>
using tcp = asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class ObjectController {

public:
  explicit ObjectController(IObjectService& service)
      : object_service_(service) {}

  void GetObjects(Context &ctx);
  void ObjectPerson(Context &ctx);
  void GetObjectById(Context &ctx);
  void DeleteObjectById(Context &ctx);

  private:
  IObjectService&object_service_;
};
