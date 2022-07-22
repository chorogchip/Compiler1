#pragma once
#include<vector>
#include<string>
#include<any>

namespace psc {

enum class EnumType { INT };
enum class EnumCommand { DECL, STMT, BLOCK };
enum class EnumStatement { ST_ASSIGN, ST_IF, ST_WHILE, ST_FOR,
    ST_READ, ST_WRITE, ST_WRITEC, ST_GOTO, ST_LABEL };
enum class EnumExpr { EX_NUM, EX_VAR, EX_OP_UN, EX_OP_BIN };

struct ID {
    ID(const ID&) = default;
    std::string str;
    ID(const std::string&);
};
struct Num {
    Num(const Num&) = default;
    EnumType type;
    std::string number;
    Num(EnumType, const std::string&);
};
struct Var {
    Var(const Var&) = default;
    EnumType type;
    std::string name;
    Var(EnumType, const std::string&);
};
struct OP_UN;
struct OP_BIN;
struct Expr {
    Expr(const Expr&) = default;
    EnumExpr type;
    std::any data;
    Expr(const Num&);
    Expr(const Var&);
    Expr(const OP_UN&);
    Expr(const OP_BIN&);
};
struct OP {
    OP(const OP&) = default;
    std::string op;
    OP(const std::string&);
};
struct OP_UN {
    OP_UN(const OP_UN&) = default;
    OP op;
    Expr expr;
    OP_UN(const OP&, const Expr&);
};
struct OP_BIN {
    OP_BIN(const OP_BIN&) = default;
    OP op;
    Expr expr1;
    Expr expr2;
    OP_BIN(const OP&, const Expr&, const Expr&);
};
struct Declare {
    Declare(const Declare&) = default;
    Var var;
    Expr expr;
    Declare(const Var&, const Expr&);
};
struct STAssign;
struct STIf;
struct STWhile;
struct STFor;
struct STRead;
struct STWrite;
struct STWritec;
struct STGoto;
struct STLabel;
struct Statement {
    Statement(const Statement&) = default;
    EnumStatement type;
    std::any data;
    Statement(const STAssign&);
    Statement(const STIf&);
    Statement(const STWhile&);
    Statement(const STFor&);
    Statement(const STRead&);
    Statement(const STWrite&);
    Statement(const STWritec&);
    Statement(const STGoto&);
    Statement(const STLabel&);
};
struct Block;
struct Command {
    Command(const Command&) = default;
    EnumCommand type;
    std::any data;
    Command(const Declare&);
    Command(const Statement&);
    Command(const Block&);
};
struct STAssign {
    STAssign(const STAssign&) = default;
    ID name;
    Expr expr;
    STAssign(const ID&, const Expr&);
};
struct STIf {
    STIf(const STIf&) = default;
    Expr expr;
    bool hasElse;
    std::any command;  // Command or std::pair<Command,Command>
    STIf(const Expr&, const Command&);
    STIf(const Expr&, const Command&, const Command&);
};
struct STWhile {
    STWhile(const STWhile&) = default;
    Expr expr;
    Command command;
    STWhile(const Expr&, const Command&);
};
struct STFor {
    STFor(const STFor&) = default;
    Declare decl;
    STAssign assign1;
    Expr expr;
    STAssign assign2;
    Command command;
    STFor(const Declare&, const STAssign&, const Expr&, const STAssign&, const Command&);
};
struct STRead {
    STRead(const STRead&) = default;
    ID name;
    STRead(const ID&);
};
struct STWrite {
    STWrite(const STWrite&) = default;
    Expr expr;
    STWrite(const Expr&);
};
struct STWritec {
    STWritec(const STWritec&) = default;
    Expr expr;
    STWritec(const Expr&);
};
struct STGoto {
    STGoto(const STGoto&) = default;
    ID name;
    STGoto(const ID&);
};
struct STLabel {
    STLabel(const STLabel&) = default;
    ID name;
    STLabel(const ID&);
};
struct Block {
    Block(const Block&) = default;
    std::vector<Command> commands;
};
struct Program {
    Program(const Program&) = default;
    std::vector<Command> commands;
};


}