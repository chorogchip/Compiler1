#include "InstructedProgram.h"

InstructedProgram::OP_::OP_(size_t ind, bool first, std::string const &nm):
    index{ind},
    is_first{first},
    name(nm)
{}

InstructedProgram::InstructedProgram(InstructedProgram &&p):
    total_memory_{p.total_memory_},
    code_(std::move(p.code_)),
    unindexed_op_(std::move(p.unindexed_op_)),
    unindexed_op_compiler_(std::move(p.unindexed_op_compiler_))
{}
size_t InstructedProgram::get_size() const {
    return code_.size();
}
void InstructedProgram::update_max_memory(size_t mem) {
    if (total_memory_ <= mem)
        total_memory_ = mem + 1U;
}
void InstructedProgram::insert(ByteCode const &cd) {
    code_.push_back(cd);
}
void InstructedProgram::insert_unknown_op(ByteCode const &cd, bool is_first, std::string const &nm) {
    unindexed_op_.push_back(InstructedProgram::OP_{code_.size(), is_first, nm});
    code_.push_back(cd);
}
void InstructedProgram::insert_unknown_op_compiler(ByteCode const &cd, bool is_first, std::string const &nm) {
    unindexed_op_compiler_.push_back(InstructedProgram::OP_{code_.size(), is_first, nm});
    code_.push_back(cd);
}
void InstructedProgram::update_label_value(std::string const &labl) {
    size_t ind{code_.size()};
    for (auto it{unindexed_op_.begin()}; it != unindexed_op_.end(); ) {
        if (it->name == labl) {
            if (it->is_first) code_[it->index].val1 = ind;
            else code_[it->index].val2 = ind;
            it = unindexed_op_.erase(it);
        } else ++it;
    }
}
void InstructedProgram::update_label_value_compiler(std::string const &labl) {
    size_t ind{code_.size()};
    for (auto it{unindexed_op_compiler_.begin()}; it != unindexed_op_compiler_.end(); ) {
        if (it->name == labl) {
            if (it->is_first) code_[it->index].val1 = ind;
            else code_[it->index].val2 = ind;
            it = unindexed_op_compiler_.erase(it);
        } else ++it;
    }
}
bool InstructedProgram::has_left_unindexed() const {
    return !unindexed_op_.empty() || !unindexed_op_compiler_.empty();
}


static std::ostream& operator<<(std::ostream& out, EnumOperation op) {
    switch (op) {
    case EnumOperation::NOP: out << "NOP"; return out;
    case EnumOperation::END: out << "END"; return out;
    case EnumOperation::JMC: out << "JMC"; return out;
    case EnumOperation::JIC: out << "JIC"; return out;
    case EnumOperation::JNC: out << "JNC"; return out;
    case EnumOperation::JMP: out << "JMP"; return out;
    case EnumOperation::JIF: out << "JIF"; return out;
    case EnumOperation::JNF: out << "JNF"; return out;
    case EnumOperation::MOC: out << "MOC"; return out;
    case EnumOperation::MOV: out << "MOV"; return out;
    case EnumOperation::MOP: out << "MOP"; return out;
    case EnumOperation::MOA: out << "MOA"; return out;
    case EnumOperation::NEG: out << "NEG"; return out;
    case EnumOperation::NOT: out << "NOT"; return out;
    case EnumOperation::MNS: out << "MNS"; return out;
    case EnumOperation::ADD: out << "ADD"; return out;
    case EnumOperation::SUB: out << "SUB"; return out;
    case EnumOperation::MUL: out << "MUL"; return out;
    case EnumOperation::DIV: out << "DIV"; return out;
    case EnumOperation::MOD: out << "MOD"; return out;
    case EnumOperation::SHL: out << "SHL"; return out;
    case EnumOperation::SHR: out << "SHR"; return out;
    case EnumOperation::AND: out << "AND"; return out;
    case EnumOperation::ORR: out << "ORR"; return out;
    case EnumOperation::XOR: out << "XOR"; return out;
    case EnumOperation::BAN: out << "BAN"; return out;
    case EnumOperation::BOR: out << "BOR"; return out;
    case EnumOperation::EQL: out << "EQL"; return out;
    case EnumOperation::NEQ: out << "NEQ"; return out;
    case EnumOperation::CMP: out << "CMP"; return out;
    case EnumOperation::CME: out << "CME"; return out;
    case EnumOperation::RCP: out << "RCP"; return out;
    case EnumOperation::RCE: out << "RCE"; return out;
    case EnumOperation::RDI: out << "RDI"; return out;
    case EnumOperation::RDC: out << "RDC"; return out;
    case EnumOperation::GET: out << "GET"; return out;
    case EnumOperation::WRI: out << "WRI"; return out;
    case EnumOperation::WRC: out << "WRC"; return out;
    case EnumOperation::PUT: out << "PUT"; return out;
    default: return out;
    }
}

std::ostream& operator<<(std::ostream& out, InstructedProgram const &pr) {
    out << pr.total_memory_ << '\n';
    out << std::hex << std::showbase;
    size_t ind{0U};
    for (auto &o : pr.code_) {
        out.width(6);
        out << ind << ' ' << o.op << ' ' << o.val1 << ' ' << o.val2 << '\n';
        ++ind;
    }
    out << std::endl;
    return out;
}