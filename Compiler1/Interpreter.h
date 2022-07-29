#pragma once
#include<iostream>
#include"ByteCode.h"
#include"InstructedProgram.h"

class Interpreter {
public:
    typedef ByteCode::data data;
private:
    InstructedProgram const p_;
    std::ostream &out_;
    data *mem_;
public:
    Interpreter(InstructedProgram &&, std::ostream &);
    ~Interpreter();
    Interpreter(Interpreter const &) = delete;
    Interpreter &operator=(Interpreter const &) = delete;
    void interpret();
};