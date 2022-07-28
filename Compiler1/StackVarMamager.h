#pragma once
#include<string>
#include<vector>
#include<any>
#include<iostream>
#include<stdexcept>
#include"ParseTreeComponents.h"

class StackVarMamager {
private:
    class Var {
    private:
        std::string name_;
        size_t index_;
    public:
        Var(std::string const &nm, size_t ind);
        Var(psc::Declare const &d);
        Var(Var const &) = default;
        Var(Var &&) noexcept;
        bool name_is_equals(std::string const &nm) const;
        size_t get_var_index() const;
    };
    class Block {
    private:
        std::vector<Var> vars_;
    public:
        Block() = default;
        void insert(Var &&) noexcept;
        bool has_var(std::string const &nm) const;
        size_t get_var_index(std::string const &nm) const;
    };
private:
    std::vector<Block> blocks_;
public:
    StackVarMamager();
    void insert(psc::Declare const &);
    void enter_block();
    void escape_block();
    size_t get_var_index(psc::ID const &name) const;
    bool has_var(std::string const &nm) const;
};

