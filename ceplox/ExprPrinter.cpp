#include "ExprPrinter.hpp"
#include <iostream>

void ExprPrinter::print(const pExpr &expr) {
  expr->accept(*this);
  std::cout << std::endl;
}

std::any ExprPrinter::visitBinary(const BinaryExpr &expression) {
  std::cout << "(" << expression.op.getLexeme() << " ";
  expression.left->accept(*this);
  std::cout << " ";
  expression.right->accept(*this);
  std::cout << ")";
  return {};
}

std::any ExprPrinter::visitGrouping(const GroupingExpr &expression) {
  std::cout << "(group ";
  expression.expression->accept(*this);
  std::cout << ")";
  return {};
}

std::any ExprPrinter::visitLiteral(const LiteralExpr &expression) {
  std::cout << expression.value;
  return {};
}

std::any ExprPrinter::visitUnary(const UnaryExpr &expression) {
  std::cout << "(" << expression.op.getLexeme() << " ";
  expression.right->accept(*this);
  std::cout << ")";
  return {};
}

std::any ExprPrinter::visitTernary(const TernaryExpr &expression) {
  std::cout << "(? ";
  expression.condition->accept(*this);
  std::cout << " ";
  expression.thenBranch->accept(*this);
  std::cout << " ";
  expression.elseBranch->accept(*this);
  std::cout << ")";
  return {};
}
