#pragma once
#include<iostream>
#include"Token.h"
#include"LexialAnalyzer.h"
class Parser {
private:
    LexialAnalyzer lexer_;
    Token token_;
    std::ostream& result_out_;

    void startParse();
    Token match(EnumTokenType t);
    Token match(Token t);
    
    void error();
    void error(const char* message);
    void error(const char* message, EnumTokenType type);

    void parse_function();

public:
    Parser(std::istream& input_stream, std::ostream& output_stream);
    ~Parser();
    void parse();
};
