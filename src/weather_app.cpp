#include <ctime>
#include <iomanip>
#include <iostream>
#include "../libs/httplib.h" 
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main() {
    std::string api_key = "Your_API";
    std::string city;

    std::cout << "Enter the city ";
    std::cin >> city;

    httplib::Client client("http://api.openweathermap.org");
    std::string path = "/data/2.5/weather?q=" + city + "&appid=" + api_key + "&units=metric&lang=ru";

    auto response = client.Get(path.c_str());

    std::time_t t = std::time(nullptr);
    std::tm *tm = std::localtime(&t);

    if(response && response->status == 200) {
        json data = json::parse(response->body);

        std::cout << city << " " << std::setfill('0') << std::setw(2) << tm->tm_mday << "."
        << std::setfill('0') << std::setw(2) << (tm->tm_mon + 1) << "."
        << (tm->tm_year + 1900) << "\n";

        std::cout << "Температура: "<< data["main"]["temp"] << "°C" << "(ощущается как " << data["main"]["feels_like"] << "°C)\n";
        auto is_rain = data["weather"][0]["description"];

        std::cout << "Погода: " << is_rain << "\n";

        std::cout << "Влажность: " << data["main"]["humidity"] << "\n";

        double wind_speed = data["wind"]["speed"];
        int wind_deg = data["wind"]["deg"];

        std::cout << "Ветер: " << wind_speed << " м/с, направление: " << wind_deg << "°\n";
    } else {
        std::cout << "Ошибка при получении данных\n";
    }
}