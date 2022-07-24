#include "Parser.h"

// do not use this->method(). just use method(). cause method call is too much

Parser::Parser(LexialAnalyzer &lexer, std::ostream &error_output_stream):
    lexer_{lexer},
    token_{EnumTokenType::T_ERROR_ON_ANALYZER},
    errout_{error_output_stream},
    program_{}
{}

Token Parser::match(EnumTokenType type) {
    Token pre_t{token_};
    if (token_.typeIsEquals(type))
        get_next_token();
    else error("type of current token does not match as expected.", type);
    return pre_t;
}
Token Parser::match(Token token) {
    Token pre_t{token_};
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
void Parser::error(char const *message) {
    errout_ << "error occured in parser.\n" << message <<
        "\ncurrent token : " << token_ << std::endl;
    throw std::invalid_argument("");
}
void Parser::error(char const *message, EnumTokenType type) {
    errout_ << "error occured in parser.\n" << message <<
        "\ntype : " << (int)type <<
        "\ncurrent token : " << token_ << std::endl;
    throw std::invalid_argument("");
}
void Parser::error(char const *message, Token token) {
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
            program_.commands.push_back(parse_command());
    } catch (std::invalid_argument &i) {
        errout_ << "error occured in parse : " << i.what() << std::endl;
    }
}
void Parser::get_next_token() {
    token_ = lexer_.getToken();
}
psc::Program &&Parser::get_program() {
    return std::move(program_);
}
std::string Parser::get_str_and_get_next_token() {
    std::string const st{token_.move_string()};
    get_next_token();
    return st;
}
psc::Command Parser::parse_command() {
    // <command> -> <decl> | <stmt> | <block>
    if (token_.typeIsEquals(EnumTokenType::T_BRACE_L))  // <block>
        return psc::Command{parse_block()};
    else if (token_.typeIsEquals(EnumTokenType::T_DATATYPE))  // <decl>
        return psc::Command{parse_decl()};
    else
        return psc::Command{parse_stmt()};  // <statement>
}
psc::Block Parser::parse_block() {
    // <block> -> '{' { <command> }  '}'
    psc::Block block{};
    match(EnumTokenType::T_BRACE_L);
    while (!token_.typeIsEquals(EnumTokenType::T_BRACE_R))
        block.commands.push_back(parse_command());
    match(EnumTokenType::T_BRACE_R);
    return block;
}
psc::Declare Parser::parse_decl() {
    // <decl> -> <type> <id> : <number> ;
    psc::Var const v{parse_var()};
    match(EnumTokenType::T_COLON);
    psc::Num const n{parse_int()};
    match(EnumTokenType::T_SEMICOLON);
    return psc::Declare{v, n};
}
psc::Statement Parser::parse_stmt() {
    // <stmt> -> <nop> | <assign> | <if> | <while> | <for> |
    // <read> | <write> | <writec> | <goto> | <label>
    if (token_.typeIsEquals(EnumTokenType::T_SEMICOLON))  // <nop>
        return psc::Statement{};
    else if (token_.typeIsEquals(EnumTokenType::T_VARIABLE))  // <assign>
        return psc::Statement{parse_assign(true)};
    else if (token_.typeIsEquals(EnumTokenType::T_LABEL))  // <label>
        return psc::Statement{parse_label()};
    else if (token_.typeIsEquals(EnumTokenType::T_IF))  // <if>
        return psc::Statement{parse_if()};
    else if (token_.typeIsEquals(EnumTokenType::T_WHILE))  // <while>
        return psc::Statement{parse_while()};
    else if (token_.typeIsEquals(EnumTokenType::T_FOR))  // <for>
        return psc::Statement{parse_for()};
    else if (token_.typeIsEquals(EnumTokenType::T_READ))  // <read>
        return psc::Statement{parse_read()};
    else if (token_.typeIsEquals(EnumTokenType::T_WRITE))  // <write>
        return psc::Statement{parse_write()};
    else if (token_.typeIsEquals(EnumTokenType::T_WRITEC))  // <writec>
        return psc::Statement{parse_writec()};
    else if (token_.typeIsEquals(EnumTokenType::T_GOTO))  // <goto>
        return psc::Statement{parse_goto()};
    
    error("command is expected");
    return psc::Statement{};
}
psc::STAssign Parser::parse_assign(bool has_semicolon) {
    // <assign> -> <id> = <expr> ;
    psc::ID const id{parse_id()};
    match(EnumTokenType::T_ASSIGN);
    psc::Expr const e{parse_expr()};
    if (has_semicolon) match(EnumTokenType::T_SEMICOLON);
    return psc::STAssign{id, e};
}
psc::STLabel Parser::parse_label() {
    // <label> -> label <id> :
    match(EnumTokenType::T_LABEL);
    psc::ID const id{parse_id()};
    match(EnumTokenType::T_COLON);
    return psc::STLabel{id};
}
psc::STIf Parser::parse_if() {
    // <if> -> if '( <expr> ')' <command> [ else <command> ]
    match(EnumTokenType::T_IF);
    match(EnumTokenType::T_PAREN_L);
    psc::Expr const e{parse_expr()};
    match(EnumTokenType::T_PAREN_R);
    psc::Command const c{parse_command()};
    if (token_.typeIsEquals(EnumTokenType::T_ELSE)) {  // else
        get_next_token();
        return psc::STIf{e, c, parse_command()};
    } else {
        return psc::STIf{e, c};
    }
}
psc::STWhile Parser::parse_while() {
    // <while> -> while '( <expr> ')' <command>
    match(EnumTokenType::T_WHILE);
    match(EnumTokenType::T_PAREN_L);
    psc::Expr const e{parse_expr()};
    match(EnumTokenType::T_PAREN_R);
    psc::Command const c{parse_command()};
    return psc::STWhile{e, c};
}
psc::STFor Parser::parse_for() {
    // <for> -> for '(' <decl> ; <assign> ; <expr> ; <assign> ')' <command>
    match(EnumTokenType::T_FOR);
    match(EnumTokenType::T_PAREN_L);
    psc::Declare const d{parse_decl()};
    psc::STAssign const a1{parse_assign(true)};
    psc::Expr const e{parse_expr()};
    match(EnumTokenType::T_SEMICOLON);
    psc::STAssign const a2{parse_assign(false)};
    match(EnumTokenType::T_PAREN_R);
    psc::Command const c{parse_command()};
    return psc::STFor{d, a1, e, a2, c};
}
psc::STRead Parser::parse_read() {
    // <read> -> read <id> ;
    match(EnumTokenType::T_READ);
    psc::STRead const r{parse_id()};
    match(EnumTokenType::T_SEMICOLON);
    return r;
}
psc::STWrite Parser::parse_write() {
    // <write> -> write <expr> ;
    match(EnumTokenType::T_WRITE);
    psc::STWrite const w{parse_expr()};
    match(EnumTokenType::T_SEMICOLON);
    return w;
}
psc::STWritec Parser::parse_writec() {
    // <writec> -> writec <expr> ;
    match(EnumTokenType::T_WRITEC);
    psc::STWritec const w{parse_expr()};
    match(EnumTokenType::T_SEMICOLON);
    return w;
}
psc::STGoto Parser::parse_goto() {     
    // <goto> -> goto <id> ;
    match(EnumTokenType::T_GOTO);
    psc::STGoto const g{parse_id()};
    match(EnumTokenType::T_SEMICOLON);
    return g;
}
psc::Var Parser::parse_var() {
    std::string name = match(EnumTokenType::T_DATATYPE).move_string();
    if (name == Token::STR_INT)
        return psc::Var{psc::EnumType::INT, parse_id()};
    error("type token expected");
    return psc::Var{psc::EnumType::INT, parse_id()};
    
}
psc::ID Parser::parse_id() {
    return psc::ID{match(EnumTokenType::T_VARIABLE).move_string()};
}
psc::Num Parser::parse_int() {
    if (token_.typeIsEquals(EnumTokenType::T_LITERAL_INT))
        return psc::Num{psc::EnumType::INT, get_str_and_get_next_token()};
    error("int literal token expected");
    return psc::Num{psc::EnumType::INT, get_str_and_get_next_token()};
}
psc::Num Parser::parse_num() {
    return parse_int();
}
psc::Expr Parser::parse_expr() {
    return parse_expr1();
}
psc::Expr Parser::parse_expr1() {
    psc::Expr e{parse_expr2()};
    while (token_ == Token{EnumTokenType::T_OPERATION_BIN, "||"}) {
        get_next_token();
        e = psc::Expr{psc::OP_BIN{psc::EnumOp::BOR, e, parse_expr2()}};
    }
    return e;
}
psc::Expr Parser::parse_expr2() {
    psc::Expr e{parse_expr3()};
    while (token_ == Token{EnumTokenType::T_OPERATION_BIN, "&&"}) {
        get_next_token();
        e = psc::Expr{psc::OP_BIN{psc::EnumOp::BAN, e, parse_expr3()}};
    }
    return e;
}
psc::Expr Parser::parse_expr3() {
    psc::Expr e{parse_expr4()};
    while (token_ == Token{EnumTokenType::T_OPERATION_BIN, "|"}) {
        get_next_token();
        e = psc::Expr{psc::OP_BIN{psc::EnumOp::ORR, e, parse_expr4()}};
    }
    return e;
}
psc::Expr Parser::parse_expr4() {
    psc::Expr e{parse_expr5()};
    while (token_ == Token{EnumTokenType::T_OPERATION_BIN, "^"}) {
        get_next_token();
        e = psc::Expr{psc::OP_BIN{psc::EnumOp::XOR, e, parse_expr5()}};
    }
    return e;
}
psc::Expr Parser::parse_expr5() {
    psc::Expr e{parse_expr6()};
    while (token_ == Token{EnumTokenType::T_OPERATION_BOTH, "&"}) {
        get_next_token();
        e = psc::Expr{psc::OP_BIN{psc::EnumOp::AND, e, parse_expr6()}};
    }
    return e;
}
psc::Expr Parser::parse_expr6() {
    psc::Expr e{parse_expr7()};
    do if (token_ == Token{EnumTokenType::T_OPERATION_BIN, "=="}) {
        get_next_token();
        e = psc::Expr{psc::OP_BIN{psc::EnumOp::EQL, e, parse_expr7()}};
    } else if (token_ == Token{EnumTokenType::T_OPERATION_BIN, "!="}) {
        get_next_token();
        e = psc::Expr{psc::OP_BIN{psc::EnumOp::NEQ, e, parse_expr7()}};
    } else break;
    while (true);
    return e;
}
psc::Expr Parser::parse_expr7() {
    psc::Expr e{parse_expr8()};
    do if (token_ == Token{EnumTokenType::T_OPERATION_BIN, "<"}) {
        get_next_token();
        e = psc::Expr{psc::OP_BIN{psc::EnumOp::SML, e, parse_expr8()}};
    } else if (token_ == Token{EnumTokenType::T_OPERATION_BIN, ">"}) {
        get_next_token();
        e = psc::Expr{psc::OP_BIN{psc::EnumOp::BIG, e, parse_expr8()}};
    } else if (token_ == Token{EnumTokenType::T_OPERATION_BIN, "<="}) {
        get_next_token();
        e = psc::Expr{psc::OP_BIN{psc::EnumOp::SME, e, parse_expr8()}};
    } else if (token_ == Token{EnumTokenType::T_OPERATION_BIN, ">="}) {
        get_next_token();
        e = psc::Expr{psc::OP_BIN{psc::EnumOp::BIE, e, parse_expr8()}};
    } else break;
    while (true);
    return e;
}
psc::Expr Parser::parse_expr8() {
    psc::Expr e{parse_expr9()};
    do if (token_ == Token{EnumTokenType::T_OPERATION_BIN, "<<"}) {
        get_next_token();
        e = psc::Expr{psc::OP_BIN{psc::EnumOp::SHL, e, parse_expr9()}};
    } else if (token_ == Token{EnumTokenType::T_OPERATION_BIN, ">>"}) {
        get_next_token();
        e = psc::Expr{psc::OP_BIN{psc::EnumOp::SHR, e, parse_expr9()}};
    } else break;
    while (true);
    return e;
}
psc::Expr Parser::parse_expr9() {
    psc::Expr e{parse_expr10()};
    do if (token_ == Token{EnumTokenType::T_OPERATION_BOTH, "+"}) {
        get_next_token();
        e = psc::Expr{psc::OP_BIN{psc::EnumOp::ADD, e, parse_expr10()}};
    } else if (token_ == Token{EnumTokenType::T_OPERATION_BOTH, "-"}) {
        get_next_token();
        e = psc::Expr{psc::OP_BIN{psc::EnumOp::SUB, e, parse_expr10()}};
    } else break;
    while (true);
    return e;
}
psc::Expr Parser::parse_expr10() {
    psc::Expr e{parse_expr11()};
    do if (token_ == Token{EnumTokenType::T_OPERATION_BIN, "*"}) {
        get_next_token();
        e = psc::Expr{psc::OP_BIN{psc::EnumOp::MUL, e, parse_expr11()}};
    } else if (token_ == Token{EnumTokenType::T_OPERATION_BIN, "/"}) {
        get_next_token();
        e = psc::Expr{psc::OP_BIN{psc::EnumOp::DIV, e, parse_expr11()}};
    } else if (token_ == Token{EnumTokenType::T_OPERATION_BIN, "%"}) {
        get_next_token();
        e = psc::Expr{psc::OP_BIN{psc::EnumOp::MOD, e, parse_expr11()}};
    } else break;
    while (true);
    return e;
}
psc::Expr Parser::parse_expr11() {
    if (token_ == Token{EnumTokenType::T_OPERATION_BOTH, "+"}) {
        get_next_token();
        return psc::Expr{psc::OP_UN{psc::EnumOp::PLS, parse_expr11()}};
    } else if (token_ == Token{EnumTokenType::T_OPERATION_UN, "-"}) {
        get_next_token();
        return psc::Expr{psc::OP_UN{psc::EnumOp::MNS, parse_expr11()}};
    } else if (token_ == Token{EnumTokenType::T_OPERATION_UN, "~"}) {
        get_next_token();
        return psc::Expr{psc::OP_UN{psc::EnumOp::NEG, parse_expr11()}};
    } else if (token_ == Token{EnumTokenType::T_OPERATION_UN, "!"}) {
        get_next_token();
        return psc::Expr{psc::OP_UN{psc::EnumOp::BNE, parse_expr11()}};
    } else if (token_ == Token{EnumTokenType::T_OPERATION_UN, "*"}) {
        get_next_token();
        return psc::Expr{psc::OP_UN{psc::EnumOp::PTR, parse_expr11()}};
    } else if (token_ == Token{EnumTokenType::T_OPERATION_BOTH, "&"}) {
        get_next_token();
        return psc::Expr{psc::OP_UN{psc::EnumOp::ADR, parse_expr11()}};
    }
    return parse_expr12();
}
psc::Expr Parser::parse_expr12() {
    if (token_.typeIsEquals(EnumTokenType::T_PAREN_L)) {
        get_next_token();
        psc::Expr const e{parse_expr()};
        match(EnumTokenType::T_PAREN_R);
        return e;
    } else if (token_.typeIsEquals(EnumTokenType::T_VARIABLE))
        return psc::Expr{parse_id()};
    else if (token_.typeIsEquals(EnumTokenType::T_LITERAL_INT))
        return psc::Expr{parse_num()};
    error("literal or value or parenthesis expected");
    return psc::Expr{psc::ID{""}};
}