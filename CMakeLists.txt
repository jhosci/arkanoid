cmake_minimum_required(VERSION 3.20)
project(Arkanoid LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

# Fetch SFML 3.0.0
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        3.0.0
)
FetchContent_MakeAvailable(SFML)

# Fetch Catch2
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.16.1
)
FetchContent_MakeAvailable(Catch2)

# Executable 1: SFML test
add_executable(test_sfml testing/test_sfml.cpp)
target_link_libraries(test_sfml PRIVATE SFML::Graphics SFML::Window SFML::System)

# Executable 2: Unit tests
add_executable(tests testing/main_test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

# Library: Game Core
add_library(GameCore src/core/core.cpp)
target_include_directories(GameCore PUBLIC src/core)