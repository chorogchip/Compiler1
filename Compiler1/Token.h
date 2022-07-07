#pragma once
#include<string>

enum class EnumTokenType {
    T_DATATYPE,
    T_LITERAL_INT,
    T_VARIABLE,

    T_OPERATION_UN,
    T_OPERATION_BIN,
    T_OPERATION_TRI,

    T_PAREN_L,
    T_PAREN_R,
    T_BRACKET_L,
    T_BRACKET_R,
    T_BRACE_L,
    T_BRACE_R,

    T_COMMA,
    T_SEMICOLON,
    T_EOF,

    T_IF,
    T_ELSE,
    T_FOR,
    T_WHILE,
    T_DO,

    T_FUNCTION,
    T_RETURN,

    T_READ,
    T_WRITE,

};
class Token {
private:
    EnumTokenType type_;
    std::string val_;
public:
    Token(EnumTokenType type, std::string& val);
    Token(EnumTokenType type, std::string&& val);
    Token(const Token& t);
    Token& operator=(const Token& t);
    ~Token();
    bool operator==(const Token& t) const;
    bool typeIsEquals(EnumTokenType type) const;
};