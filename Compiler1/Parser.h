#pragma once
#include<iostream>
#include <stdexcept>
#include"ParseTreeComponents.h"
#include"Token.h"
#include"LexialAnalyzer.h"
class Parser {
private:
    LexialAnalyzer &lexer_;
    Token token_;
    std::ostream &errout_;
    psc::Program program_;

    void start_parse();
    Token match(EnumTokenType type);
    Token match(Token token);
    void get_next_token();
    std::string get_str_and_get_next_token();
    
    void error();
    void error(char const *message);
    void error(char const *message, EnumTokenType type);
    void error(char const *message, Token token);

    psc::Command parse_command();
    psc::Block parse_block();
    psc::Declare parse_decl();
    psc::Label parse_label();
    psc::Statement parse_stmt();
    psc::STAssign parse_assign(bool has_semicolon = true);
    psc::STIf parse_if();
    psc::STWhile parse_while();
    psc::STFor parse_for();
    psc::STRead parse_read();
    psc::STWrite parse_write();
    psc::STWritec parse_writec();
    psc::STGoto parse_goto();
    psc::Var parse_var();
    psc::ID parse_id();
    psc::Num parse_int();
    psc::Num parse_num();
    psc::Expr parse_expr();
    psc::Expr parse_expr1();
    psc::Expr parse_expr2();
    psc::Expr parse_expr3();
    psc::Expr parse_expr4();
    psc::Expr parse_expr5();
    psc::Expr parse_expr6();
    psc::Expr parse_expr7();
    psc::Expr parse_expr8();
    psc::Expr parse_expr9();
    psc::Expr parse_expr10();
    psc::Expr parse_expr11();
    psc::Expr parse_expr12();

public:
    Parser(LexialAnalyzer &lexer, std::ostream &error_output_stream);
    bool parse();
    psc::Program &&get_program();
};
