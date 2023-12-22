#include "Expr.hpp"
#include "Token.hpp"
#include <vector>

class Parser {
public:
  Parser(std::vector<Token> &&tokens);
  std::optional<pExpr> parse();

private:
  std::vector<Token> tokens;
  std::vector<Token>::iterator current;

  std::optional<pExpr> expression();
  std::optional<pExpr> comma();
  std::optional<pExpr> ternary();
  std::optional<pExpr> equality();
  std::optional<pExpr> comparison();
  std::optional<pExpr> term();
  std::optional<pExpr> factor();
  std::optional<pExpr> unary();
  std::optional<pExpr> primary();

  bool isAtEnd() const;
  Token peek() const;
  bool match(const std::vector<TokenType> &tokenTypes) const;

  Token consume();
};
