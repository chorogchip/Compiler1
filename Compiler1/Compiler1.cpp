
#include<iostream>
#include<sstream>
#include"LexialAnalyzer.h"
#include"Parser.h"

int main()
{   
    std::string str {"1 123 int do while for fore iif func function return\
retun 123A2 adasdk2 skdk22313+kdsad<=>>2313/32"};
    str += -1;
    std::istringstream ss;
    ss.str(str);

    LexialAnalyzer la{ss};
    Parser p{la, std::cout};
    p.parse();
}

