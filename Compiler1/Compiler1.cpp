
#include<iostream>
#include<sstream>
#include"LexialAnalyzer.h"
#include"Parser.h"
#include"Instructor.h"
#include"Interpreter.h"
#include"test_programs.h"

int main()
{   

    std::istringstream ss{};
    ss.str(test3 + static_cast<char>(-1));

    LexialAnalyzer la{ss};
    Parser p{la, std::cout};
    bool res_parse{p.parse()};
    if (!res_parse) {
        std::cout << "instruct failed" << std::endl;
        return 0;
    }
    psc::Program pr{p.move_program()};

    Instructor in{std::move(pr), std::cout};
    bool res_instruct{in.instruct()};
    if (!res_instruct) {
        std::cout << "instruct failed" << std::endl;
        return 0;
    };
    InstructedProgram ipr = in.move_program();
    std::cout << ipr << std::endl;

    Interpreter ipt{std::move(ipr), std::cout};
    ipt.interpret();

    std::cout << "\nprogram end" << std::endl;
}

