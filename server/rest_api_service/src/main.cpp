#include "../include/controllers/object_controller.hpp"
#include "../include/router.hpp"
#include "../include/server.hpp"
#include "../include/services/object_service.hpp"
#include <iostream>
#include <memory>

int main(void) {
    try {
        Router router{};
        ObjectService object_service{};
        ObjectController person_controller{object_service};
        Server server{8080, router};

        router.SetPrefix("/v1");

        //        router.AddRoute(GET, "/person", [person_controller](auto &ctx) {
        //            person_controller->GetObjects(ctx);
        //        });
        //
        //        router_.AddRoute(POST, "/person", [person_controller](auto &ctx) {
        //            person_controller->ObjectPerson(ctx);
        //        });
        //
        //        router_.AddRoute(GET, "/person/{id}", [person_controller](auto &ctx) {
        //            person_controller->GetObjectById(ctx);
        //        });
        //
        //        router_.AddRoute(DELETE, "/person/{id}", [person_controller](auto &ctx) {
        //            person_controller->DeleteObjectById(ctx);
        //        });

        std::cout << "Server starting on port_ " << server.GetPort() << std::endl;
        server.Run();
    } catch (std::exception const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
