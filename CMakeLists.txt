cmake_minimum_required(VERSION 3.21)
project(rooz_lab_1)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenCV REQUIRED)

add_executable(rooz_lab_1 main.cpp)
target_link_libraries(rooz_lab_1 ${OpenCV_LIBS})
