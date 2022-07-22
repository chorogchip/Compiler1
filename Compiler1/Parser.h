#pragma once
#include<iostream>
#include <stdexcept>
#include"ParseTreeComponents.h"
#include"Token.h"
#include"LexialAnalyzer.h"
class Parser {
private:
    LexialAnalyzer& lexer_;
    Token token_;
    std::ostream& errout_;
    psc::Program program_;

    void start_parse();
    Token match(EnumTokenType type);
    Token match(Token token);
    void get_next_token();
    
    void error();
    void error(const char* message);
    void error(const char* message, EnumTokenType type);
    void error(const char* message, Token token);

    psc::Command parse_command();
    psc::Expr parse_expr();

public:
    Parser(LexialAnalyzer& lexer, std::ostream& error_output_stream);
    ~Parser() = default;
    void parse();
    psc::Program&& get_program();
};
