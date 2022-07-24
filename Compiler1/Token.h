#pragma once
#include<string>
#include<iostream>

enum class EnumTokenType {
    T_DATATYPE,
    T_LITERAL_INT,
    T_VARIABLE,

    T_OPERATION_UN,
    T_OPERATION_BIN,
    T_OPERATION_BOTH, // can be unary or binary

    T_ASSIGN,
    T_COLON,

    T_PAREN_L,
    T_PAREN_R,
    T_BRACE_L,
    T_BRACE_R,

    T_SEMICOLON,
    T_EOF,

    T_IF,
    T_ELSE,
    T_WHILE,
    T_FOR,
    T_DO,
    T_GOTO,
    T_LABEL,

    T_READ,
    T_WRITE,
    T_WRITEC,

    T_ERROR_ON_READER,
    T_ERROR_ON_ANALYZER,
};

class Token {
private:
    EnumTokenType type_;
    std::string val_;
public:
    explicit Token(EnumTokenType type);
    explicit Token(EnumTokenType type, char val);
    explicit Token(EnumTokenType type, std::string const &val);
    explicit Token(EnumTokenType type, std::string &&val);
    Token(Token const &t);
    Token &operator=(Token const &t);
    ~Token();
    std::string &&move_string() noexcept;
    bool operator==(Token const &t) const;
    bool typeIsEquals(EnumTokenType type) const;
    bool typeIsEquals(Token const &t) const;
    bool stringIsEquals(char const *str) const;
    friend std::ostream &operator<<(std::ostream &ostr, Token const &t);

    constexpr static const char *STR_INT{"int"};
};