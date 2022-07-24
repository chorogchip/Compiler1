#pragma once
#include<iostream>
#include"ParseTreeComponents.h"
#include"VMemoryPool.h"

class Interpreter {
private:
    psc::Program p_;
    std::ostream &out_;
    //VMemoryPool mem_;
public:
    Interpreter(psc::Program &&p, std::ostream &out);
    Interpreter(Interpreter const &) = delete;
    Interpreter &operator=(Interpreter const &) = delete;
    void interpret() const;
};

