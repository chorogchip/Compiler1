#pragma once
#include<iostream>
#include"VMemoryPool.h"
#include"ParseTreeComponents.h"

class Interpreter {
private:
    psc::Program p_;
    std::ostream& out_;
    //VMemoryPool mem_;
public:
    Interpreter(psc::Program&& p, std::ostream& out);
    Interpreter(const Interpreter&) = delete;
    ~Interpreter() = default; 
    Interpreter& operator=(const Interpreter&) = delete;
    void interpret() const;
};

