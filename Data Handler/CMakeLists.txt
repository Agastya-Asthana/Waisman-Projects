cmake_minimum_required(VERSION 3.22)
project(Data_Handler)

set(CMAKE_CXX_STANDARD 23)

find_package(Matplot++ REQUIRED)

add_executable(Data_Handler main.cpp)
target_link_libraries(Data_Handler Matplot++::matplot)

add_executable(MatplotPlayground MatplotPlayground.cpp)
target_link_libraries(MatplotPlayground Matplot++::matplot)
