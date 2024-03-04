#include <iostream>
#include <curl/curl.h>
#include <rapidjson/document.h>
#include <string>
#include <vector>
#include <cfloat>

struct DailyWeatherForecast {
    std::string date;
    double temperature;
    std::string description;
};

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    output->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::vector<DailyWeatherForecast> fillWeatherForecast(const rapidjson::Document& document) {
    std::vector<DailyWeatherForecast> forecast;

    if (!document.HasMember("list") || !document["list"].IsArray()) {
        std::cerr << "\nFailed to parse weather forecast!" << std::endl;
        return forecast;
    }

    const rapidjson::Value& list = document["list"];
    for (rapidjson::SizeType i = 0; i < list.Size(); i++) {
        const rapidjson::Value& item = list[i];

        DailyWeatherForecast dailyForecast;
        dailyForecast.date = item["dt_txt"].GetString();
        dailyForecast.temperature = item["main"]["temp"].GetDouble();
        dailyForecast.description = item["weather"][0]["description"].GetString();

        forecast.push_back(dailyForecast);
    }

    return forecast;
}

std::vector<DailyWeatherForecast> getWeatherForecast(const std::string& postalCode) {
    std::string url = "http://api.openweathermap.org/data/2.5/forecast?zip=" + postalCode + ",ru&appid=e74e099d8d21f608679a4682469043ac"; // MY API KEY

    CURL* curl = curl_easy_init();
    std::string response;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Failed to get weather forecast. Error: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }

    std::vector<DailyWeatherForecast> forecast;
    rapidjson::Document document;
    document.Parse(response.c_str());

    forecast = fillWeatherForecast(document);

    return forecast;
}

void showTodayWeatherForecast(const std::vector<DailyWeatherForecast>& weatherForecast) {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    char dateBuffer[11];
    strftime(dateBuffer, sizeof(dateBuffer), "%Y-%m-%d", localTime);
    std::string todayDate(dateBuffer);

    bool found = false;

    for (const auto& forecast : weatherForecast) {
        if (forecast.date.substr(0, 10) == todayDate) {
            found = true;

            std::cout << "Day: " << forecast.date.substr(0, 10) << std::endl;
            std::cout << "Temperature: " << forecast.temperature << " K" << std::endl;
            std::cout << "Description: " << forecast.description << std::endl;
            break;
        }
    }

    if (!found)
        std::cout << "There is no weather forecast for today." << std::endl;
}

void showFiveWeatherForecast(const std::vector<DailyWeatherForecast>& weatherForecast) {
    bool found = false;
    for (const auto& forecast : weatherForecast) {
        found = true;

        std::cout << forecast.date << " - " << forecast.description << " - " << forecast.temperature << " K\n";
    }

    if (!found)
        std::cout << "There is no weather forecast for five days." << std::endl;
}

void showSpecificWeatherForecast(const std::vector<DailyWeatherForecast>& weatherForecast) {
    std::string date;
    std::cout << "Enter a date (yyyy-mm-dd): ";
    std::cin >> date;

    bool found = false;
    for (const auto& forecast : weatherForecast) {
        if (forecast.date.substr(0, 10) == date) {
            found = true;

            std::cout << forecast.date << " - " << forecast.description << " - " << forecast.temperature << " K\n";
        }
    }

    if (!found) {
        std::cout << "Forecast for the specified date not found.\n";
    }
}

void showLowestHighestWeatherForecast(const std::vector<DailyWeatherForecast>& weatherForecast) {
    double minTemperature = DBL_MAX;
    double maxTemperature = -DBL_MAX;
    bool found = false;
    for (const auto& forecast : weatherForecast) {
        found = true;

        if (forecast.temperature < minTemperature) {
            minTemperature = forecast.temperature;
        }
        if (forecast.temperature > maxTemperature) {
            maxTemperature = forecast.temperature;
        }
    }
    if (found) {
        std::cout << "Lowest temperature: " << minTemperature << " K\n"
                  << "Highest temperature: " << maxTemperature << " K\n";
    } else {
        std::cout << "Forecast for the lowest and highest temperatures was not found.\n";
    }
}

int main() {
    std::string postalCode;
    std::cout << "Enter the zip code: ";
    std::cin >> postalCode;

    std::vector<DailyWeatherForecast> forecast = getWeatherForecast(postalCode);

    int choice = 0;
    do {
        std::cout << "\nMenu:\n"
                  << "1. View forecast for the entered zip code\n"
                  << "2. View forecast for the next 5 days\n"
                  << "3. View forecast for a specific day\n"
                  << "4. Display the lowest and highest temperatures\n"
                  << "0. Exit\n"
                  << "\nChoose an action: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
            {
                showTodayWeatherForecast(forecast);
                break;
            }
            case 2:
            {
                showFiveWeatherForecast(forecast);
                break;
            }
            case 3:
            {
                showSpecificWeatherForecast(forecast);
                break;
            }
            case 4:
            {
                showLowestHighestWeatherForecast(forecast);
                break;
            }
            case 0:
            {
                std::cout << "Exiting the program.\n";
                break;
            }
            default:
            {
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    } while (choice != 0);

    return 0;
}
