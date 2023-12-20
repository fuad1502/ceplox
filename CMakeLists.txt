cmake_minimum_required(VERSION 3.14)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(ceplox)

add_subdirectory(code_generator)

add_executable(ceplox ceplox/main.cpp)

add_dependencies(ceplox ExprGeneratorTarget)

target_sources(ceplox PRIVATE ceplox/Ceplox.cpp ceplox/Scanner.cpp ceplox/Token.cpp ceplox/TokenType.cpp)

target_include_directories(ceplox PRIVATE ceplox)
target_include_directories(ceplox PRIVATE ${CMAKE_BINARY_DIR}/code_generator)
