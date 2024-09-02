#include "../include/controllers/object_controller.hpp"
#include "../include/router.hpp"
#include "../include/server.hpp"
#include "../include/services/object_service.hpp"
#include <iostream>
#include <memory>

int main(void) {
    try {
        std::string connection_string = "dbname=postgres user=postgres password=postgres host=postgres_db";
        Router router{};
        ObjectService object_service{connection_string};
        ObjectController object_controller{object_service};
        Server server{8080, router};

        router.SetPrefix("/v1");
        router.AddRoute(GET, "/object", [&](auto &ctx) {
            object_controller.GetObjects(ctx);
        });

        router.AddRoute(POST, "/object", [&](auto &ctx) {
            object_controller.CreateObject(ctx);
        });
        //
        //        router_.AddRoute(GET, "/person/{id}", [object_controller](auto &ctx) {
        //            object_controller->GetObjectById(ctx);
        //        });
        //
        //        router_.AddRoute(DELETE, "/person/{id}", [object_controller](auto &ctx) {
        //            object_controller->DeleteObjectById(ctx);
        //        });

        std::cout << "Server starting on port_ " << server.GetPort() << std::endl;
        server.Run();
    } catch (std::exception const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}