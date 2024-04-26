#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Flight {
    std::string flight_number;
    std::string departure_time;
    std::string arrival_time;
    std::string duration;
    std::string airline;
};

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string get_request(const std::string& url)
{
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return readBuffer;
}

void getFlights(const std::string& date, const std::string& from, const std::string& to) {
    std::string apiKey = "6b8adbd5-4ed0-47a8-b020-a64cd7031468";
    std::string url = "https://api.rasp.yandex.net/v3.0/search/?apikey=" + apiKey + "&format=json&date=" + date + "&from=" + from + "&to=" + to;

    std::string response = get_request(url);
    if (!response.empty()) {
        json data = json::parse(response);

        if (data.find("segments") != data.end() && !data["segments"].is_null()) {
            for (const auto& segment : data["segments"]) {
                std::string carrierTitle = segment["thread"]["carrier"]["title"];
                std::cout << "Carrier: " << carrierTitle << std::endl;
                std::cout << "Departure time: " << segment["departure"] << std::endl;
                std::cout << "Arrival time: " << segment["arrival"] << std::endl;
                std::cout << std::endl;
            }
        }
        else {
            std::cout << "No flights were found for the specified date and location." << std::endl;
        }
    }
    else {
        std::cout << "An error occurred while making the API request." << std::endl;
    }
}

void getNearestStations(const std::string& city) {
    std::string apiKey = "6b8adbd5-4ed0-47a8-b020-a64cd7031468";
    std::string url = "https://api.rasp.yandex.net/v3.0/nearest_stations/" + city + "&fields=items.point&key=" + apiKey;

    std::string response = get_request(url);
    if (!response.empty()) {
        json data = json::parse(response);

        if (!data["result"].is_null() && data["result"]["items"].size() > 0) {
            float lat = data["result"]["items"][0]["point"]["lat"].get<float>();
            float lon = data["result"]["items"][0]["point"]["lon"].get<float>();
            std::cout << "Latitude: " << lat << std::endl;
            std::cout << "Longitude: " << lon << std::endl;
            std::cout << std::endl;

            std::string stationsUrl = "https://api.rasp.yandex.net/v3.0/nearest_stations/?apikey=d946fec0-4ee8-4107-9212-07643c816efe&format=json&lat="
                + std::to_string(lat) + "&lng=" + std::to_string(lon) + "&distance=50&lang=ru_RU";
            std::string stationsResponse = get_request(stationsUrl);

            if (!stationsResponse.empty()) {
                json stationsData = json::parse(stationsResponse);

                if (stationsData.count("stations") > 0) {
                    for (const auto& station : stationsData["stations"]) {
                        std::string name = station["name"].get<std::string>();
                        std::cout << "Station: " << name << std::endl;
                        std::cout << "Adress: " << station["address"].get<std::string>() << std::endl;
                        std::cout << std::endl;
                    }
                }
                else {
                    std::cout << "No nearest stations were found at the specified address." << std::endl;
                }
            }
            else {
                std::cout << "An error occurred while querying nearby stations." << std::endl;
            }
        }
        else {
            std::cout << "An error occurred while querying nearby stations." << std::endl;
        }
    }
    else {
        std::cout << "An error occurred while executing the geocode request." << std::endl;
    }
}

void getCarrierInfo(const std::string& code) {
    std::string apiKey = "6b8adbd5-4ed0-47a8-b020-a64cd7031468";
    std::string url = "https://api.rasp.yandex.net/v3.0/carrier/?apikey=" + apiKey + "&code=" + code;

    std::string response = get_request(url);
    if (!response.empty()) {
        json data = json::parse(response);

        if (!data["title"].is_null()) {
            std::cout << "Carrier: " << data["title"] << std::endl;
            std::cout << "Number: " << data["phones"][0] << std::endl;
            std::cout << "URL: " << data["url"] << std::endl;
        }
        else {
            std::cout << "Carrier not found for the specified code." << std::endl;
        }
    }
    else {
        std::cout << "An error occurred while making the API request." << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::string date, from, to;
    std::cout << "Enter date (YYYY-MM-DD): ";
    std::cin >> date;
    std::cout << "Enter departure: ";
    std::cin >> from;
    std::cout << "Enter arrival: ";
    std::cin >> to;

    int choice;
    do {
        std::cout << std::endl;
        std::cout << "Menu:" << std::endl;
        std::cout << "1. View your ticket for the specified dates and locations." << std::endl;
        std::cout << "2. View nearby stations." << std::endl;
        std::cout << "3. View carrier information." << std::endl;
        std::cout << "Enter your choice (1-3) or 0, to leave: ";
        std::cin >> choice;
        std::cout << std::endl;

        switch (choice) {
        case 1:
            getFlights(date, from, to);
            break;
        case 2: {
            std::string city;
            std::cout << "Enter city: ";
            std::cin >> city;

            getNearestStations(city);
            break;
        }
        case 3: {
            std::string code;
            std::cout << "Enter carrier code: ";
            std::cin >> code;
            getCarrierInfo(code);
            break;
        }
        case 0:
            std::cout << "Exit" << std::endl;
            break;
        default:
            std::cout << "No such option." << std::endl;
            break;
        }
    } while (choice != 0);

    return 0;
}
