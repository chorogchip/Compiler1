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
        Var(const std::string& nm, size_t ind);
        Var(const psc::Declare& d);
        Var(const Var&) = default;
        Var(Var&&) noexcept;
        bool name_is_equals(const std::string& nm) const;
    };

    class Label {
    private:
        std::string name_;
    public:
        Label(const std::string nm);
        Label(const psc::STLabel& l);
        Label(const Label&) = default;
        Label(Label&&) noexcept;
        bool name_is_equals(const std::string& nm) const;
    };

    class Block {
    private:
        std::vector<Var> vars_;
        std::vector<Label> labels_;
    public:
        Block() = default;
        void insert(Var&&) noexcept;
        void insert(Label&&) noexcept;
        bool hasVar(const std::string& nm) const;
        bool hasLabel(const std::string& nm) const;
    };
private:
    const psc::Program& pr_;
    std::ostream& errout_;
    std::vector<Block> blocks_;
    size_t current_block_;

    void read_program();
public:
    StackVarMamager(const psc::Program&, std::ostream&);
};

