#include "Parser.h"

Parser::Parser(LexialAnalyzer& lexer, std::ostream& error_output_stream)
    : lexer_(lexer), token_(EnumTokenType::T_ERROR_ON_ANALYZER),
      errout_(error_output_stream) {
}
Parser::~Parser() {}

Token Parser::match(EnumTokenType type) {
    Token pre_t = token_;
    if (token_.typeIsEquals(type))
        get_next_token();
    else error("type of current token does not match as expected.", type);
    return pre_t;
}
Token Parser::match(Token token) {
    Token pre_t = token_;
    if (token_ == token)
        get_next_token();
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

void Parser::start_parse() {
    lexer_.startReading();
    get_next_token();
}
void Parser::parse() {
    start_parse();
    // <program> -> { <command> }
    while (!token_.typeIsEquals(EnumTokenType::T_EOF))
        parse_command();
}
void Parser::get_next_token() {
    token_ = lexer_.getToken();
}


void Parser::parse_command() {
    // <command> -> <decl> | <stmt> | <block>
    if (token_.typeIsEquals(EnumTokenType::T_BRACE_L)) {  // <block>
        // <block> -> '{' { <command> }  '}'
        get_next_token();
        while (!token_.typeIsEquals(EnumTokenType::T_BRACE_R))
            parse_command();
        match(EnumTokenType::T_BRACE_R);
    } else if (token_.typeIsEquals(EnumTokenType::T_DATATYPE)) {  // <decl>
        // <decl> -> <type> <id> : <number> ;
        get_next_token();
        match(EnumTokenType::T_VARIABLE);
        match(EnumTokenType::T_COLON);
        match(EnumTokenType::T_LITERAL_INT);
        match(EnumTokenType::T_SEMICOLON);
    } else {
        // <stmt> -> <assign> | <if> | <while> | <for> |
        // <read> | <write> | <writec> | <goto> | <label>
        if (token_.typeIsEquals(EnumTokenType::T_VARIABLE)) {  // <assign> | <label>
            get_next_token();
            if (token_.typeIsEquals(EnumTokenType::T_ASSIGN)) {  // <assign>
                // <assign> -> <id> = <expr> ;
                get_next_token();
                parse_expr();
                match(EnumTokenType::T_SEMICOLON);
            } else if (token_.typeIsEquals(EnumTokenType::T_COLON)) {  // <label>
                get_next_token();
            } else {
                error("token not matched : = or : is expected after name as assign or label statement");
            }
        } else if (token_.typeIsEquals(EnumTokenType::T_IF)) {  // <if>
            // <if> -> if '( <expr> ')' <command>
            get_next_token();
            match(EnumTokenType::T_PAREN_L);
            parse_expr();
            match(EnumTokenType::T_PAREN_R);
            parse_command();
            match(EnumTokenType::T_SEMICOLON);
        } else if (token_.typeIsEquals(EnumTokenType::T_WHILE)) {  // <while>
            // <while> -> while '( <expr> ')' <command>
            get_next_token();
            match(EnumTokenType::T_PAREN_L);
            parse_expr();
            match(EnumTokenType::T_PAREN_R);
            parse_command();
            match(EnumTokenType::T_SEMICOLON);
        } else if (token_.typeIsEquals(EnumTokenType::T_FOR)) {  // <for>
            // <for> -> for '(' <decl> ; <assign> ; <expr> ; <assign> ')' <command>
            get_next_token();
            match(EnumTokenType::T_PAREN_L);
            // <decl> ;
            get_next_token();
            match(EnumTokenType::T_VARIABLE);
            match(EnumTokenType::T_COLON);
            match(EnumTokenType::T_LITERAL_INT);
            match(EnumTokenType::T_SEMICOLON);
            // <assign> ;
            match(EnumTokenType::T_VARIABLE);
            match(EnumTokenType::T_ASSIGN);
            parse_expr();
            match(EnumTokenType::T_SEMICOLON);
            // <expr> ;
            parse_expr();
            match(EnumTokenType::T_SEMICOLON);
            // <assign>
            match(EnumTokenType::T_VARIABLE);
            match(EnumTokenType::T_ASSIGN);
            parse_expr();

            match(EnumTokenType::T_PAREN_R);
            parse_command();
            match(EnumTokenType::T_SEMICOLON);
        } else if (token_.typeIsEquals(EnumTokenType::T_READ)) {  // <read>
            // <read> -> read <id> ;
            get_next_token();
            match(EnumTokenType::T_VARIABLE);
            match(EnumTokenType::T_SEMICOLON);
        } else if (token_.typeIsEquals(EnumTokenType::T_WRITE)) {  // <write>
            // <write> -> write <expr> ;
            get_next_token();
            parse_expr();
            match(EnumTokenType::T_SEMICOLON);
        } else if (token_.typeIsEquals(EnumTokenType::T_WRITEC)) {  // <writec>
            // <writec> -> writec <expr> ;
            get_next_token();
            parse_expr();
            match(EnumTokenType::T_SEMICOLON);
        } else if (token_.typeIsEquals(EnumTokenType::T_GOTO)) {  // <goto>
            // <goto> -> goto <id> ;
            get_next_token();
            Token label_name = match(EnumTokenType::T_VARIABLE);
            match(EnumTokenType::T_SEMICOLON);
        } else {
            error("token not matched : command is expected");
        }
    }
}

void Parser::parse_expr() {

}