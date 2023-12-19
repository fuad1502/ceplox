#pragma once

#include "Token.hpp"
#include <string>
#include <unordered_map>
#include <vector>

class Scanner {
public:
  Scanner(std::string source);
  Scanner(Scanner &&) = default;
  Scanner(const Scanner &) = default;
  Scanner &operator=(Scanner &&) = default;
  Scanner &operator=(const Scanner &) = default;
  ~Scanner();
  std::vector<Token> scanTokens();

private:
  std::string source;
  std::string::const_iterator current;
  std::string::const_iterator start;
  std::vector<Token> tokens;
  int line;

  void scanToken();
  void addToken(TokenType type);
  void addToken(TokenType type,
                std::variant<bool, double, std::string> literal);
  void addStringToken();
  void addNumberToken();
  void addIdentifierToken();
  char consume();
  bool matchAndConsume(char c);
  void consumeSingleLineComment();
  void consumeMultiLineComment();

  char peek() const;
  char peekNext() const;
  bool isAtEnd() const;

  static std::unordered_map<std::string, TokenType> keywordMap;

  static bool isNumeric(char c);
  static bool isAlpha(char c);
  static bool isAlphaNumeric(char c);
};
