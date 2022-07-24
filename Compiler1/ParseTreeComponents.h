#pragma once
#include<vector>
#include<string>
#include<any>

namespace psc {

enum class EnumType { INT };
enum class EnumCommand { DECL, STMT, BLOCK };
enum class EnumStatement { ST_NOP, ST_ASSIGN, ST_IF, ST_WHILE, ST_FOR,
    ST_READ, ST_WRITE, ST_WRITEC, ST_GOTO, ST_LABEL };
enum class EnumExpr { EX_NUM, EX_VAR, EX_OP_UN, EX_OP_BIN };
enum class EnumOp { ADD, SUB, MUL, DIV, MOD, SHL, SHR, AND, ORR, XOR,
    BAN, BOR, EQL, NEQ, BIG, BIE, SML, SME,
    PLS, MNS, NEG, BNE, ADR, PTR, PAR };

struct ID {
    ID(ID const &) = default;
    std::string str;
    explicit ID(std::string const &);
};
struct Num {
    Num(Num const &) = default;
    EnumType type;
    std::string number;
    explicit Num(EnumType, std::string const &);
};
struct Var {
    Var(Var const &) = default;
    EnumType type;
    ID name;
    Var(EnumType, ID const &);
};
struct OP_UN;
struct OP_BIN;
struct Expr {
    Expr(Expr const &) = default;
    EnumExpr type;
    std::any data;
    Expr(Num const &);
    Expr(ID const &);
    Expr(OP_UN const &);
    Expr(OP_BIN const &);
};
struct OP {
    OP(OP const &) = default;
    EnumOp op;
    OP(EnumOp const &);
};
struct OP_UN {
    OP_UN(OP_UN const &) = default;
    OP op;
    Expr expr;
    OP_UN(OP const &, Expr const &);
};
struct OP_BIN {
    OP_BIN(OP_BIN const &) = default;
    OP op;
    Expr expr1;
    Expr expr2;
    OP_BIN(OP const &, Expr const &, Expr const &);
};
struct Declare {
    Declare(Declare const &) = default;
    Var var;
    Num address;
    Declare(Var const &, Num const &);
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
    Statement(Statement const &) = default;
    EnumStatement type;
    std::any data;
    Statement();
    Statement(STAssign const &);
    Statement(STIf const &);
    Statement(STWhile const &);
    Statement(STFor const &);
    Statement(STRead const &);
    Statement(STWrite const &);
    Statement(STWritec const &);
    Statement(STGoto const &);
    Statement(STLabel const &);
};
struct Block;
struct Command {
    Command(Command const &) = default;
    EnumCommand type;
    std::any data;
    Command(Declare const &);
    Command(Statement const &);
    Command(Block const &);
};
struct STAssign {
    STAssign(STAssign const &) = default;
    ID name;
    Expr expr;
    STAssign(ID const &, Expr const &);
};
struct STIf {
    STIf(STIf const &) = default;
    Expr expr;
    bool hasElse;
    std::any command;  // Command or std::pair<Command,Command>
    STIf(Expr const &, Command const &);
    STIf(Expr const &, Command const &, Command const &);
};
struct STWhile {
    STWhile(STWhile const &) = default;
    Expr expr;
    Command command;
    STWhile(Expr const &, Command const &);
};
struct STFor {
    STFor(STFor const &) = default;
    Declare decl;
    STAssign assign1;
    Expr expr;
    STAssign assign2;
    Command command;
    STFor(Declare const &, STAssign const &, Expr const &, STAssign const &, Command const &);
};
struct STRead {
    STRead(STRead const &) = default;
    ID name;
    STRead(ID const &);
};
struct STWrite {
    STWrite(STWrite const &) = default;
    Expr expr;
    STWrite(Expr const &);
};
struct STWritec {
    STWritec(STWritec const &) = default;
    Expr expr;
    STWritec(Expr const &);
};
struct STGoto {
    STGoto(STGoto const &) = default;
    ID name;
    STGoto(ID const &);
};
struct STLabel {
    STLabel(STLabel const &) = default;
    ID name;
    STLabel(ID const &);
};
struct Block {
    Block(Block const &) = default;
    std::vector<Command> commands;
};
struct Program {
    Program(Program const &) = default;
    std::vector<Command> commands;
};


}