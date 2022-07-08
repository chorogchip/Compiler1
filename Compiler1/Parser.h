#pragma once
#include<iostream>
#include"Token.h"
#include"LexialAnalyzer.h"
class Parser {
private:
    LexialAnalyzer lexer_;
    Token token_;
    void startParse();
    void match(EnumTokenType t);
    void match(Token t);
    void error();
    void error(const char* message);
public:
    Parser(std::istream& input_stream);
    ~Parser();
    void parse();
};

