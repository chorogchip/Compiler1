#pragma once
#include<vector>
#include<string>

namespace psc {
using namespace std;

struct Program {
    vector<Function> functions;
};
struct Function {
    EnumType returnType;
    vector<Variable> inputs;
    vector<Command> commands;
};
struct Command {
    EnumCommand type;
    union {
        Declare* decl;
        Statement* stmt;
        Command* block;  // TODO : 블럭을 잘못 정의함. 언어 정의부터 다시
    } data;
    Command(Declare* decl): type(EnumCommand::DECL) { data.decl = decl; }
    Command(Statement* stmt): type(EnumCommand::STMT) { data.stmt = stmt; }
    Command(Command* block): type(EnumCommand::BLOCK) { data.block = block; }
    ~Command() { switch (type) {
        case EnumCommand::DECL: delete data.decl; break;
        case EnumCommand::STMT: delete data.stmt; break;
        case EnumCommand::BLOCK: delete data.block; break;
    }}
};
struct Declare {
    Variable var;
    bool hasExpr;
    Expr expr;
};
struct Statement {
    EnumStatement type;
    union {
        STAssign* stmt_assign;
        STIF* stmt_if;
        STWHILE* stmt_while;
        STFOR* stmt_for;
        STRead* stmt_read;
        STWrite* stmt_write;
    } data;
    ~Statement() { switch (type) {
        case EnumStatement::ST_ASSIGN: delete data.stmt_assign; break;
        case EnumStatement::ST_IF: delete data.stmt_if; break;
        case EnumStatement::ST_WHILE: delete data.stmt_while; break;
        case EnumStatement::ST_FOR: delete data.stmt_for; break;
        case EnumStatement::ST_READ: delete data.stmt_read; break;
        case EnumStatement::ST_WRITE: delete data.stmt_write; break;
    }}
};
struct Variable {
    EnumType type;
    string name;
};
struct STAssign {
    string name;
    Expr expr;
};
struct STIF {
    Expr expr;
    Command command;
};
struct STWHILE {
    Expr expr;
    Command command;
};
struct STFOR {
    Declare decl;
    Expr expr;
    STAssign assign;
    Command command;
};
struct STRead {
    string name;
};
struct STWrite {
    string name;
};
struct Expr {
    EnumExpr type;
    union {
        string* number;
        string* id;
        OP_UN* op_un;
        OP_BIN* op_bin;
    } data;
    ~Expr() { switch (type) {
        case EnumExpr::EX_NUM: delete data.number; break;
        case EnumExpr::EX_ID: delete data.id; break;
        case EnumExpr::EX_OP_UN: delete data.op_un; break;
        case EnumExpr::EX_OP_BIN: delete data.op_bin; break;
    }}
};
struct OP_UN {
    string op;
    Expr expr;
};
struct OP_BIN {
    string op;
    Expr expr1, expr2;
};

enum class EnumType { INT };
enum class EnumCommand { DECL, STMT, BLOCK };
enum class EnumStatement { ST_ASSIGN, ST_IF, ST_WHILE, ST_FOR, ST_READ, ST_WRITE };
enum class EnumExpr { EX_NUM, EX_ID, EX_OP_UN, EX_OP_BIN };

}