#pragma once
#include<vector>
#include<list>
#include<string>
#include<iostream>
#include <iomanip>
#include"EnumOperation.h"
#include"ByteCode.h"
#include"EnumOperation.h"
class InstructedProgram {
private:
    class OP_ {
    public:
        size_t index;
        bool is_first;
        std::string name;
        OP_(size_t, bool, std::string const &);
    };
    size_t total_memory_ = 0U;
    std::vector<ByteCode> code_;
    std::list<OP_> unindexed_op_;
    std::list<OP_> unindexed_op_compiler_;
public:
    InstructedProgram() = default;
    size_t get_size() const;
    void update_max_memory(size_t);
    void insert(ByteCode const &);
    void insert_unknown_op(ByteCode const &, bool, std::string const&);
    void insert_unknown_op_compiler(ByteCode const &, bool, std::string const&);
    void update_label_value(std::string const &);
    void update_label_value_compiler(std::string const &);
    bool has_left_unindexed() const;
    friend std::ostream& operator<<(std::ostream& out, InstructedProgram const &pr);
};

