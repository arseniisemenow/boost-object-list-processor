#include "../include/controllers/object_controller.hpp"
#include "../include/router.hpp"
#include "../include/server.hpp"
#include "../include/services/object_service.hpp"
#include <iostream>
#include <memory>

int main(void) {
    try {
        Router router{};
        PersonService personService{};
        ObjectController personController{personService};
        Server server{8080, router};

        router.SetPrefix("/v1");

        router.AddRoute(GET, "/person", [personController](auto &ctx) {
            personController->GetObjects(ctx);
        });
//
//        router_.AddRoute(POST, "/person", [personController](auto &ctx) {
//            personController->ObjectPerson(ctx);
//        });
//
//        router_.AddRoute(GET, "/person/{id}", [personController](auto &ctx) {
//            personController->GetObjectById(ctx);
//        });
//
//        router_.AddRoute(DELETE, "/person/{id}", [personController](auto &ctx) {
//            personController->DeleteObjectById(ctx);
//        });

        std::cout << "Server starting on port_ " << server.GetPort() << std::endl;
        server.Run();
    } catch (std::exception const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
