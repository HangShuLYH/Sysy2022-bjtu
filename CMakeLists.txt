cmake_minimum_required(VERSION 3.21)
project(Sysy2022-bjtu)
include_directories(include)
include_directories(include/frontend)
add_subdirectory(src/frontend)
add_executable(
        compiler
        main.cpp)
target_link_libraries(
        compiler
        driver
)