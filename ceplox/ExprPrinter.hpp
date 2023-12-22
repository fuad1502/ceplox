#include "Expr.hpp"
#include "ExprVisitor.hpp"

class ExprPrinter : public ExprVisitor {
public:
  void print(const pExpr &expr);
  std::any visitBinary(const BinaryExpr &expr) override;
  std::any visitGrouping(const GroupingExpr &expr) override;
  std::any visitLiteral(const LiteralExpr &expr) override;
  std::any visitUnary(const UnaryExpr &expr) override;
  std::any visitTernary(const TernaryExpr &expr) override;

private:
};
