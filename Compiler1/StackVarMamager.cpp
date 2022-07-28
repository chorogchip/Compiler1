#include "StackVarMamager.h"

StackVarMamager::Var::Var(std::string const &nm, size_t ind):
    name_(nm),
    index_{ind}
{}
StackVarMamager::Var::Var(Var &&v) noexcept:
    name_(std::move(v.name_)),
    index_{v.index_}
{}
bool StackVarMamager::Var::name_is_equals(std::string const &nm) const {
    return nm == name_;
}
StackVarMamager::Var::Var(psc::Declare const &d):
    name_(d.var.name.str),
    index_{static_cast<size_t>(std::stoll(d.address.number))}
{}
size_t StackVarMamager::Var::get_var_index() const {
    return index_;
}

void StackVarMamager::Block::insert(Var &&v) noexcept {
    vars_.push_back(std::move(v));
}
bool StackVarMamager::Block::has_var(std::string const &nm) const {
    for (auto it{vars_.rbegin()}; it != vars_.rend(); ++it)
        if (it->name_is_equals(nm))
            return true;
    return false;
}
size_t StackVarMamager::Block::get_var_index(std::string const &nm) const {
    for (auto it{vars_.rbegin()}; it != vars_.rend(); ++it)
        if (it->name_is_equals(nm))
            return it->get_var_index();
    throw std::out_of_range("variable does not exists");
    return 0U;
}

StackVarMamager::StackVarMamager():
    blocks_({Block{}})
{}
void StackVarMamager::insert(psc::Declare const & decl) {
    blocks_.back().insert(Var{decl});
}
void StackVarMamager::enter_block() {
    blocks_.push_back(Block{});
}
void StackVarMamager::escape_block() {
    if (blocks_.size() <= 1)
        throw std::out_of_range("escaping global block");
    blocks_.pop_back();
}
size_t StackVarMamager::get_var_index(psc::ID const &name) const {
    for (auto it{blocks_.rbegin()}; it != blocks_.rend(); ++it)
        if (it->has_var(name.str))
            return it->get_var_index(name.str);
    throw std::out_of_range("variable does not exists");
    return 0U;
}
bool StackVarMamager::has_var(std::string const &nm) const {
    for (auto it{blocks_.rbegin()}; it != blocks_.rend(); ++it)
        if (it->has_var(nm))
            return true;
    return false;
}