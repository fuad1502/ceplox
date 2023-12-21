#include "Token.hpp"
#include <variant>

Token::Token(std::string lexeme, TokenType tokenType,
             std::optional<LiteralValue> literal, int line)
    : lexeme{lexeme}, tokenType{tokenType}, literal{literal}, line{line} {}

std::string Token::getLexeme() const { return lexeme; }
TokenType Token::getTokenType() const { return tokenType; }
std::optional<LiteralValue> Token::getLiteral() const { return literal; }
int Token::getLine() const { return line; }

std::ostream &operator<<(std::ostream &stream, const Token &token) {
  return stream << token.tokenType << " " << token.lexeme << " "
                << token.literal;
}

template <typename T>
std::ostream &operator<<(std::ostream &stream, const std::optional<T> &opt) {
  if (opt.has_value()) {
    return stream << opt.value();
  } else {
    return stream << "nullopt";
  }
}

std::ostream &operator<<(std::ostream &stream, const LiteralValue &literal) {
  if (std::holds_alternative<bool>(literal)) {
    return stream << std::get<bool>(literal);
  } else if (std::holds_alternative<double>(literal)) {
    return stream << std::get<double>(literal);
  } else if (std::holds_alternative<std::string>(literal)) {
    return stream << std::get<std::string>(literal);
  } else {
    return stream;
  }
}
