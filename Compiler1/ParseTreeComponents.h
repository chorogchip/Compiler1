#pragma once
#include<vector>
#include<string>

using namespace std;
struct Program {
    vector<Function> functions;
};
struct Function {
    Type returnType;
    vector<FunctionInput> inputs;
    vector<Statement> statements;
};
struct FunctionInput {
    Type type;
    Id name;
};

struct Statement {
    
};
typedef enum class EnumType { INT } Type;
typedef string Id;
