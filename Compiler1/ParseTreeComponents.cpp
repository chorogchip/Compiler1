#include "ParseTreeComponents.h"

namespace psc {


ID::ID(std::string const &s): str(s) {}
Num::Num(EnumType t, std::string const &s): type{t}, number(s) {}
Var::Var(EnumType t, ID const &s): type{t}, name{s} {}
Expr::Expr(Num const &number):    type(EnumExpr::EX_NUM), data{number} {}
Expr::Expr(ID const &id):  type(EnumExpr::EX_VAR), data{id} {}
Expr::Expr(OP_UN const &op_un):   type(EnumExpr::EX_OP_UN), data{op_un} {}
Expr::Expr(OP_BIN const &op_bin): type(EnumExpr::EX_OP_BIN), data{op_bin} {}
OP::OP(EnumOp const &opp): op{opp} {}
OP_UN::OP_UN(OP const &opr, Expr const &ex): op{opr}, expr{ex} {}
OP_BIN::OP_BIN(OP const &opr, Expr const &ex1, Expr const &ex2):
    op{opr}, expr1{ex1}, expr2{ex2} {}
Declare::Declare(Var const &v, Num const &add): var{v}, address{add} {}
Label::Label(ID const &nm): name{nm} {}
Statement::Statement(): type(EnumStatement::ST_NOP), data{} {}
Statement::Statement(STAssign const &ass):  type{EnumStatement::ST_ASSIGN}, data{ass} {}
Statement::Statement(STIf const &iff):      type{EnumStatement::ST_IF}, data{iff} {}
Statement::Statement(STWhile const &wh):    type{EnumStatement::ST_WHILE}, data{wh} {}
Statement::Statement(STFor const &forr):    type{EnumStatement::ST_FOR}, data{forr} {}
Statement::Statement(STRead const &rd):     type{EnumStatement::ST_READ}, data{rd} {}
Statement::Statement(STWrite const &wr):    type{EnumStatement::ST_WRITE}, data{wr} {}
Statement::Statement(STWritec const &wrc):  type{EnumStatement::ST_WRITEC}, data{wrc} {}
Statement::Statement(STGoto const &gotoo):  type{EnumStatement::ST_GOTO}, data{gotoo} {}
Command::Command(Declare const &decl): type{EnumCommand::DECL}, data{decl} {}
Command::Command(Statement const &stmt): type{EnumCommand::STMT}, data{stmt} {}
Command::Command(Block const &blk): type{EnumCommand::BLOCK}, data{blk} {}
Command::Command(Label const &labl):  type{EnumCommand::LABEL}, data{labl} {}
STAssign::STAssign(ID const &nm, Expr const &ex): name{nm}, expr{ex} {}
STIf::STIf(Expr const &ex, Command const &cmd): expr{ex}, command{cmd}, hasElse{false} {}
STIf::STIf(Expr const &ex, Command const &cmd, Command const &cmd_else):
    expr{ex}, command{std::make_pair(cmd, cmd_else)}, hasElse{true} {}
STWhile::STWhile(Expr const &ex, Command const &cmd): expr{ex}, command{cmd} {}
STFor::STFor(Declare const &de, STAssign const &ass1, Expr const &ex,
             STAssign const &ass2, Command const &cmd):
    decl{de}, assign1{ass1}, expr{ex}, assign2{ass2}, command{cmd} {}
STRead::STRead(ID const &nm): name{nm} {}
STWrite::STWrite(Expr const &ex): expr{ex} {}
STWritec::STWritec(Expr const &ex): expr{ex} {}
STGoto::STGoto(Expr const &ex): expr{ex} {}
Block::Block(Block &&bl) noexcept:
    commands(std::move(bl.commands)) {}
Program::Program(Program &&p) noexcept:
    commands(std::move(p.commands)), max_address{p.max_address} {}
}