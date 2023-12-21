#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class ExprGenerator {
public:
  static void generate(std::string grammarFilePath, std::string outputFilePath);

private:
  static void generate(std::vector<std::string> grammar,
                       std::string outputFilePath);
  static void generateClass(std::string className,
                            std::vector<std::string> fields,
                            std::ofstream &outputFile);
  static void generateAbstractVisitor(std::ofstream &outputFile,
                                      std::vector<std::string> grammar);
  static std::vector<std::string> parseGrammar(std::string grammarFilePath);
  static std::vector<std::string> parseFields(std::string fields);
  static std::string name(std::string field);
};

void ExprGenerator::generate(std::string grammarFilePath,
                             std::string outputFilePath) {
  std::vector<std::string> grammar = parseGrammar(grammarFilePath);
  generate(grammar, outputFilePath);
}

void ExprGenerator::generate(std::vector<std::string> grammar,
                             std::string outputFilePath) {
  // Generate Expr header file
  std::ofstream headerFile(outputFilePath + "/Expr.hpp");
  // Guard
  headerFile << "#pragma once" << std::endl;
  // Header
  headerFile << "#include \"Token.hpp\"" << std::endl;
  headerFile << "#include <memory>" << std::endl;
  headerFile << "#include <any>" << std::endl;
  headerFile << std::endl;
  // Forward declaration
  headerFile << "class ExprVisitor;" << std::endl;
  headerFile << std::endl;
  // Base Expr class
  headerFile << "class Expr {" << std::endl;
  headerFile << "public:" << std::endl;
  headerFile << "  virtual std::any accept(ExprVisitor &visitor) const = 0;"
             << std::endl;
  headerFile << "};" << std::endl;
  headerFile << std::endl;
  // Subclasses
  for (auto rule : grammar) {
    auto className = rule.substr(0, rule.find(":"));
    boost::trim(className);
    auto fields = rule.substr(rule.find(":") + 1);
    boost::trim(fields);
    generateClass(className, parseFields(fields), headerFile);
    headerFile << std::endl;
  }

  // Generate ExprVisitor interface
  std::ofstream visitorHeaderFile(outputFilePath + "/ExprVisitor.hpp");
  // Guard
  visitorHeaderFile << "#pragma once" << std::endl;
  // Header
  visitorHeaderFile << "#include \"Expr.hpp\"" << std::endl;
  visitorHeaderFile << std::endl;
  generateAbstractVisitor(visitorHeaderFile, grammar);

  // Generate Expr source file
  std::ofstream sourceFile(outputFilePath + "/Expr.cpp");
  sourceFile << "#include \"Expr.hpp\"" << std::endl;
  sourceFile << "#include \"ExprVisitor.hpp\"" << std::endl;
  sourceFile << std::endl;
  for (auto rule : grammar) {
    auto className = rule.substr(0, rule.find(":"));
    boost::trim(className);
    sourceFile << "std::any " << name(className)
               << "Expr::accept(ExprVisitor &visitor) const {" << std::endl;
    sourceFile << "  return visitor.visit" << className << "(*this);"
               << std::endl;
    sourceFile << "}" << std::endl;
    sourceFile << std::endl;
  }
}

void ExprGenerator::generateClass(std::string className,
                                  std::vector<std::string> fields,
                                  std::ofstream &outputFile) {
  outputFile << "class " << className << "Expr : public Expr {" << std::endl;
  outputFile << "public:" << std::endl;
  // Declare constructor
  outputFile << "  " << className << "Expr(";
  // Constructor parameters
  for (auto field : fields) {
    outputFile << field << ", ";
  }
  outputFile.seekp(-2, std::ios_base::end);
  outputFile << ")" << std::endl;
  // Constructor initializer list
  outputFile << "      : ";
  for (auto field : fields) {
    outputFile << name(field) << "(std::move(" << name(field) << ")), ";
  }
  outputFile.seekp(-2, std::ios_base::end);
  outputFile << "{};" << std::endl;
  // Class members
  for (auto field : fields) {
    outputFile << "  " << field << ";" << std::endl;
  }
  // Visitor accept method
  outputFile << "  std::any accept(ExprVisitor &visitor) const override;"
             << std::endl;
  outputFile << "};" << std::endl;
}

void ExprGenerator::generateAbstractVisitor(std::ofstream &outputFile,
                                            std::vector<std::string> grammar) {
  outputFile << "class ExprVisitor {" << std::endl;
  outputFile << "public:" << std::endl;
  for (auto rule : grammar) {
    auto className = rule.substr(0, rule.find(":"));
    boost::trim(className);
    outputFile << "  virtual std::any visit" << className << "(const "
               << name(className) << "Expr &expression) = 0;" << std::endl;
  }
  outputFile << "};" << std::endl;
}

std::vector<std::string>
ExprGenerator::parseGrammar(std::string grammarFilePath) {
  std::ifstream grammarFile(grammarFilePath);
  std::string line;
  std::vector<std::string> grammar;
  while (std::getline(grammarFile, line)) {
    grammar.push_back(line);
  }
  return grammar;
}

std::vector<std::string> ExprGenerator::parseFields(std::string fields) {
  std::vector<std::string> fieldsVector;
  boost::split(fieldsVector, fields, boost::is_any_of(","));
  for (auto &field : fieldsVector) {
    boost::trim(field);
  }
  return fieldsVector;
}

std::string ExprGenerator::name(std::string field) {
  return field.substr(field.find(" ") + 1);
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cout << "Usage: ExprGenerator <grammarFile> <outputPath>" << std::endl;
    return 1;
  }
  std::string grammarFilePath = argv[1];
  std::string outputFilePath = argv[2];
  ExprGenerator::generate(grammarFilePath, outputFilePath);
  return 0;
}
