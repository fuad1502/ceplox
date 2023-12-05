#include "Ceplox.hpp"

int main(int argc, char *argv[]) {
  if (argc > 2) {
    std::printf("Usage: ceplox [script]\n");
    exit(64);
  } else if (argc == 2) {
    auto file_name = argv[1];
    Ceplox::runFile(file_name);
  } else if (argc == 1) {
    Ceplox::runPrompt();
  }
}
