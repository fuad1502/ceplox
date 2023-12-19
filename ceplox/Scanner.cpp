#include "Scanner.hpp"
#include "Ceplox.hpp"
#include "TokenType.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>

Scanner::Scanner(std::string source) {
  this->source = source;
  this->current = this->source.begin();
  this->line = 1;
}

Scanner::~Scanner() {}

std::vector<Token> Scanner::scanTokens() {
  while (!isAtEnd()) {
    start = current;
    scanToken();
  }
  start = current;
  addToken(TokenType::END_OF_FILE);
  return tokens;
}

void Scanner::scanToken() {
  auto c = consume();
  switch (c) {
  // Handle one character lexemes
  case '(':
    addToken(TokenType::LEFT_PAREN);
    break;
  case ')':
    addToken(TokenType::RIGHT_PAREN);
    break;
  case '{':
    addToken(TokenType::LEFT_BRACE);
    break;
  case '}':
    addToken(TokenType::RIGHT_BRACE);
    break;
  case ',':
    addToken(TokenType::COMMA);
    break;
  case '.':
    addToken(TokenType::DOT);
    break;
  case '-':
    addToken(TokenType::MINUS);
    break;
  case '+':
    addToken(TokenType::PLUS);
    break;
  case ';':
    addToken(TokenType::SEMICOLON);
    break;
  case '*':
    addToken(TokenType::STAR);
    break;
  // Handle one or two character lexemes
  case '!':
    if (matchAndConsume('=')) {
      addToken(TokenType::BANG_EQUAL);
    } else {
      addToken(TokenType::BANG);
    }
    break;
  case '=':
    if (matchAndConsume('=')) {
      addToken(TokenType::EQUAL_EQUAL);
    } else {
      addToken(TokenType::EQUAL);
    }
    break;
  case '>':
    if (matchAndConsume('=')) {
      addToken(TokenType::GREATER_EQUAL);
    } else {
      addToken(TokenType::GREATER);
    }
    break;
  case '<':
    if (matchAndConsume('=')) {
      addToken(TokenType::LESS_EQUAL);
    } else {
      addToken(TokenType::LESS);
    }
    break;
  case '/':
    if (matchAndConsume('/')) {
      while ((peek() != '\n') && !isAtEnd())
        consume();
    } else {
      addToken(TokenType::SLASH);
    }
    break;
  // Handle whitespaces
  case ' ':
  case '\r':
  case '\t':
    break;
  // Handle new line
  case '\n':
    line++;
    break;
  // Handle string
  case '"':
    addStringToken();
    break;
  default:
    // Handle numeric
    if (isNumeric(c)) {
      addNumberToken();
    }
    // Handle identifier
    else if (isAlpha(c)) {
      addIdentifierToken();
    }
    // Unexpected character
    else {
      Ceplox::error(line, "Unexpected character.");
    }
    break;
  }
}

void Scanner::addStringToken() {
  bool foundEnclosingQuote = false;
  while (!isAtEnd()) {
    if (matchAndConsume('"')) {
      foundEnclosingQuote = true;
      break;
    }
    consume();
  }
  if (!foundEnclosingQuote) {
    Ceplox::error(line, "Unterminated string.");
    return;
  }
  auto literal = std::string(std::next(start), std::prev(current));
  addToken(TokenType::STRING, literal);
}

void Scanner::addNumberToken() {
  while (isNumeric(peek())) {
    consume();
  }
  if (peek() == '.' && isNumeric(peekNext())) {
    consume();
    while (isNumeric(peek())) {
      consume();
    }
  }
  auto literal = std::stod(std::string(start, current));
  addToken(TokenType::NUMBER, literal);
}

void Scanner::addIdentifierToken() {
  while (isAlphaNumeric(peek()))
    consume();
  auto lexeme = std::string(start, current);
  if (keywordMap.find(lexeme) != keywordMap.end()) {
    addToken(keywordMap[lexeme]);
    return;
  }
  addToken(TokenType::IDENTIFIER);
}

void Scanner::addToken(TokenType type) { addToken(type, ""); }

void Scanner::addToken(TokenType type,
                       std::variant<bool, double, std::string> literal) {
  auto lexeme = std::string(start, current);
  tokens.push_back(Token(lexeme, type, literal, line));
}

char Scanner::consume() {
  auto c = *current;
  std::advance(current, 1);
  return c;
}

bool Scanner::matchAndConsume(char expectedChar) {
  if (isAtEnd()) {
    return false;
  }
  if (peek() == expectedChar) {
    consume();
    return true;
  }
  return false;
}

char Scanner::peek() const {
  if (current == source.end()) {
    return '\0';
  }
  return *current;
}

char Scanner::peekNext() const {
  if (std::next(current) == source.end()) {
    return '\0';
  }
  return *std::next(current);
}

bool Scanner::isAtEnd() const {
  return (current == source.end() || peek() == '\0');
}

bool Scanner::isNumeric(char c) {
  if (c >= '0' && c <= '9') {
    return true;
  } else {
    return false;
  }
}

bool Scanner::isAlpha(char c) {
  if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_')) {
    return true;
  } else {
    return false;
  }
}

bool Scanner::isAlphaNumeric(char c) { return isAlpha(c) || isNumeric(c); }

std::unordered_map<std::string, TokenType> Scanner::keywordMap = [] {
  std::unordered_map<std::string, TokenType> keywordMap;
  keywordMap["and"] = TokenType::AND;
  keywordMap["class"] = TokenType::CLASS;
  keywordMap["else"] = TokenType::ELSE;
  keywordMap["false"] = TokenType::FALSE;
  keywordMap["for"] = TokenType::FOR;
  keywordMap["fun"] = TokenType::FUN;
  keywordMap["if"] = TokenType::IF;
  keywordMap["nil"] = TokenType::NIL;
  keywordMap["or"] = TokenType::OR;
  keywordMap["print"] = TokenType::PRINT;
  keywordMap["return"] = TokenType::RETURN;
  keywordMap["super"] = TokenType::SUPER;
  keywordMap["this"] = TokenType::THIS;
  keywordMap["true"] = TokenType::TRUE;
  keywordMap["var"] = TokenType::VAR;
  keywordMap["while"] = TokenType::WHILE;
  return keywordMap;
}();
