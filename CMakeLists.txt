cmake_minimum_required(VERSION 3.14)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(ceplox)

add_subdirectory(code_generator)

add_custom_command(
  OUTPUT Expr.cpp Expr.hpp ExprVisitor.hpp
  COMMAND ExprGenerator ARGS 
        ${CMAKE_SOURCE_DIR}/code_generator/grammar.txt 
        ${CMAKE_BINARY_DIR}/
  DEPENDS ExprGenerator code_generator/grammar.txt
)

add_executable(ceplox ceplox/main.cpp)

target_sources(ceplox PRIVATE ceplox/Ceplox.cpp ceplox/Scanner.cpp ceplox/Token.cpp ceplox/TokenType.cpp Expr.cpp ceplox/ExprPrinter.cpp ceplox/Parser.cpp)

target_include_directories(ceplox PRIVATE ceplox)
target_include_directories(ceplox PRIVATE ${CMAKE_BINARY_DIR})
