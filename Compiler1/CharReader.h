#pragma once
#include<iostream>
#include"UtilChar.h"

class CharReader {
private:
    std::istream& istr_;
    char c_;
public:
    CharReader(std::istream& input_stream);
    ~CharReader();
    char getC();
    EnumCharType getNextCharType() const;
    bool nextCharIs(char c) const;
    void flushWhiteSpace();
};

