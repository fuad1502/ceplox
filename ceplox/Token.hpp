#pragma once

#include "TokenType.hpp"
#include <optional>
#include <string>
#include <variant>

using LiteralValue = std::variant<bool, double, std::string>;

class Token {
public:
  Token(std::string lexeme, TokenType tokenType,
        std::optional<LiteralValue> literal, int line);
  friend std::ostream &operator<<(std::ostream &stream, const Token &token);

private:
  std::string lexeme;
  TokenType tokenType;
  std::optional<LiteralValue> literal;
  int line;
};
