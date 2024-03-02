#include <iostream>
#include <string>
#include <vector>
#include <cpprest/http_client.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;

// Структура для хранения прогноза погоды на один день
struct DailyWeatherForecast {
    std::string date;
    std::string description;
    double temperature;
};

// Функция для получения прогноза погоды на 5 дней с сайта openweathermap.com
std::vector<DailyWeatherForecast> getWeatherForecast(const std::string& postalCode)
{
    std::vector<DailyWeatherForecast> forecast;

    // Замените YOUR_API_KEY на свой ключ API с сайта openweathermap.com
    const std::string apiKey = "YOUR_API_KEY";

    // Формирование URL для запроса
    const std::string url = "http://api.openweathermap.org/data/2.5/forecast?zip=" + postalCode + ",us&appid=" + apiKey;

    http_client client(url);

    // Отправка GET-запроса и обработка ответа
    json::value jsonResponse = client.request(methods::GET).get().extract_json().get();

    // Извлечение данных из JSON-ответа
    json::array forecasts = jsonResponse["list"].as_array();

    for (const auto& forecastData : forecasts)
    {
        DailyWeatherForecast dailyForecast;

        dailyForecast.date = forecastData["dt_txt"].as_string();
        dailyForecast.description = forecastData["weather"][0]["description"].as_string();
        dailyForecast.temperature = forecastData["main"]["temp"].as_double();

        forecast.push_back(dailyForecast);
    }

    return forecast;
}

int main()
{
    std::cout << "Введите почтовый индекс: ";
    std::string postalCode;
    std::cin >> postalCode;

    std::vector<DailyWeatherForecast> weatherForecast = getWeatherForecast(postalCode);

    int choice = 0;
    while (choice != 6)
    {
        std::cout << "Меню:" << std::endl;
        std::cout << "1. Просмотр прогноза для введенного пользователем почтового индекса" << std::endl;
        std::cout << "2. Просмотр прогноза на все 5 дней" << std::endl;
        std::cout << "3. Просмотр прогноза на конкретный день" << std::endl;
        std::cout << "4. Отображение самой низкой и самой высокой температур из всех прогнозов" << std::endl;
        std::cout << "5. Реализация еще как минимум одной креативной опции" << std::endl;
        std::cout << "6. Выход" << std::endl;
        std::cout << "Введите номер выбранного действия: ";
        std::cin >> choice;

        switch (choice)
        {
            case 1:
            {
                std::cout << "Прогноз погоды для почтового индекса " << postalCode << ":" << std::endl;
                for (const auto& forecast : weatherForecast)
                {
                    std::cout << "Дата: " << forecast.date << std::endl;
                    std::cout << "Описание: " << forecast.description << std::endl;
                    std::cout << "Температура: " << forecast.temperature << std::endl;
                    std::cout << std::endl;
                }
                break;
            }
            case 2:
            {
                std::cout << "Прогноз погоды на все 5 дней:" << std::endl;
                for (const auto& forecast : weatherForecast)
                {
                    std::cout << "Дата: " << forecast.date << std::endl;
                    std::cout << "Описание: " << forecast.description << std::endl;
                    std::cout << "Температура: " << forecast.temperature << std::endl;
                    std::cout << std::endl;
                }
                break;
            }
            case 3:
            {
                std::cout << "Введите номер дня (от 1 до 5): ";
                int day;
                std::cin >> day;

                if (day >= 1 && day <= 5)
                {
                    const auto& forecast = weatherForecast[day - 1];
                    std::cout << "Прогноз погоды на " << forecast.date << ":" << std::endl;
                    std::cout << "Описание: " << forecast.description << std::endl;
                    std::cout << "Температура: " << forecast.temperature << std::endl;
                }
                else
                {
                    std::cout << "Некорректный номер дня!" << std::endl;
                }
                break;
            }
            case 4:
            {
                double minTemperature = weatherForecast[0].temperature;
                double maxTemperature = weatherForecast[0].temperature;

                for (const auto& forecast : weatherForecast)
                {
                    if (forecast.temperature < minTemperature)
                    {
                        minTemperature = forecast.temperature;
                    }

                    if (forecast.temperature > maxTemperature)
                    {
                        maxTemperature = forecast.temperature;
                    }
                }

                std::cout << "Самая низкая температура: " << minTemperature << std::endl;
                std::cout << "Самая высокая температура: " << maxTemperature << std::endl;
                break;
            }
            case 5:
            {
                // Креативная опция
                std::cout << "Реализация креативной опции." << std::endl;
                break;
            }
            case 6:
            {
                std::cout << "Выход." << std::endl;
                break;
            }
            default:
            {
                std::cout << "Некорректный номер действия!" << std::endl;
                break;
            }
        }

        std::cout << std::endl;
    }

    return 0;
}
