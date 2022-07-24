#include "Interpreter.h"

Interpreter::Interpreter(psc::Program&& p, std::ostream& out):
    p_{std::move(p)},
    out_{out}
    //mem_{}
{}

void Interpreter::interpret() const {
    for (auto& cmd : p_.commands) {
        switch(cmd.type) {
        case psc::EnumCommand::DECL:
        case psc::EnumCommand::BLOCK:
        case psc::EnumCommand::STMT:
            break;
        }
    }
}