#include "Interpreter.h"

Interpreter::Interpreter(InstructedProgram &&p, std::ostream &out):
    p_{std::move(p)},
    out_{out},
    mem_{new data[p.total_memory_]}
{}
Interpreter::~Interpreter() {
    delete[] mem_;
}

void Interpreter::interpret() {
    size_t code_sz{p_.code_.size()};
    data d;
    for (size_t pc{0U}; pc < code_sz; ) {
        const ByteCode &code = p_.code_[pc];
        switch (code.op) {
        case EnumOperation::NOP: ++pc; break;
        case EnumOperation::END: return;

        case EnumOperation::JMC: pc = code.val1; break;
        case EnumOperation::JIC: if (static_cast<bool>(mem_[code.val2])) pc = code.val1; else ++pc; break;
        case EnumOperation::JNC: if (!static_cast<bool>(mem_[code.val2])) pc = code.val1; else ++pc; break;
        case EnumOperation::JMP: pc = mem_[code.val1]; break;
        case EnumOperation::JIF: if (static_cast<bool>(mem_[code.val2])) pc = mem_[code.val1]; else ++pc; break;
        case EnumOperation::JNF: if (!static_cast<bool>(mem_[code.val2])) pc = mem_[code.val1]; else ++pc; break;

        case EnumOperation::MOC: mem_[code.val1] = code.val2; ++pc; break;
        case EnumOperation::MOV: mem_[code.val1] = mem_[code.val2]; ++pc; break;
        case EnumOperation::MOP: mem_[code.val1] = mem_[mem_[code.val2]]; ++pc; break;
        case EnumOperation::MOA: mem_[mem_[code.val1]] = mem_[code.val2]; ++pc; break;

        case EnumOperation::NEG: mem_[code.val1] = ~mem_[code.val1]; ++pc; break;
        case EnumOperation::NOT: mem_[code.val1] = static_cast<data>(!static_cast<bool>(mem_[code.val1])); ++pc; break;
        case EnumOperation::MNS: mem_[code.val1] = -mem_[code.val1]; ++pc; break;

        case EnumOperation::ADD: mem_[code.val1] += mem_[code.val2]; ++pc; break;
        case EnumOperation::SUB: mem_[code.val1] -= mem_[code.val2]; ++pc; break;
        case EnumOperation::MUL: mem_[code.val1] *= mem_[code.val2]; ++pc; break;
        case EnumOperation::DIV: mem_[code.val1] /= mem_[code.val2]; ++pc; break;
        case EnumOperation::MOD: mem_[code.val1] %= mem_[code.val2]; ++pc; break;
        case EnumOperation::SHL: mem_[code.val1] <<= mem_[code.val2]; ++pc; break;
        case EnumOperation::SHR: mem_[code.val1] >>= mem_[code.val2]; ++pc; break;
        case EnumOperation::AND: mem_[code.val1] &= mem_[code.val2]; ++pc; break;
        case EnumOperation::XOR: mem_[code.val1] ^= mem_[code.val2]; ++pc; break;
        case EnumOperation::ORR: mem_[code.val1] |= mem_[code.val2]; ++pc; break;
        case EnumOperation::BAN: mem_[code.val1] = static_cast<data>(static_cast<bool>(mem_[code.val1]) && static_cast<bool>(mem_[code.val2])); ++pc; break;
        case EnumOperation::BOR: mem_[code.val1] = static_cast<data>(static_cast<bool>(mem_[code.val1]) && static_cast<bool>(mem_[code.val2])); ++pc; break;

        case EnumOperation::EQL: mem_[code.val1] = static_cast<data>(mem_[code.val1] == mem_[code.val2]); ++pc; break;
        case EnumOperation::NEQ: mem_[code.val1] = static_cast<data>(mem_[code.val1] != mem_[code.val2]); ++pc; break;
        case EnumOperation::CMP: mem_[code.val1] = static_cast<data>(mem_[code.val1] < mem_[code.val2]); ++pc; break;
        case EnumOperation::CME: mem_[code.val1] = static_cast<data>(mem_[code.val1] <= mem_[code.val2]); ++pc; break;
        case EnumOperation::RCP: mem_[code.val1] = static_cast<data>(mem_[code.val1] > mem_[code.val2]); ++pc; break;
        case EnumOperation::RCE: mem_[code.val1] = static_cast<data>(mem_[code.val1] >= mem_[code.val2]); ++pc; break;

        case EnumOperation::RDC: mem_[code.val1] = static_cast<data>(getchar()); ++pc; break;
        case EnumOperation::RDI: scanf_s("%lld", &d); mem_[code.val1] = d; ++pc; break;
        case EnumOperation::GET: for (data i{static_cast<data>(0)}; i < mem_[code.val2]; ++i)
            mem_[mem_[code.val1] + i] = static_cast<data>(getchar());
            ++pc; break;
        case EnumOperation::WRC: putchar(static_cast<char>(mem_[code.val1])); ++pc; break;
        case EnumOperation::WRI: printf("%lld", mem_[code.val1]); ++pc; break;
        case EnumOperation::PUT: for (data i{static_cast<data>(0)}; i < mem_[code.val2]; ++i)
                                    putchar(static_cast<char>(mem_[mem_[code.val1] + i]));
            ++pc; break;
        }
    }
}