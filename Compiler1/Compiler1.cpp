
#include<iostream>
#include<sstream>
#include"LexialAnalyzer.h"

int main()
{   
    std::string str = "1 123 int do while for fore iif func function return retun 123A2 adasdk2 skdk22313+kdsad<=>>2313/32";
    str += -1;
    std::istringstream ss;
    ss.str(str);
    LexialAnalyzer la(ss);
    Token t(EnumTokenType::T_ERROR_ON_ANALYZER);

    la.startReading();
    do std::cout << (t = la.getToken()) << std::endl;
    while (!t.typeIsEquals(EnumTokenType::T_EOF));
}

