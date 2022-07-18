#include "Parser.h"

Parser::Parser(std::istream& input_stream, std::ostream& output_stream)
    : lexer_(input_stream), token_(EnumTokenType::T_ERROR_ON_ANALYZER),
      result_out_(output_stream) {
}
Parser::~Parser() {}

void Parser::startParse() {
    lexer_.startReading();
    token_ = lexer_.getToken();
}
Token Parser::match(EnumTokenType type) {
    Token pre_t = token_;
    if (token_.typeIsEquals(type))
        token_ = lexer_.getToken();
    else error("type of current token does not match as expected.", type);
    return pre_t;
}
Token Parser::match(Token t) {
    Token pre_t = token_;
    if (token_ == t)
        token_ = lexer_.getToken();
    else if (token_.typeIsEquals(t))
        error("type of current token matches as expected,\nbut data does not mach.");
    else
        error("type of current token does not match as expected.");
    return pre_t;
}
void Parser::error() {
    result_out_ << "error occured in parser.\ncurrent token : " << token_ << std::endl;
    throw token_;
}
void Parser::error(const char* message) {
    result_out_ << "error occured in parser.\n" << message <<
        "\ncurrent token : " << token_ << std::endl;
    throw token_;
}
void Parser::error(const char* message, EnumTokenType type) {
    result_out_ << "error occured in parser.\n" << message <<
        "\ntype : " << (int)type <<
        "\ncurrent token : " << token_ << std::endl;
    throw token_;
}


void Parser::parse_function() {
    match(EnumTokenType::T_FUNCTION);
    Token t = match(EnumTokenType::T_VARIABLE);
}













void Parser::parse() {
    this->startParse();
    do {
        token_ = lexer_.getToken();
        
    } while (!token_.typeIsEquals(EnumTokenType::T_EOF));
}