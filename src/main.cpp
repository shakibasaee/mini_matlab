// File: src/main.cpp
#include <fstream>
#include <iostream>
#include <iterator>
#include "lexer.h"

using namespace mini;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: mini_matlab <source.mml>\n";
        return EXIT_FAILURE;
    }

    const std::string filename = argv[1];
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: cannot open file '" << filename << "'\n";
        return EXIT_FAILURE;
    }

    const std::string source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    auto lexer = Lexer(source);
    std::cout << "=== Lexical Analysis of " << filename << " ===\n";

    for (auto token = lexer.next_token(); token.type != TokenType::EndOfFile; token = lexer.next_token()) {
        std::cout << token_type_to_string(token.type)
                  << "\t'" << token.lexeme << "'"
                  << "\t(" << token.line << ":" << token.column << ")\n";
    }

    std::cout << "=== End of Tokens ===\n";
    return EXIT_SUCCESS;
}
