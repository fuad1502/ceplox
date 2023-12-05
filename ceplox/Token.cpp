#include "Token.hpp"
#include <variant>

std::ostream &
operator<<(std::ostream &stream,
           const std::variant<bool, double, std::string> &variant);

Token::Token(std::string lexeme, TokenType tokenType,
             std::variant<bool, double, std::string> literal, int line)
    : lexeme{lexeme}, tokenType{tokenType}, literal{literal}, line{line} {}

std::ostream &operator<<(std::ostream &stream, const Token &token) {
  return stream << token.tokenType << " " << token.lexeme << " "
                << token.literal;
}

std::ostream &
operator<<(std::ostream &stream,
           const std::variant<bool, double, std::string> &variant) {
  if (std::holds_alternative<bool>(variant)) {
    return stream << std::get<bool>(variant);
  } else if (std::holds_alternative<double>(variant)) {
    return stream << std::get<double>(variant);
  } else if (std::holds_alternative<std::string>(variant)) {
    return stream << std::get<std::string>(variant);
  } else {
    return stream;
  }
}
