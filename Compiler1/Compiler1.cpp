
#include<iostream>
#include<sstream>
#include"LexialAnalyzer.h"
#include"Parser.h"
#include"Instructor.h"

int main()
{   
    std::string str(R"asdf%%asdf(

int a : 1;
int b : 2;
a = 3;
b = a * 3;
for (int c : 3; c = 1;  c <= 10; c = c + 1) {
    b = b + 1;
    write b;
    writec 10;
}
if (a == 3) writec 65;
else writec 66;

)asdf%%asdf");
    str += -1;
    std::istringstream ss{};
    ss.str(str);

    LexialAnalyzer la{ss};
    Parser p{la, std::cout};
    bool res_parse{p.parse()};
    if (!res_parse) {
        std::cout << "instruct failed" << std::endl;
        return 0;
    }
    psc::Program pr{p.get_program()};

    Instructor in{pr, std::cout};
    bool res_instruct{in.instruct()};
    if (!res_instruct) {
        std::cout << "instruct failed" << std::endl;
        return 0;
    }
    InstructedProgram ipr{in.get_program()};

    std::cout << ipr << std::endl;
}

