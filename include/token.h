#pragma once
#include <string>
#include <optional>
#include <unordered_map>

enum class TokenType {
    EndOfFile, Number, Identifier, Keyword,
    Plus, Minus, Star, Slash,
    Assign, Semi, Comma,
    LParen, RParen, LBracket, RBracket,
    Less, Greater, LessEqual, GreaterEqual,
    EqualEqual, NotEqual,
    Unknown
};

struct Token {
    TokenType type = TokenType::Unknown;
    std::string lexeme;
    int line = 1;
    int column = 1;
    std::optional<double> number_value;

    Token() = default;
    Token(TokenType t, std::string l, int ln, int col)
        : type(t), lexeme(std::move(l)), line(ln), column(col) {}
};

inline std::string token_type_to_string(TokenType t) {
    static const std::unordered_map<TokenType, std::string> names = {
        {TokenType::EndOfFile, "EOF"}, {TokenType::Number, "Number"},
        {TokenType::Identifier, "Identifier"}, {TokenType::Keyword, "Keyword"},
        {TokenType::Plus, "Plus"}, {TokenType::Minus, "Minus"},
        {TokenType::Star, "Star"}, {TokenType::Slash, "Slash"},
        {TokenType::Assign, "Assign"}, {TokenType::Semi, "Semi"},
        {TokenType::Comma, "Comma"}, {TokenType::LParen, "LParen"},
        {TokenType::RParen, "RParen"}, {TokenType::LBracket, "LBracket"},
        {TokenType::RBracket, "RBracket"}, {TokenType::Less, "Less"},
        {TokenType::Greater, "Greater"}, {TokenType::LessEqual, "LessEqual"},
        {TokenType::GreaterEqual, "GreaterEqual"},
        {TokenType::EqualEqual, "EqualEqual"}, {TokenType::NotEqual, "NotEqual"},
        {TokenType::Unknown, "Unknown"}
    };
    if (auto it = names.find(t); it != names.end())
        return it->second;
    return "Unknown";
}
