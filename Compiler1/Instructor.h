#pragma once
#include<iostream>
#include<stdexcept>
#include<any>
#include"ParseTreeComponents.h"
#include"StackVarMamager.h"
#include"LabelManager.h"
#include"InstructedProgram.h"

class Instructor {
private:
    psc::Program const &pr_;
    StackVarMamager vars_;
    LabelManager labels_;
    std::ostream &errout_;
    InstructedProgram program_;
    size_t control_statement_num_;

    void error(char const *message);

    void instruct_program(psc::Program const &);
    void instruct_command(psc::Command const &);
    void instruct_decl(psc::Declare const &);
    void instruct_label(psc::Label const &);
    void instruct_block(psc::Block const &);
    void instruct_statement(psc::Statement const &);
    
    void instruct_nop();
    void instruct_assign(psc::STAssign const &);
    void instruct_if(psc::STIf const &);
    void instruct_for(psc::STFor const &);
    void instruct_while(psc::STWhile const &);
    void instruct_goto(psc::STGoto const &);
    void instruct_read(psc::STRead const &);
    void instruct_write(psc::STWrite const &);
    void instruct_writec(psc::STWritec const &);

    void instruct_expr(psc::Expr const &, size_t);
    void instruct_op_un(psc::OP_UN const &, size_t);
    void instruct_op_bin(psc::OP_BIN const &, size_t);
    void instruct_val(psc::ID const &, size_t);
    void instruct_num(psc::Num const &, size_t);

public:
    Instructor(psc::Program const&, std::ostream &);
    bool instruct();
    InstructedProgram&& get_program() noexcept;
};

