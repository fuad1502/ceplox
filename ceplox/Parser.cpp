#include "Parser.hpp"
#include "Ceplox.hpp"
#include "Expr.hpp"
#include "TokenType.hpp"
#include <memory>
#include <optional>

Parser::Parser(std::vector<Token> &&tokens) : tokens(std::move(tokens)) {
  current = this->tokens.begin();
}

std::optional<pExpr> Parser::parse() { return expression(); }

std::optional<pExpr> Parser::expression() { return ternary(); }

std::optional<pExpr> Parser::ternary() {
  auto opt = equality();
  if (!opt)
    return std::nullopt;
  auto expr = std::move(opt.value());

  if (match(std::vector{TokenType::QUESTION})) {
    consume();
    auto opt = expression();
    if (!opt)
      return std::nullopt;
    auto thenExpr = std::move(opt.value());
    if (!match(std::vector{TokenType::COLON})) {
      Ceplox::error(peek().getLine(), "Expected colon");
      return std::nullopt;
    }
    consume();
    auto opt2 = expression();
    if (!opt2)
      return std::nullopt;
    auto elseExpr = std::move(opt2.value());
    expr = std::unique_ptr<Expr>(new TernaryExpr(
        std::move(expr), std::move(thenExpr), std::move(elseExpr)));
  }

  return expr;
}

// equality → comparison ( ( "!=" | "==" ) comparison )* ;
std::optional<pExpr> Parser::equality() {
  auto opt = comparison();
  if (!opt)
    return std::nullopt;
  auto expr = std::move(opt.value());

  std::vector<TokenType> matchingToken{TokenType::EQUAL_EQUAL,
                                       TokenType::BANG_EQUAL};

  while (match(matchingToken)) {
    auto op = consume();
    auto opt = comparison();
    if (!opt)
      return std::nullopt;
    auto rightExpr = std::move(opt.value());
    expr = std::unique_ptr<Expr>(
        new BinaryExpr(std::move(expr), op, std::move(rightExpr)));
  }

  return expr;
}

// comparison → term ( ( ">= " | "> " | "<= " | "< " ) term )* ;
std::optional<pExpr> Parser::comparison() {
  auto opt = term();
  if (!opt)
    return std::nullopt;
  auto expr = std::move(opt.value());

  std::vector<TokenType> matchingToken{TokenType::GREATER,
                                       TokenType::GREATER_EQUAL,
                                       TokenType::LESS, TokenType::LESS_EQUAL};

  while (match(matchingToken)) {
    auto op = consume();
    auto opt = term();
    if (!opt)
      return std::nullopt;
    auto rightExpr = std::move(opt.value());
    expr = std::unique_ptr<Expr>(
        new BinaryExpr(std::move(expr), op, std::move(rightExpr)));
  }

  return expr;
}

// term → factor ( ( "-" | "+" ) factor )* ;
std::optional<pExpr> Parser::term() {
  auto opt = factor();
  if (!opt)
    return std::nullopt;
  auto expr = std::move(opt.value());

  std::vector<TokenType> matchingToken{TokenType::MINUS, TokenType::PLUS};

  while (match(matchingToken)) {
    auto op = consume();
    auto opt = factor();
    if (!opt)
      return std::nullopt;
    auto rightExpr = std::move(opt.value());
    expr = std::unique_ptr<Expr>(
        new BinaryExpr(std::move(expr), op, std::move(rightExpr)));
  }

  return expr;
}

// factor → unary ( ( "/" | "*" ) unary )* ;
std::optional<pExpr> Parser::factor() {
  auto opt = unary();
  if (!opt)
    return std::nullopt;
  auto expr = std::move(opt.value());

  std::vector<TokenType> matchingToken{TokenType::SLASH, TokenType::STAR};

  while (match(matchingToken)) {
    auto op = consume();
    auto opt = unary();
    if (!opt)
      return std::nullopt;
    auto rightExpr = std::move(opt.value());
    expr = std::unique_ptr<Expr>(
        new BinaryExpr(std::move(expr), op, std::move(rightExpr)));
  }

  return expr;
}

// unary -> ( "!" | "-") unary | primary ;
std::optional<pExpr> Parser::unary() {
  std::vector<TokenType> matchingToken{TokenType::BANG, TokenType::MINUS};

  if (match(matchingToken)) {
    auto op = consume();
    auto opt = unary();
    if (!opt)
      return std::nullopt;
    auto right = std::move(opt.value());
    auto expr = std::unique_ptr<Expr>(new UnaryExpr(op, std::move(right)));
    return expr;
  } else {
    return primary();
  }
}

std::optional<pExpr> Parser::primary() {
  std::vector<TokenType> matchingToken{TokenType::NUMBER, TokenType::STRING,
                                       TokenType::TRUE, TokenType::FALSE,
                                       TokenType::NIL};
  if (match(matchingToken)) {
    auto token = consume();
    auto expr =
        std::unique_ptr<Expr>(new LiteralExpr(token.getLiteral().value_or("")));
    return expr;
  } else if (match(std::vector{TokenType::LEFT_PAREN})) {
    consume();
    auto opt = expression();
    if (!opt)
      return std::nullopt;
    auto containedExpr = std::move(opt.value());
    if (!match(std::vector{TokenType::RIGHT_PAREN})) {
      Ceplox::error(peek().getLine(), "Expected right parantheses");
      return std::nullopt;
    }
    consume();
    auto expr =
        std::unique_ptr<Expr>(new GroupingExpr(std::move(containedExpr)));
    return expr;
  } else {
    Ceplox::error(peek().getLine(), "Expected expression");
    return std::nullopt;
  }
}

bool Parser::isAtEnd() const {
  return peek().getTokenType() == TokenType::END_OF_FILE;
}

Token Parser::peek() const { return *current; }

bool Parser::match(const std::vector<TokenType> &matchingTypes) const {
  auto type = peek().getTokenType();
  for (auto t : matchingTypes) {
    if (t == type) {
      return true;
    }
  }
  return false;
}

Token Parser::consume() {
  auto t = peek();
  if (!isAtEnd()) {
    std::advance(current, 1);
  }
  return t;
}
