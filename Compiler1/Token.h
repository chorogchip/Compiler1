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
    Token(EnumTokenType type);
    Token(EnumTokenType type, char val);
    Token(EnumTokenType type, std::string& val);
    Token(EnumTokenType type, std::string&& val);
    Token(const Token& t);
    Token& operator=(const Token& t);
    ~Token();
    bool operator==(const Token& t) const;
    bool typeIsEquals(EnumTokenType type) const;
    bool typeIsEquals(const Token& t) const;
    bool stringIsEquals(const char* str) const;
    friend std::ostream& operator<<(std::ostream& ostr, const Token& t);
};