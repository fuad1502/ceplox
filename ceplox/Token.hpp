#pragma once

#include "TokenType.hpp"
#include <string>
#include <variant>

class Token {
  Token(std::string lexeme, TokenType tokenType,
        std::variant<bool, double, std::string> literal, int line);
  friend std::ostream &operator<<(std::ostream &stream, const Token &token);

private:
  std::string lexeme;
  TokenType tokenType;
  std::variant<bool, double, std::string> literal;
  int line;
};
