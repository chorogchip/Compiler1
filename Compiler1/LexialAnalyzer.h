#pragma once
#include<iostream>
#include<string>
#include"Token.h"

class LexialAnalyzer {
private:
    std::istream& istr_;
    char c_;
public:
    LexialAnalyzer(std::istream& input_stream);
    ~LexialAnalyzer();
    Token getToken();

};

