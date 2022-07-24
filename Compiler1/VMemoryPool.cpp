#include "VMemoryPool.h"

VMemoryPool::Mem::Mem(size_t st, size_t en):
    start_{st},
    end_{en},
    mem_{new int[en - st]}
{}
VMemoryPool::Mem::Mem(Mem &&m) noexcept :
    start_{m.start_},
    end_{m.end_},
    mem_{m.mem_}
{
    m.mem_ = nullptr;
}
VMemoryPool::Mem::~Mem() {
    if (mem_ != nullptr)
        delete[] mem_;
}
int &VMemoryPool::Mem::operator[](size_t i) {
    return mem_[i - start_];
}
bool VMemoryPool::Mem::operator<(size_t i) {
    return end_ <= i;
}

VMemoryPool::VMemoryPool():
    mem_(),
    back_{0U}
{}
int &VMemoryPool::operator[](size_t i) {
    if (mem_.empty()) {
        mem_.emplace_back(0, i + 100);
        back_ = i + 100;
        return mem_[0][i];
    } else if (mem_.back() < i) {
        mem_.emplace_back(back_, i + 100);
        back_ = i + 100;
        return mem_.back()[i];
    } else {
        size_t lo{0U}, md, hi{mem_.size() - 1};
        while (lo < hi) {
            md = (lo + hi + 1U) >> 1U;
            if (mem_[md] < i) hi = md - 1;
            else lo = md;
        }
        return mem_[lo][i];
    }
}