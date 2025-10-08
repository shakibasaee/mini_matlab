#pragma once
#include <string>
#include <vector>

enum class TokenType {
    Identifier, Number, KeywordPrint, KeywordIf, KeywordElse,
    Plus, Minus, Star, Slash, Assign,
    Semicolon, LParen, RParen, LBrace, RBrace,
    Equal, NotEqual, Greater, Less, GreaterEqual, LessEqual,
    EndOfFile
};

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    explicit Lexer(const std::string& input);
    std::vector<Token> tokenize();

private:
    std::string input;
    size_t pos;
    char currentChar();
    void advance();
    void skipWhitespace();
    Token nextToken();
};
