project(ExprGenerator)

add_executable(ExprGenerator ExprGenerator.cpp)

add_custom_command(
  OUTPUT Expr.hpp
  COMMAND ExprGenerator ARGS 
        ${CMAKE_SOURCE_DIR}/code_generator/grammar.txt 
        ${CMAKE_BINARY_DIR}/code_generator/Expr.hpp
  DEPENDS ExprGenerator
)

add_custom_target(ExprGeneratorTarget DEPENDS Expr.hpp)
