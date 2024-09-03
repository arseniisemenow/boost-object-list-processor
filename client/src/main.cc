#include <iostream>
#include <string>
#include <curl/curl.h>

const std::string base_url = "http://localhost:8080/v1/object";

// Function to print a menu for user interaction
void print_menu() {
    std::cout << "1. Get all objects\n";
    std::cout << "2. Insert new object\n";
    std::cout << "3. Exit\n";
    std::cout << "Choose an option: ";
}

// CURL write callback to capture the HTTP response body
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response) {
    size_t total_size = size * nmemb;
    response->append((char*)contents, total_size);
    return total_size;
}

// Function to make a GET request to retrieve all objects
void get_all_objects() {
    CURL* curl;
    CURLcode res;
    std::string response_string;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, base_url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "Objects retrieved:\n" << response_string << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

// Function to build a JSON string manually
std::string build_json(const std::string& name, int x, int y, const std::string& type, const std::string& metadata) {
    return "{\"name\":\"" + name + "\",\"x\":" + std::to_string(x) + ",\"y\":" + std::to_string(y) +
        ",\"type\":\"" + type + "\",\"metadata\":" + metadata + "}";
}

// Function to make a POST request to insert a new object
void insert_new_object() {
    std::string name, type, metadata_key, metadata_value, metadata_json;
    int x, y;

    std::cout << "Enter object name: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "Enter object type (Tree, Bush, Doghouse, Swing, Southpaw): ";
    std::getline(std::cin, type);

    std::cout << "Enter x coordinate: ";
    std::cin >> x;

    std::cout << "Enter y coordinate: ";
    std::cin >> y;

    // Collect metadata as JSON string
    std::string add_more_metadata;
    metadata_json = "{";
    bool first = true;
    do {
        std::cout << "Enter metadata key (or type 'done' to finish): ";
        std::cin.ignore();
        std::getline(std::cin, metadata_key);

        if (metadata_key == "done") break;

        std::cout << "Enter metadata value: ";
        std::getline(std::cin, metadata_value);

        if (!first) {
            metadata_json += ",";
        }
        metadata_json += "\"" + metadata_key + "\":\"" + metadata_value + "\"";
        first = false;

        std::cout << "Add more metadata? (yes/no): ";
        std::getline(std::cin, add_more_metadata);
    } while (add_more_metadata == "yes");

    metadata_json += "}";

    std::string json_payload = build_json(name, x, y, type, metadata_json);

    CURL* curl;
    CURLcode res;
    std::string response_string;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, base_url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            if (response_string.empty()) {
                std::cout << "Object inserted successfully." << std::endl;
            } else {
                std::cout << "Response:\n" << response_string << std::endl;
            }
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

[[noreturn]] int main() {
    int option;

    while (true) {
        print_menu();
        std::cin >> option;

        switch (option) {
            case 1:
                get_all_objects();
                break;
            case 2:
                insert_new_object();
                break;
            case 3:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cerr << "Invalid option. Please try again.\n";
                break;
        }
    }
}
