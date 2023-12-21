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

  std::string getLexeme() const;
  TokenType getTokenType() const;
  std::optional<LiteralValue> getLiteral() const;
  int getLine() const;

  friend std::ostream &operator<<(std::ostream &stream, const Token &token);

private:
  std::string lexeme;
  TokenType tokenType;
  std::optional<LiteralValue> literal;
  int line;
};

template <typename T>
std::ostream &operator<<(std::ostream &stream, const std::optional<T> &opt);
std::ostream &operator<<(std::ostream &stream, const LiteralValue &literal);
