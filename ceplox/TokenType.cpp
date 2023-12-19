#include "TokenType.hpp"
#include <map>

std::ostream &operator<<(std::ostream &out, const TokenType tokenType) {
  static const auto tokenTypeStrings = [] {
    std::map<TokenType, std::string_view> result;
#define INSERT_ELEMENT(p) result.emplace(p, #p);
    INSERT_ELEMENT(TokenType::LEFT_PAREN);
    INSERT_ELEMENT(TokenType::LEFT_PAREN);
    INSERT_ELEMENT(TokenType::RIGHT_PAREN);
    INSERT_ELEMENT(TokenType::LEFT_BRACE);
    INSERT_ELEMENT(TokenType::RIGHT_BRACE);
    INSERT_ELEMENT(TokenType::COMMA);
    INSERT_ELEMENT(TokenType::DOT);
    INSERT_ELEMENT(TokenType::MINUS);
    INSERT_ELEMENT(TokenType::PLUS);
    INSERT_ELEMENT(TokenType::SEMICOLON);
    INSERT_ELEMENT(TokenType::SLASH);
    INSERT_ELEMENT(TokenType::STAR);
    INSERT_ELEMENT(TokenType::BANG);
    INSERT_ELEMENT(TokenType::BANG_EQUAL);
    INSERT_ELEMENT(TokenType::EQUAL);
    INSERT_ELEMENT(TokenType::EQUAL_EQUAL);
    INSERT_ELEMENT(TokenType::GREATER);
    INSERT_ELEMENT(TokenType::GREATER_EQUAL);
    INSERT_ELEMENT(TokenType::LESS);
    INSERT_ELEMENT(TokenType::LESS_EQUAL);
    INSERT_ELEMENT(TokenType::IDENTIFIER);
    INSERT_ELEMENT(TokenType::STRING);
    INSERT_ELEMENT(TokenType::NUMBER);
    INSERT_ELEMENT(TokenType::AND);
    INSERT_ELEMENT(TokenType::CLASS);
    INSERT_ELEMENT(TokenType::ELSE);
    INSERT_ELEMENT(TokenType::FALSE);
    INSERT_ELEMENT(TokenType::FUN);
    INSERT_ELEMENT(TokenType::FOR);
    INSERT_ELEMENT(TokenType::IF);
    INSERT_ELEMENT(TokenType::NIL);
    INSERT_ELEMENT(TokenType::OR);
    INSERT_ELEMENT(TokenType::PRINT);
    INSERT_ELEMENT(TokenType::RETURN);
    INSERT_ELEMENT(TokenType::SUPER);
    INSERT_ELEMENT(TokenType::THIS);
    INSERT_ELEMENT(TokenType::TRUE);
    INSERT_ELEMENT(TokenType::VAR);
    INSERT_ELEMENT(TokenType::WHILE);
    INSERT_ELEMENT(TokenType::END_OF_FILE);
#undef INSERT_ELEMENT
    return result;
  }();

  return out << tokenTypeStrings.at(tokenType);
}
