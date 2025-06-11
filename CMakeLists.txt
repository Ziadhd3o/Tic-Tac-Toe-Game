cmake_minimum_required(VERSION 3.31)
project(SF)

set(CMAKE_CXX_STANDARD 20)
set(SFML_DIR C:/SFML3/lib/cmake/SFML)

add_executable(SF main.cpp)
find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio Network)
include_directories(C:/SFML3/include/)
target_link_libraries(SF PRIVATE SFML::Graphics SFML::Audio SFML::Network)