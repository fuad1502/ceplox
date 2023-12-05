#pragma once
#include <string>

class Ceplox {
public:
  void static runFile(char *file_name);
  void static runPrompt();
  void static run(std::string source);

private:
  static bool hadError;
  void static error(int line, std::string message);
  void static report(int line, std::string where, std::string message);
};
