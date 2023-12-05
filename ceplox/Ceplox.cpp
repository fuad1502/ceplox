#include "Ceplox.hpp"
#include "Scanner.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

bool Ceplox::hadError = false;

void Ceplox::runFile(char *file_name) {
  std::ifstream ifs(file_name);
  std::stringstream ss;
  ss << ifs.rdbuf();
  auto source = ss.str();
  run(source);
  if (hadError)
    std::exit(65);
}

void Ceplox::runPrompt() {
  while (true) {
    std::cout << "> ";
    std::string line;
    if (std::getline(std::cin, line).eof())
      break;
    run(line);
    hadError = false;
  }
}

void Ceplox::run(std::string source) {
  Scanner scanner(source);
  auto tokens = scanner.scanTokens();
  for (auto &token : tokens) {
    std::cout << token << std::endl;
  }
}

void Ceplox::error(int line, std::string message) { report(line, "", message); }

void Ceplox::report(int line, std::string where, std::string message) {
  std::cerr << "[line " << line << "] Error" << where << ": " << message
            << std::endl;
  hadError = true;
}
