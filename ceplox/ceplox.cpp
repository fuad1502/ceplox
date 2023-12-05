#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Ceplox {
public:
  void static runFile(char *file_name);
  void static runPrompt();
  void static run(std::string source);

private:
};

void Ceplox::runFile(char *file_name) {
  std::ifstream ifs(file_name);
  std::stringstream ss;
  ss << ifs.rdbuf();
  auto source = ss.str();
  run(source);
}

void Ceplox::runPrompt() {
  while (true) {
    std::cout << "> ";
    std::string line;
    if (std::getline(std::cin, line).eof())
      break;
    run(line);
  }
}

void Ceplox::run(std::string source) {
  std::cout << "Processing : " << source << std::endl;
}
