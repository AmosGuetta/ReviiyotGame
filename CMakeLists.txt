cmake_minimum_required(VERSION 3.6)
project(ReviiyotGame)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES reviiyot.cpp)

add_executable(ReviiyotGame src/Card.cpp src/Deck.cpp src/Game.cpp src/Hand.cpp src/Player.cpp src/reviiyot.cpp)