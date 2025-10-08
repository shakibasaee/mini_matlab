#pragma once
#include "token.h"
#include <string>
#include <vector>

namespace mini {

class Lexer {
public:
    explicit Lexer(std::string src);

    Token next();              // get next token
    Token peek(size_t ahead = 1) const;
    const std::vector<Token>& tokens() const { return tokens_; }

private:
    Token scan_one();

    std::string source;
    size_t pos = 0;
    int line = 1;
    int col = 1;
    size_t current = 0;

    std::vector<Token> tokens;

    char curr() const;
    char look(size_t offset = 1) const;
    bool end() const;
    void step();

    void skip_ws_and_comments();
    Token read_number();
    Token read_identifier();
};

}
