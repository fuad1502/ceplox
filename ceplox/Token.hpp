#pragma once

#include <string>
class Token {
  friend std::ostream &operator<<(std::ostream &stream, const Token &token);

private:
  std::string name;
};
