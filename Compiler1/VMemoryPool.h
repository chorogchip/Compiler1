#pragma once/*
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
        Mem(const Mem&) = delete;
        Mem(size_t st, size_t en);
        ~Mem();
        Mem& operator=(const Mem&) = delete;
        int& operator[](size_t i);
        bool operator<(size_t i);
    };
    std::vector<Mem> mem_;
    size_t back_;
public:
    VMemoryPool();
    VMemoryPool(const VMemoryPool&) = delete;
    ~VMemoryPool() = default;
    VMemoryPool& operator=(const VMemoryPool&) = delete;
    int& operator[](size_t i);
};

*/