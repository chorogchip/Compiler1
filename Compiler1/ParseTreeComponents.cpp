#include "ParseTreeComponents.h"

namespace psc {


ID::ID(const std::string& s): str{s} {}
Num::Num(EnumType t, const std::string& s): type{t}, number{s} {}
Var::Var(EnumType t, const std::string& s): type{t}, name{s} {}
Expr::Expr(const Num& number):    type(EnumExpr::EX_NUM), data{number} {}
Expr::Expr(const Var& var):  type(EnumExpr::EX_VAR), data{var} {}
Expr::Expr(const OP_UN& op_un):   type(EnumExpr::EX_OP_UN), data{op_un} {}
Expr::Expr(const OP_BIN& op_bin): type(EnumExpr::EX_OP_BIN), data{op_bin} {}
OP::OP(const std::string& s): op{s} {}
OP_UN::OP_UN(const OP& opr, const Expr& ex): op{opr}, expr{ex} {}
OP_BIN::OP_BIN(const OP& opr, const Expr& ex1, const Expr& ex2):
    op{opr}, expr1{ex1}, expr2{ex2} {}
Declare::Declare(const Var& v, const Expr& ex): var{v}, expr{ex} {}
Statement::Statement(const STAssign& ass):  type{EnumStatement::ST_ASSIGN}, data{ass} {}
Statement::Statement(const STIf& iff):      type{EnumStatement::ST_IF}, data{iff} {}
Statement::Statement(const STWhile& wh):    type{EnumStatement::ST_WHILE}, data{wh} {}
Statement::Statement(const STFor& forr):    type{EnumStatement::ST_FOR}, data{forr} {}
Statement::Statement(const STRead& rd):     type{EnumStatement::ST_READ}, data{rd} {}
Statement::Statement(const STWrite& wr):    type{EnumStatement::ST_WRITE}, data{wr} {}
Statement::Statement(const STWritec& wrc):  type{EnumStatement::ST_WRITEC}, data{wrc} {}
Statement::Statement(const STGoto& gotoo):  type{EnumStatement::ST_GOTO}, data{gotoo} {}
Statement::Statement(const STLabel& labl):  type{EnumStatement::ST_LABEL}, data{labl} {}
Command::Command(const Declare& decl): type{EnumCommand::DECL}, data{decl} {}
Command::Command(const Statement& stmt): type{EnumCommand::STMT}, data{stmt} {}
Command::Command(const Block& blk): type{EnumCommand::BLOCK}, data{blk} {}
STAssign::STAssign(const ID& nm, const Expr& ex): name{nm}, expr{ex} {}
STIf::STIf(const Expr& ex, const Command& cmd): expr{ex}, command{cmd}, hasElse{false} {}
STIf::STIf(const Expr& ex, const Command& cmd, const Command& cmd_else):
    expr{ex}, command{std::make_pair(cmd, cmd_else)}, hasElse{true} {}
STWhile::STWhile(const Expr& ex, const Command& cmd): expr{ex}, command{cmd} {}
STFor::STFor(const Declare& de, const STAssign& ass1, const Expr& ex,
             const STAssign& ass2, const Command& cmd):
    decl{de}, assign1{ass1}, expr{ex}, assign2{ass2}, command{cmd} {}
STRead::STRead(const ID& nm): name{nm} {}
STWrite::STWrite(const Expr& ex): expr{ex} {}
STWritec::STWritec(const Expr& ex): expr{ex} {}
STGoto::STGoto(const ID& nm): name{nm} {}
STLabel::STLabel(const ID& nm): name{nm} {}
}