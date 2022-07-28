#include "LabelManager.h"


LabelManager::Labl::Labl(std::string const &nm, size_t in):
    name_(nm),
    index_{in}
{}
LabelManager::Labl::Labl(psc::Label const &lb, size_t ind):
    name_(lb.name.str),
    index_{ind}
{}
LabelManager::Labl::Labl(Labl &&lb) noexcept:
    name_(std::move(lb.name_)),
    index_{lb.index_}
{}
bool LabelManager::Labl::name_is_equals(std::string const &nm) const {
    return name_ == nm;
}
size_t LabelManager::Labl::get_labl_index() const {
    return index_;
}

void LabelManager::insert(psc::Label const &lb, size_t ind) {
    labls_.push_back(Labl{lb, ind});
}
bool LabelManager::has_labl(std::string const &nm) const {
    for (auto it{labls_.rbegin()}; it != labls_.rend(); ++it)
        if (it->name_is_equals(nm))
            return true;
    return false;
}
size_t LabelManager::get_labl_index(std::string const &nm) const {
    for (auto it{labls_.rbegin()}; it != labls_.rend(); ++it)
        if (it->name_is_equals(nm))
            return it->get_labl_index();
    throw std::domain_error("nm");
    return 0U;
}