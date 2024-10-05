cmake_minimum_required(VERSION 3.21)

project(Battle)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

find_package(GTest REQUIRED)

add_executable(Battle main.cpp src/game.cpp src/interface.cpp src/map.cpp src/map_builder.cpp src/ship.cpp src/game_loop.cpp)

add_executable(Test test.cpp src/map.cpp src/ship.cpp)

target_link_libraries(Battle sfml-graphics sfml-audio)

target_link_libraries(Test GTest::gtest)