cmake_minimum_required(VERSION 3.10.2)

project(Bank)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g -Wall")

include_directories(include)
file(GLOB CLASSES "src/*.cpp")

set(SOURCESS ${CLASSES} "Bank.cpp")
add_executable(${PROJECT_NAME} ${SOURCESS})
