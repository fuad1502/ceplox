#pragma once

#include "Token.hpp"
#include <string>
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
};
