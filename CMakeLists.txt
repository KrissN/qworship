cmake_minimum_required(VERSION 2.8.11)

project(qworship)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Quick)
find_package(Qt5LinguistTools)

add_subdirectory(src)
