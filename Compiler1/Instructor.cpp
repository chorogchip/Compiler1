#include "Instructor.h"

Instructor::Instructor(psc::Program const& p, std::ostream &out):
    pr_(p),
    vars_{},
    labels_{},
    errout_{out},
    program_{},
    control_statement_num_{0U}
{}
void Instructor::error(char const *message) {
    errout_ << "error occured in instructor.\n" << message
        << std::endl;
    throw std::invalid_argument("");
}
bool Instructor::instruct() {
    try {
        instruct_program(pr_);
        program_.insert(ByteCode{EnumOperation::END});
        if (program_.has_left_unindexed()) {
            errout_ << "unindexed label is left" << std::endl;
            return false;
        }
        return true;
    } catch (std::bad_any_cast &e) {
        errout_ << e.what() << "\ninvalid any data" << std::endl;
    } catch (std::invalid_argument &e) {
        errout_ << e.what() << "\ninvalid argument" << std::endl;
    } catch (std::out_of_range &e) {
        errout_ << e.what() << "\ninvalid index" << std::endl;
    } catch (std::domain_error &e ) {
        errout_ << e.what() << "\nthat name already exists" << std::endl;
    } catch (std::range_error &e) {
        errout_ << e.what() << "\nthat name does not exists" << std::endl;
    }
    return false;
}
void Instructor::instruct_program(psc::Program const & pr) {
    for (const auto &o : pr_.commands)
        instruct_command(o);
}
void Instructor::instruct_command(psc::Command const &cmd) {
    switch (cmd.type) {
    case psc::EnumCommand::DECL:
        instruct_decl(std::any_cast<psc::Declare const &>(cmd.data));
        break;
    case psc::EnumCommand::LABEL:
        instruct_label(std::any_cast<psc::Label const &>(cmd.data));
        break;
    case psc::EnumCommand::BLOCK:
        vars_.enter_block();
        instruct_block(std::any_cast<psc::Block const &>(cmd.data));
        vars_.escape_block();
        break;
    case psc::EnumCommand::STMT:
        instruct_statement(std::any_cast<psc::Statement const &>(cmd.data));
        break;
    default: error("data of command is invalid");
    }
}
void Instructor::instruct_decl(psc::Declare const &decl) {
    if (labels_.has_labl(decl.var.name.str))
        throw std::domain_error(decl.var.name.str);
    vars_.insert(decl);
}
void Instructor::instruct_label(psc::Label const &labl) {
    if (vars_.has_var(labl.name.str) || labels_.has_labl(labl.name.str))
        throw std::domain_error(labl.name.str);
    labels_.insert(labl, program_.get_size());
    program_.update_label_value(labl.name.str);
}
void Instructor::instruct_block(psc::Block const &b) {
    for (const auto &o : b.commands)
        instruct_command(o);
}
void Instructor::instruct_statement(psc::Statement const &st) {
    switch (st.type) {
    case psc::EnumStatement::ST_NOP:
        instruct_nop();
        break;
    case psc::EnumStatement::ST_ASSIGN:
        instruct_assign(std::any_cast<psc::STAssign const &>(st.data));
        break;
    case psc::EnumStatement::ST_IF:
        instruct_if(std::any_cast<psc::STIf const &>(st.data));
        break;
    case psc::EnumStatement::ST_FOR:
        instruct_for(std::any_cast<psc::STFor const &>(st.data));
        break;
    case psc::EnumStatement::ST_WHILE:
        instruct_while(std::any_cast<psc::STWhile const &>(st.data));
        break;
    case psc::EnumStatement::ST_GOTO:
        instruct_goto(std::any_cast<psc::STGoto const &>(st.data));
        break;
    case psc::EnumStatement::ST_READ:
        instruct_read(std::any_cast<psc::STRead const &>(st.data));
        break;
    case psc::EnumStatement::ST_WRITE:
        instruct_write(std::any_cast<psc::STWrite const &>(st.data));
        break;
    case psc::EnumStatement::ST_WRITEC:
        instruct_writec(std::any_cast<psc::STWritec const &>(st.data));
        break;
    default: error("data of statement is invalid");
    }
}

void Instructor::instruct_nop() {
    program_.insert(ByteCode{EnumOperation::NOP});
}
void Instructor::instruct_assign(psc::STAssign const &st) {
    size_t ind_to{vars_.get_var_index(st.name)};
    size_t ind_fr{pr_.max_address + 1U};
    if (st.expr.type == psc::EnumExpr::EX_OP_UN && std::any_cast<psc::OP_UN const &>(st.expr.data).op.op == psc::EnumOp::ADR) {
        const auto o = std::any_cast<psc::OP_UN const &>(st.expr.data);
        instruct_expr(std::any_cast<psc::Expr const &>(o.expr), ind_fr);
        program_.insert(ByteCode{EnumOperation::MOA, ind_to, ind_fr});
        return;
    }
    instruct_expr(st.expr, ind_fr);
    program_.insert(ByteCode{EnumOperation::MOV, ind_to, ind_fr});
}
void Instructor::instruct_if(psc::STIf const &st) {
    size_t ind{pr_.max_address + 1U};
    if (!st.hasElse) {
        psc::Command cmd{std::any_cast<psc::Command const &>(st.command)};
        ++control_statement_num_;
        std::string label_end(std::to_string(control_statement_num_));
        instruct_expr(st.expr, ind);
        program_.insert_unknown_op(ByteCode{EnumOperation::JNC, 0U, ind}, true, label_end);
        instruct_command(cmd);
        program_.update_label_value(label_end);
    } else {
        typedef  std::pair<psc::Command, psc::Command> pcc;
        pcc cmds = std::any_cast<pcc const &>(st.command);
        ++control_statement_num_;
        std::string label_else(std::to_string(control_statement_num_));
        ++control_statement_num_;
        std::string label_end(std::to_string(control_statement_num_));
        instruct_expr(st.expr, ind);
        program_.insert_unknown_op(ByteCode{EnumOperation::JNC, 0U, ind}, true, label_else);
        instruct_command(cmds.first);
        program_.insert_unknown_op(ByteCode{EnumOperation::JMC, 0U}, true, label_end);
        program_.update_label_value(label_else);
        instruct_command(cmds.second);
        program_.update_label_value(label_end);
    }
}
void Instructor::instruct_for(psc::STFor const &st) {
    size_t ind{pr_.max_address + 1U};
    vars_.enter_block();
    instruct_decl(st.decl);
    instruct_assign(st.assign1);
    size_t label_first{program_.get_size()};
    ++control_statement_num_;
    std::string label_end(std::to_string(control_statement_num_));
    instruct_expr(st.expr, ind);
    program_.insert_unknown_op(ByteCode{EnumOperation::JNC, 0U, ind}, true, label_end);
    instruct_command(st.command);
    instruct_assign(st.assign2);
    program_.insert(ByteCode{EnumOperation::JMC, label_first});
    program_.update_label_value(label_end);
    vars_.escape_block();
}
void Instructor::instruct_while(psc::STWhile const &st) {
    size_t ind{pr_.max_address + 1U};
    size_t label_first{program_.get_size()};
    ++control_statement_num_;
    std::string label_end(std::to_string(control_statement_num_));
    instruct_expr(st.expr, ind);
    program_.insert_unknown_op(ByteCode{EnumOperation::JNC, 0U, ind}, true, label_end);
    instruct_command(st.command);
    program_.insert(ByteCode{EnumOperation::JMC, label_first});
    program_.update_label_value(label_end);
}
void Instructor::instruct_goto(psc::STGoto const &st) {
    size_t ind{pr_.max_address + 1U};
    instruct_expr(st.expr, ind);
    program_.insert(ByteCode{EnumOperation::JMP, ind});
}
void Instructor::instruct_read(psc::STRead const &st) {
    program_.insert(ByteCode{EnumOperation::RDI, vars_.get_var_index(st.name)});
}
void Instructor::instruct_write(psc::STWrite const &st) {
    size_t ind{pr_.max_address + 1U};
    instruct_expr(st.expr, ind);
    program_.insert(ByteCode{EnumOperation::WRI, ind});
}
void Instructor::instruct_writec(psc::STWritec const &st) {
    size_t ind{pr_.max_address + 1U};
    instruct_expr(st.expr, ind);
    program_.insert(ByteCode{EnumOperation::WRC, ind});
}

void Instructor::instruct_expr(psc::Expr const &ex, size_t ind) {
    switch (ex.type) {
    case psc::EnumExpr::EX_NUM:
        instruct_num(std::any_cast<psc::Num const &>(ex.data), ind);
        break;
    case psc::EnumExpr::EX_VAR:
        instruct_val(std::any_cast<psc::ID const &>(ex.data), ind);
        break;
    case psc::EnumExpr::EX_OP_UN:
        instruct_op_un(std::any_cast<psc::OP_UN const &>(ex.data), ind);
        break;
    case psc::EnumExpr::EX_OP_BIN:
        instruct_op_bin(std::any_cast<psc::OP_BIN const &>(ex.data), ind);
        break;
    }
}
void Instructor::instruct_op_un(psc::OP_UN const &op_un, size_t ind) {
    EnumOperation op{EnumOperation::NOP};
    switch (op_un.op.op) {
    case psc::EnumOp::NEG: op = EnumOperation::NEG; break;
    case psc::EnumOp::BNE: op = EnumOperation::NOT; break;
    case psc::EnumOp::PLS: op = EnumOperation::NOP; break;
    case psc::EnumOp::MNS: op = EnumOperation::MNS; break;
    case psc::EnumOp::PTR:
        goto OP_UN_PTR;
    case psc::EnumOp::ADR:
        goto OP_UN_ADR;
    default:
        error("data of op_un is invalid");
    }
    instruct_expr(std::any_cast<psc::Expr const &>(op_un.expr), ind);
    if (op == EnumOperation::NOP) return;
    program_.insert(ByteCode{op, ind});
    return;
OP_UN_PTR:
    instruct_expr(std::any_cast<psc::Expr const &>(op_un.expr), ind + 1U);
    program_.insert(ByteCode{EnumOperation::MOP, ind, ind + 1U});
    return;
OP_UN_ADR:
    instruct_expr(std::any_cast<psc::Expr const &>(op_un.expr), ind + 1U);
    program_.insert(ByteCode{EnumOperation::MOA, ind, ind + 1U});
    return;
}
void Instructor::instruct_op_bin(psc::OP_BIN const &op_bin, size_t ind) {
    EnumOperation op{EnumOperation::NOP};
    switch (op_bin.op.op) {
    case psc::EnumOp::ADD: op = EnumOperation::ADD; break;
    case psc::EnumOp::SUB: op = EnumOperation::SUB; break;
    case psc::EnumOp::MUL: op = EnumOperation::MUL; break;
    case psc::EnumOp::DIV: op = EnumOperation::DIV; break;
    case psc::EnumOp::MOD: op = EnumOperation::MOD; break;
    case psc::EnumOp::SHL: op = EnumOperation::SHL; break;
    case psc::EnumOp::SHR: op = EnumOperation::SHR; break;
    case psc::EnumOp::AND: op = EnumOperation::AND; break;
    case psc::EnumOp::ORR: op = EnumOperation::ORR; break;
    case psc::EnumOp::XOR: op = EnumOperation::XOR; break;
    case psc::EnumOp::BAN: op = EnumOperation::BAN; break;
    case psc::EnumOp::BOR: op = EnumOperation::BOR; break;
    case psc::EnumOp::EQL: op = EnumOperation::EQL; break;
    case psc::EnumOp::NEQ: op = EnumOperation::NEQ; break;
    case psc::EnumOp::SML: op = EnumOperation::CMP; break;
    case psc::EnumOp::SME: op = EnumOperation::CME; break;
    case psc::EnumOp::BIG: op = EnumOperation::RCP; break;
    case psc::EnumOp::BIE: op = EnumOperation::RCE; break;
    default:
        error("data of op_un is invalid");
    }
    instruct_expr(std::any_cast<psc::Expr const &>(op_bin.expr1), ind);
    instruct_expr(std::any_cast<psc::Expr const &>(op_bin.expr2), ind + 1U);
    program_.insert(ByteCode{op, ind, ind + 1U});
}
void Instructor::instruct_val(psc::ID const &id, size_t ind) {
    if (vars_.has_var(id.str))
        program_.insert(ByteCode{EnumOperation::MOV, ind, vars_.get_var_index(id)});
    else if (labels_.has_labl(id.str))
        program_.insert(ByteCode{EnumOperation::MOC, ind, labels_.get_labl_index(id.str)});
    else
        program_.insert_unknown_op(ByteCode{EnumOperation::MOC, ind, 0U}, false, id.str);
    program_.update_max_memory(ind);
}
void Instructor::instruct_num(psc::Num const &num, size_t ind) {
    program_.insert(ByteCode{EnumOperation::MOC, ind, static_cast<size_t>(stoll(num.number))});
    program_.update_max_memory(ind);
}
InstructedProgram&& Instructor::get_program() noexcept {
    return std::move(program_);
}