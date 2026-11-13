cmake_minimum_required(VERSION 3.20)
project(Arkanoid LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include(FetchContent)
set(FETCHCONTENT_QUIET OFF)



# SFML - GRAPHICS
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        3.1.0
)

FetchContent_MakeAvailable(SFML)



# CATCH2 - TESTING
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.16.0
)
FetchContent_MakeAvailable(Catch2)



# ACTUAL THINGS TO COMPILE
set(GAME_CORE_SOURCES 
    src/core/Ball.cpp
    src/core/Paddle.cpp
    src/core/Brick.cpp
    src/core/Arena.cpp 
    src/core/Player.cpp
    src/core/World.cpp
    src/core/Geometry.cpp
)

add_library(GameCore ${GAME_CORE_SOURCES})
target_include_directories(GameCore PUBLIC src/include)

add_executable(test_sfml testing/test_sfml.cpp)
target_link_libraries(test_sfml PUBLIC 
    SFML::Graphics 
    SFML::Window 
    SFML::System 
)

add_executable(tests testing/test_main.cpp)
target_link_libraries(tests PUBLIC 
    Catch2::Catch2WithMain 
    GameCore 
)


