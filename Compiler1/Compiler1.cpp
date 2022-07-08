
#include<iostream>
#include<sstream>
#include"LexialAnalyzer.h"

int main()
{   
    std::string str = "1 123 123A2 adasdk2 skdk22313+kdsad<=>>2313/32";
    str += -1;
    std::istringstream ss;
    ss.str(str);
    LexialAnalyzer la(ss);
    la.startReading();
    Token t(EnumTokenType::T_DO);
    do {
        t = la.getToken();
        std::cout << t;
    } while (!t.typeIsEquals(EnumTokenType::T_EOF));
}

