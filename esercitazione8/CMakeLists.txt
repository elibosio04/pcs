cmake_minimum_required(VERSION 3.20)
project(esercitazione8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

find_package(Eigen3 CONFIG REQUIRED)

add_executable(test_gc main.cpp)
target_link_libraries(test_gc PRIVATE Eigen3::Eigen)

enable_testing()
