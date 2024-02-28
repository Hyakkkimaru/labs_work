#include <iostream>
#include <curl/curl.h>
#include <rapidjson/document.h>
#include <vector>
#include <algorithm>

using namespace std;
using namespace rapidjson;

struct DailyWeatherForecast {
    string date;
    double temperature;
};

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* response) {
    size_t newLength = size * nmemb;
    response->append((char*)contents, newLength);
    return newLength;
}

vector<DailyWeatherForecast> getWeatherForecast(string postalCode) {
    vector<DailyWeatherForecast> forecast;
    string apiKey = "e74e099d8d21f608679a4682469043ac";

    string url = "http://api.openweathermap.org/data/2.5/forecast?zip=" + postalCode + ",us&appid=" + apiKey;

    CURL* curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            cout << "Сталась помилка під час отримання прогнозу погоди: " << curl_easy_strerror(res) << endl;
        } else {
            Document document;
            document.Parse(response.c_str());

            const Value& list = document["list"];
            for (SizeType i = 0; i < list.Size(); i++) {
                const Value& item = list[i];
                double temperature = item["main"]["temp"].GetDouble();
                string date = item["dt_txt"].GetString();

                DailyWeatherForecast weatherForecast;
                weatherForecast.date = date;
                weatherForecast.temperature = temperature;

                forecast.push_back(weatherForecast);
            }
        }

        curl_easy_cleanup(curl);
    }

    return forecast;
}

void viewForecastByPostalCode() {
    cout << "Введіть поштовий індекс: ";
    string postalCode;
    cin >> postalCode;

    vector<DailyWeatherForecast> forecast = getWeatherForecast(postalCode);

    if (forecast.empty()) {
        cout << "Прогноз погоди недоступний" << endl;
        return;
    }

    cout << "Прогноз погоди для поштового індексу " << postalCode << ":" << endl;
    for (const auto& weatherForecast : forecast) {
        cout << "Дата: " << weatherForecast.date << ", Температура: " << weatherForecast.temperature << "°C" << endl;
    }
}

void viewForecastForAllDays() {
    vector<DailyWeatherForecast> forecast = getWeatherForecast("YOUR_POSTAL_CODE"); // Замените YOUR_POSTAL_CODE на ваш почтовый индекс

    if (forecast.empty()) {
        cout << "Прогноз погоди недоступний" << endl;
        return;
    }

    cout << "Прогноз погоди на всі дні:" << endl;
    for (const auto& weatherForecast : forecast) {
        cout << "Дата: " << weatherForecast.date << ", Температура: " << weatherForecast.temperature << "°C" << endl;
    }
}

void viewForecastForSpecificDay() {
    cout << "Введіть дату (у форматі YYYY-MM-DD): ";
    string date;
    cin >> date;

    vector<DailyWeatherForecast> forecast = getWeatherForecast("YOUR_POSTAL_CODE"); // Замените YOUR_POSTAL_CODE на ваш почтовый индекс

    if (forecast.empty()) {
        cout << "Прогноз погоди недоступний" << endl;
        return;
    }

    cout << "Прогноз погоди на " << date << ":" << endl;
    for (const auto& weatherForecast : forecast) {
        if (weatherForecast.date.find(date) != string::npos) {
            cout << "Температура: " << weatherForecast.temperature << "°C" << endl;
        }
    }
}

void displayHighestAndLowestTemperature() {
    vector<DailyWeatherForecast> forecast = getWeatherForecast("YOUR_POSTAL_CODE"); // Замените YOUR_POSTAL_CODE на ваш почтовый индекс

    if (forecast.empty()) {
        cout << "Прогноз погоди недоступний" << endl;
        return;
    }

    double highestTemperature = forecast[0].temperature;
    double lowestTemperature = forecast[0].temperature;

    for (const auto& weatherForecast : forecast) {
        highestTemperature = max(highestTemperature, weatherForecast.temperature);
        lowestTemperature = min(lowestTemperature, weatherForecast.temperature);
    }

    cout << "Найвища температура: " << highestTemperature << "°C" << endl;
    cout << "Найнижча температура: " << lowestTemperature << "°C" << endl;
}

int main() {
    while (true) {
        cout << "Меню:" << endl;
        cout << "1. Просмотр прогноза для введенного пользователем почтового индекса" << endl;
        cout << "2. Просмотр прогноза на все 5 дней" << endl;
        cout << "3. Просмотр прогноза на конкретный день" << endl;
        cout << "4. Отображение самой низкой и самой высокой температур из всех" << endl;
        cout << "0. Вихід" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 0:
                return 0;
            case 1:
                viewForecastByPostalCode();
                break;
            case 2:
                viewForecastForAllDays();
                break;
            case 3:
                viewForecastForSpecificDay();
                break;
            case 4:
                displayHighestAndLowestTemperature();
                break;
            default:
                cout << "Невірний вибір. Введіть ще раз." << endl;
                break;
        }

        cout << endl;
    }
}
