cmake_minimum_required(VERSION 3.20)
project(Arkanoid LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#todo transision to FetchContent style for sfml (and later catch2) importing 
find_package(SFML 3.0 REQUIRED COMPONENTS Graphics Window System)

add_executable(test_sfml testing/test_sfml.cpp)
target_link_libraries(test PRIVATE SFML::Graphics SFML::Window SFML::System)

find_package(Catch2 3 REQUIRED)
add_executable(tests /testing/main_test.cpp)
target_link_libraries(testing PRIVATE Catch2::Catch2WithMain)

add_library(GameCore src/core/core.cpp)
target_include_directories(GameCore PUBLIC src/core)
