#include "lexer.h"
#include <cctype>
#include <iostream>

namespace mini {

Lexer::Lexer(const std::string& input)
    : input_(input), pos_(0), line_(1), col_(1) {}


char Lexer::current_char() const {
    if (pos_ >= input_.size()) return '\0';
    return input_[pos_];
}

char Lexer::peek_char() const {
    if (pos_ + 1 >= input_.size()) return '\0';
    return input_[pos_ + 1];
}

void Lexer::advance() {
    if (pos_ < input_.size()) {
        if (input_[pos_] == '\n') { line_++; col_ = 1; }
        else col_++;
        pos_++;
    }
}

void Lexer::skip_whitespace() {
    while (std::isspace(current_char())) advance();
}


std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (true) {
        skip_whitespace();
        char c = current_char();
        if (c == '\0') {
            tokens.emplace_back(TokenType::EndOfFile, "", line_, col_);
            break;
        }

        Token token = match_operator_or_delimiter();
        if (token.type != TokenType::Unknown) {
            tokens.push_back(token);
            continue;
        }

        if (std::isdigit(c) || (c == '.' && std::isdigit(peek_char()))) {
            tokens.push_back(read_number());
            continue;
        }

        if (std::isalpha(c) || c == '_') {
            tokens.push_back(read_identifier_or_keyword());
            continue;
        }

        // unknown character
        std::cerr << "Warning [Line " << line_ << ", Col " << col_ << "]: Unknown symbol '" << c << "'\n";
        std::string lexeme(1, c);
        advance();
        tokens.emplace_back(TokenType::Unknown, lexeme, line_, col_);
    }

    return tokens;
}


Token Lexer::match_operator_or_delimiter() {
    char c = current_char();
    int start_line = line_, start_col = col_;

    auto make = [&](TokenType t, std::string v) {
        advance();
        return Token(t, std::move(v), start_line, start_col);
    };

    switch (c) {
        case '(': return make(TokenType::LParen, "(");
        case ')': return make(TokenType::RParen, ")");
        case '[': return make(TokenType::LBracket, "[");
        case ']': return make(TokenType::RBracket, "]");
        case '{': return make(TokenType::LBrace, "{");
        case '}': return make(TokenType::RBrace, "}");
        case ';': return make(TokenType::Semicolon, ";");
        case '+': return make(TokenType::Plus, "+");
        case '-': return make(TokenType::Minus, "-");
        case '*': return make(TokenType::Star, "*");
        case '/': return make(TokenType::Slash, "/");
    }

    if (c == '=') {
        if (peek_char() == '=') { advance(); advance(); return Token(TokenType::Equal, "==", start_line, start_col); }
        return make(TokenType::Assign, "=");
    }

    if (c == '<') {
        if (peek_char() == '=') { advance(); advance(); return Token(TokenType::LessEqual, "<=", start_line, start_col); }
        return make(TokenType::Less, "<");
    }

    if (c == '>') {
        if (peek_char() == '=') { advance(); advance(); return Token(TokenType::GreaterEqual, ">=", start_line, start_col); }
        return make(TokenType::Greater, ">");
    }

    if (c == '!') {
        if (peek_char() == '=') { advance(); advance(); return Token(TokenType::NotEqual, "!=", start_line, start_col); }
        return make(TokenType::Not, "!");
    }

    return Token(TokenType::Unknown, "", line_, col_);
}


//Numbers
Token Lexer::read_number() {
    std::string num;
    int start_line = line_, start_col = col_;
    bool has_dot = false;

    while (std::isdigit(current_char()) || current_char() == '.') {
        if (current_char() == '.') {
            if (has_dot) break;
            has_dot = true;
        }
        num += current_char();
        advance();
    }

    return Token(TokenType::Number, num, start_line, start_col);
}


//Keywords
Token Lexer::read_identifier_or_keyword() {
    std::string word;
    int start_line = line_, start_col = col_;

    while (std::isalnum(current_char()) || current_char() == '_') {
        word += current_char();
        advance();
    }

    if (word == "print") return Token(TokenType::KeywordPrint, word, start_line, start_col);
    if (word == "if") return Token(TokenType::KeywordIf, word, start_line, start_col);
    if (word == "else") return Token(TokenType::KeywordElse, word, start_line, start_col);

    return Token(TokenType::Identifier, word, start_line, start_col);
}

}
