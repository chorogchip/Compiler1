#pragma once
#include<iostream>
#include<string>
#include"UtilChar.h"
#include"Token.h"
#include"CharReader.h"

class LexialAnalyzer {
private:
    CharReader cr_;
    std::string readDigit();
    std::string readAlphabet();
    Token filterKeywordsFromAlphabetToken(Token&& t);
    Token readSymbol();

public:
    LexialAnalyzer(std::istream& input_stream);
    ~LexialAnalyzer();
    void startReading();
    Token getToken();

};

