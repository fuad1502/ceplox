cmake_minimum_required(VERSION 3.14)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(ceplox)

add_executable(ceplox ceplox/main.cpp)

target_sources(ceplox PRIVATE ceplox/Ceplox.cpp ceplox/Scanner.cpp ceplox/Token.cpp)

target_include_directories(ceplox PRIVATE ceplox)
