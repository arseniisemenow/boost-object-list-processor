#include "postgres_database_manager.hpp"

int main() {
    std::string connection_str = "dbname=mydb user=myuser password=mypass hostaddr=127.0.0.1 port=5432";
    PostgresDatabaseManager db_manager(connection_str);

    // Create tables
    db_manager.CreateTables();

    // Insert an object
    Object obj("John Doe", 10.5, 20.3, "Person", 1693235249.98678);
    db_manager.InsertObject(obj);

    // Retrieve all objects
    std::vector<Object> objects = db_manager.GetAllObjects();
    for (const auto& obj : objects) {
        std::cout << obj.GetName() << std::endl;
    }

    return 0;
}