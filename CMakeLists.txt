cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME driver_work_period)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


FIND_PACKAGE(Boost)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

add_library(DriverData STATIC DriverData.hpp DriverData.cpp)

add_executable(${PROJECT_NAME} main.cpp)
TARGET_LINK_LIBRARIES(${PROJECT_NAME}
    LINK_PUBLIC ${Boost_LIBRARIES}
    LINK_PRIVATE DriverData)
