#pragma once
#include<string>
#include<vector>
#include<any>
#include<iostream>
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
    };

    class Label {
    private:
        std::string name_;
    public:
        Label(std::string const &nm);
        Label(psc::STLabel const &l);
        Label(Label const &) = default;
        Label(Label &&) noexcept;
        bool name_is_equals(std::string const &nm) const;
    };

    class Block {
    private:
        std::vector<Var> vars_;
        std::vector<Label> labels_;
    public:
        Block() = default;
        void insert(Var &&) noexcept;
        void insert(Label &&) noexcept;
        bool hasVar(std::string const &nm) const;
        bool hasLabel(std::string const &nm) const;
    };
private:
    psc::Program const &pr_;
    std::ostream &errout_;
    std::vector<Block> blocks_;
    size_t current_block_;

    void read_program();
public:
    StackVarMamager(psc::Program const &, std::ostream &);
};

