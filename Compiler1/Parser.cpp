#include "Parser.h"

Parser::Parser(LexialAnalyzer& lexer, std::ostream& error_output_stream)
    : lexer_(lexer), token_(EnumTokenType::T_ERROR_ON_ANALYZER),
      errout_(error_output_stream) {
}
Parser::~Parser() {}

Token Parser::match(EnumTokenType type) {
    Token pre_t = token_;
    if (token_.typeIsEquals(type))
        token_ = lexer_.getToken();
    else error("type of current token does not match as expected.", type);
    return pre_t;
}
Token Parser::match(Token token) {
    Token pre_t = token_;
    if (token_ == token)
        token_ = lexer_.getToken();
    else if (token_.typeIsEquals(token))
        error("type of current token matches as expected,\nbut data does not mach.", token);
    else
        error("type of current token does not match as expected.", token);
    return pre_t;
}
void Parser::error() {
    errout_ << "error occured in parser.\ncurrent token : " << token_ << std::endl;
    throw token_;
}
void Parser::error(const char* message) {
    errout_ << "error occured in parser.\n" << message <<
        "\ncurrent token : " << token_ << std::endl;
    throw token_;
}
void Parser::error(const char* message, EnumTokenType type) {
    errout_ << "error occured in parser.\n" << message <<
        "\ntype : " << (int)type <<
        "\ncurrent token : " << token_ << std::endl;
    throw token_;
}
void Parser::error(const char* message, Token token) {
    errout_ << "error occured in parser.\n" << message <<
        "\nexpected token : " << token <<
        "\ncurrent token : " << token_ << std::endl;
    throw token_;
}

void Parser::startParse() {
    lexer_.startReading();
    token_ = lexer_.getToken();
}
void Parser::parse() {
    startParse();
    while (!token_.typeIsEquals(EnumTokenType::T_EOF))
        parse_function();
}

void Parser::parse_function() {
    match(EnumTokenType::T_FUNCTION);
    match(EnumTokenType::T_DATATYPE);
    Token t = match(EnumTokenType::T_VARIABLE);
    match(EnumTokenType::T_PAREN_L);
    while (token_.typeIsEquals(EnumTokenType::T_DATATYPE)) {
        match(EnumTokenType::T_DATATYPE);
        Token t = match(EnumTokenType::T_VARIABLE);
    }
    match(EnumTokenType::T_PAREN_R);
    match(EnumTokenType::T_BRACKET_L);
    while (!token_.typeIsEquals(EnumTokenType::T_BRACE_R))
        parse_command();
    match(EnumTokenType::T_BRACKET_R);
}
void Parser::parse_command() {
    
}