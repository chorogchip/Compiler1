#pragma once
#include<iostream>
#include"Token.h"
#include"LexialAnalyzer.h"
class Parser {
private:
    LexialAnalyzer& lexer_;
    Token token_;
    std::ostream& errout_;

    void startParse();
    Token match(EnumTokenType type);
    Token match(Token token);
    
    void error();
    void error(const char* message);
    void error(const char* message, EnumTokenType type);
    void error(const char* message, Token token);

    void parse_function();
    void parse_command();

public:
    Parser(LexialAnalyzer& lexer, std::ostream& error_output_stream);
    ~Parser();
    void parse();
};
