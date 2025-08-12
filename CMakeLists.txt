cmake_minimum_required(VERSION 3.12)
project(WeatherApp)

set(CMAKE_CXX_STANDARD 17)


add_library(httplib INTERFACE)
target_include_directories(httplib INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/httplib
)

find_package(nlohmann_json 3.2.0 REQUIRED)

add_executable(weather_app
    src/weather_app.cpp
)

target_link_libraries(weather_app
    PRIVATE
    httplib
    nlohmann_json::nlohmann_json
    ssl crypto  # Для HTTPS в httplib
)
