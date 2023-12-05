#include "Token.hpp"

std::ostream &operator<<(std::ostream &stream, const Token &token) {
  stream << token.name;
  return stream;
}
