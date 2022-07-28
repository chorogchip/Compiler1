#pragma once
#include<vector>
class VMemoryPool {
private:
    class Mem {
    private:
        size_t start_;
        size_t end_;
        int *mem_;
    public:
        Mem() = delete;
        Mem(Mem const &) = delete;
        Mem(Mem &&) noexcept;
        Mem(size_t st, size_t en);
        ~Mem();
        Mem &operator=(Mem const &) = delete;
        int &operator[](size_t i);
        bool operator<(size_t i);
    };
    std::vector<Mem> mem_;
    size_t back_;
public:
    VMemoryPool();
    VMemoryPool(VMemoryPool const &) = delete;
    VMemoryPool &operator=(VMemoryPool const &) = delete;
    int &operator[](size_t i);
};
