#include "Token.hpp"
#include <variant>

std::ostream &operator<<(std::ostream &stream,
                         const std::optional<LiteralValue> &literal);

Token::Token(std::string lexeme, TokenType tokenType,
             std::optional<LiteralValue> literal, int line)
    : lexeme{lexeme}, tokenType{tokenType}, literal{literal}, line{line} {}

std::ostream &operator<<(std::ostream &stream, const Token &token) {
  return stream << token.tokenType << " " << token.lexeme << " "
                << token.literal;
}

std::ostream &operator<<(std::ostream &stream,
                         const std::optional<LiteralValue> &literal) {
  if (literal.has_value()) {
    auto variant = literal.value();
    if (std::holds_alternative<bool>(variant)) {
      return stream << std::get<bool>(variant);
    } else if (std::holds_alternative<double>(variant)) {
      return stream << std::get<double>(variant);
    } else if (std::holds_alternative<std::string>(variant)) {
      return stream << std::get<std::string>(variant);
    } else {
      return stream;
    }
  } else {
    return stream << "nullopt";
  }
}
