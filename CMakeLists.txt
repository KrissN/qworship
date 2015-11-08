cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 11)

enable_testing()

project(qworship)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Quick)
find_package(Qt5LinguistTools)
find_package(Qt5Test)

add_subdirectory(src)
add_subdirectory(test)


