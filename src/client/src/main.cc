#include <curl/curl.h>
#include <iostream>
#include <string>

bool IsNumber(const std::string &s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

const std::string kUrls[] = {
    "http://localhost:8080/v1/object",
    "http://localhost:8080/v1/object?group_by=type&min_count=1",
    "http://localhost:8080/v1/object?group_by=name",
    "http://localhost:8080/v1/object?group_by=time",
    "http://localhost:8080/v1/object?group_by=distance",
};

void PrintMenu() {
    std::cout << "1. Get all objects\n";
    std::cout << "2. Get all objects grouped by type\n";
    std::cout << "3. Get all objects grouped by name\n";
    std::cout << "4. Get all objects grouped by time\n";
    std::cout << "5. Get all objects grouped by distance\n";
    std::cout << "6. Insert new object\n";
    std::cout << "7. Delete all objects\n";
    std::cout << "8. Exit\n";
    std::cout << "Choose an option: ";
}

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *response) {
    size_t total_size = size * nmemb;
    response->append((char *) contents, total_size);
    return total_size;
}

void GetAllObjects(const int url_index) {
    CURL *curl;
    CURLcode res;
    std::string response_string;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, kUrls[url_index].c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "Objects retrieved:\n"
                      << response_string << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}
void DeleteAllObjects() {
    CURL *curl;
    CURLcode res;
    std::string response_string;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
        curl_easy_setopt(curl, CURLOPT_URL, kUrls[0].c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "Objects deleted:\n"
                      << response_string << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

std::string BuildJson(const std::string &name, int x, int y, const std::string &type, const std::string &metadata) {
    return "{\"name\":\"" + name + "\",\"x\":" + std::to_string(x) + ",\"y\":" + std::to_string(y) + ",\"type\":\"" + type + "\",\"metadata\":" + metadata + "}";
}

void InsertNewObject() {
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

    std::string add_more_metadata;
    metadata_json = "{";
    bool first = true;
    do {
        std::cout << "Enter metadata key (or type 'done' to finish): ";
        std::cin.ignore();
        metadata_key.clear();
        std::cin >> metadata_key;

        if (metadata_key == "done") break;

        std::cout << "Enter metadata value: ";
        std::cin >> metadata_value;

        if (!first) {
            metadata_json += ",";
        }
        if (!IsNumber(metadata_value)) { metadata_value = "\"" + metadata_value + "\""; }
        metadata_json += "\"" + metadata_key + "\":" + metadata_value + "";
        first = false;

    } while (1);

    metadata_json += "}";

    std::string json_payload = BuildJson(name, x, y, type, metadata_json);

    CURL *curl;
    CURLcode res;
    std::string response_string;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, kUrls[0].c_str());
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
                std::cout << "Response:\n"
                          << response_string << std::endl;
            }
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

int main() {
    int option;

    while (true) {
        PrintMenu();
        std::cin >> option;

        switch (option) {
            case 1:
                GetAllObjects(0);
                break;
            case 2:
                GetAllObjects(1);
                break;
            case 3:
                GetAllObjects(2);
                break;
            case 4:
                GetAllObjects(3);
                break;
            case 5:
                GetAllObjects(4);
                break;
            case 6:
                InsertNewObject();
                break;
            case 7:
                DeleteAllObjects();
                break;
            case 8:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cerr << "Invalid option. Please try again.\n";
                break;
        }
    }
    return 0;
}
