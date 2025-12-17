cmake_minimum_required(VERSION 3.10)

project(MiniUber)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

add_executable(MiniUber
    src/main.cpp
    src/Driver.h
    src/Driver.cpp
    src/Rider.h
    src/Rider.cpp
    src/Pattern.h
    src/Pattern.cpp
    src/Ride.h
    src/RideManager.h
    src/RideManager.cpp
)