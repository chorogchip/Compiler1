#include "Parser.h"

Parser::Parser(std::istream& input_stream)
    : lexer_(input_stream), token_(EnumTokenType::T_ERROR_ON_ANALYZER) {
    
}
Parser::~Parser() {}

void Parser::startParse() {
    lexer_.startReading();
    token_ = lexer_.getToken();
}
void Parser::match(EnumTokenType type) {
    if (token_.typeIsEquals(type))
        token_ = lexer_.getToken();
    else error("type of current token does not match as expected.");
}
void Parser::match(Token t) {
    if (token_ == t)
        token_ = lexer_.getToken();
    else if (token_.typeIsEquals(t))
        error("type of current token matches as expected,\nbut data does not mach.");
    else
        error("type of current token does not match as expected.");
}
void Parser::error() {
    std::cout << "error occured in parser.\ncurrent token : " << token_ << std::endl;
    throw token_;
}
void Parser::error(const char* message) {
    std::cout << "error occured in parser.\n" << message <<
        "\ncurrent token : " << token_ << std::endl;
    throw token_;
}
void Parser::parse() {
    this->startParse();
    do {
        token_ = lexer_.getToken();
        // TODO
    } while (!token_.typeIsEquals(EnumTokenType::T_EOF));
}