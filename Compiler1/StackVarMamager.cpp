#include "StackVarMamager.h"

StackVarMamager::Var::Var(const std::string& nm, size_t ind):
    name_(nm),
    index_{ind}
{}
StackVarMamager::Var::Var(Var&& v) noexcept:
    name_(std::move(v.name_)),
    index_{v.index_}
{}
bool StackVarMamager::Var::name_is_equals(const std::string& nm) const {
    return nm == name_;
}
StackVarMamager::Var::Var(const psc::Declare& d):
    name_(d.var.name.str),
    index_{static_cast<size_t>(std::stoll(d.address.number))}
{}

StackVarMamager::Label::Label(const std::string nm):
    name_(nm)
{}
StackVarMamager::Label::Label(Label&& l) noexcept:
    name_(std::move(l.name_))
{}
bool StackVarMamager::Label::name_is_equals(const std::string& nm) const {
    return nm == name_;
}
StackVarMamager::Label::Label(const psc::STLabel& l):
    name_(l.name.str)
{}

void StackVarMamager::Block::insert(Var&& v) noexcept {
    vars_.push_back(std::move(v));
}
void StackVarMamager::Block::insert(Label&& l) noexcept {
    labels_.push_back(std::move(l));
}
bool StackVarMamager::Block::hasVar(const std::string& nm) const {
    for (auto& o : vars_)
        if (o.name_is_equals(nm))
            return true;
    return false;
}
bool StackVarMamager::Block::hasLabel(const std::string& nm) const {
    for (auto& o : labels_)
        if (o.name_is_equals(nm))
            return true;
    return false;
}

StackVarMamager::StackVarMamager(const psc::Program& p, std::ostream& out):
    pr_{p},
    errout_{out},
    blocks_({Block{}}),
    current_block_{0U}
{
    try {
        this->read_program();
    } catch (std::bad_any_cast& e) {
        errout_ << "error on StackVarManager reading program\n"
                << "invalid program structure : "
                << e.what() << std::endl;
    } catch (std::exception& e) {
        errout_ << "error on StackVarManager reading program\n"
                << "unknown exception :" 
                << e.what() << std::endl;
    }
}
void StackVarMamager::read_program() {
    for (auto& o : pr_.commands) {
        switch (o.type) {
        case psc::EnumCommand::DECL:
            blocks_.back().insert(Var{std::any_cast<psc::Declare>(o)});
            break;
        case psc::EnumCommand::BLOCK:
            blocks_.push_back(Block{});
            break;  // TODO wrong structure : block must be nested, not stored in vector
        case psc::EnumCommand::STMT:
            break;
            // TODO
        }
    }
}