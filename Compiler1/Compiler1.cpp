
#include<iostream>
#include<sstream>
#include"LexialAnalyzer.h"
#include"Parser.h"

int main()
{   
    std::string str {"int a : 1; int b : 2; a = 3; b = a + 3;"};
    str += -1;
    std::istringstream ss;
    ss.str(str);

    LexialAnalyzer la{ss};
    Parser p{la, std::cout};
    p.parse();
}

