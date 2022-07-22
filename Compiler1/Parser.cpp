#include "Parser.h"

// do not use this->method(). just use method(). cause method call is too much

Parser::Parser(LexialAnalyzer& lexer, std::ostream& error_output_stream):
    lexer_{lexer},
    token_{EnumTokenType::T_ERROR_ON_ANALYZER},
    errout_{error_output_stream},
    program_{}
{}

Token Parser::match(EnumTokenType type) {
    Token pre_t = {token_};
    if (token_.typeIsEquals(type))
        get_next_token();
    else error("type of current token does not match as expected.", type);
    return pre_t;
}
Token Parser::match(Token token) {
    Token pre_t = {token_};
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
    throw std::invalid_argument("");
}
void Parser::error(const char* message) {
    errout_ << "error occured in parser.\n" << message <<
        "\ncurrent token : " << token_ << std::endl;
    throw std::invalid_argument("");
}
void Parser::error(const char* message, EnumTokenType type) {
    errout_ << "error occured in parser.\n" << message <<
        "\ntype : " << (int)type <<
        "\ncurrent token : " << token_ << std::endl;
    throw std::invalid_argument("");
}
void Parser::error(const char* message, Token token) {
    errout_ << "error occured in parser.\n" << message <<
        "\nexpected token : " << token <<
        "\ncurrent token : " << token_ << std::endl;
    throw std::invalid_argument("");
}

void Parser::start_parse() {
    lexer_.startReading();
    get_next_token();
}
void Parser::parse() {
    start_parse();
    try {
        // <program> -> { <command> }
        while (!token_.typeIsEquals(EnumTokenType::T_EOF))
            parse_command();
    } catch (int e) {
        errout_ << "error occured in parse : " << e << std::endl;
    }
}
void Parser::get_next_token() {
    token_ = lexer_.getToken();
}
psc::Program&& Parser::get_program() {
    return std::move(program_);
}

psc::Command Parser::parse_command() {
    // <command> -> <decl> | <stmt> | <block>
    if (token_.typeIsEquals(EnumTokenType::T_BRACE_L)) {  // <block>
        // <block> -> '{' { <command> }  '}'
        psc::Block* block = {new psc::Block{}};
        try {
            get_next_token();
            while (!token_.typeIsEquals(EnumTokenType::T_BRACE_R))
                block->commands.push_back(parse_command());
            match(EnumTokenType::T_BRACE_R);
        } catch (std::invalid_argument& e) {
            errout_ << e.what() << std::endl;
            delete block;
            throw e;
        }
        return psc::Command(block);
    } else if (token_.typeIsEquals(EnumTokenType::T_DATATYPE)) {  // <decl>
        // <decl> -> <type> <id> : <number> ;
        psc::Declare* decl = {new psc::Declare{}};
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
            // <if> -> if '( <expr> ')' <command> [ else ( <if> | <command> ) ]
            get_next_token();
            match(EnumTokenType::T_PAREN_L);
            parse_expr();
            match(EnumTokenType::T_PAREN_R);
            parse_command();
            if (token_.typeIsEquals(EnumTokenType::T_ELSE)) {  // else
                get_next_token();
                if (token_.typeIsEquals(EnumTokenType::T_IF)) {
                    // TODO parse if
                } else {
                    parse_command();
                }
            }
        } else if (token_.typeIsEquals(EnumTokenType::T_WHILE)) {  // <while>
            // <while> -> while '( <expr> ')' <command>
            get_next_token();
            match(EnumTokenType::T_PAREN_L);
            parse_expr();
            match(EnumTokenType::T_PAREN_R);
            parse_command();
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

psc::Expr Parser::parse_expr() {

}