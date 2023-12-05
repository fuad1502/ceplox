#include "Scanner.hpp"
#include <vector>

Scanner::Scanner(std::string source) { this->source = source; }

Scanner::~Scanner() {}

std::vector<Token> Scanner::scanTokens() { return std::vector<Token>(); }
