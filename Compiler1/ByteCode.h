#pragma once
#include"EnumOperation.h"
class ByteCode {
public:
    typedef long long data;
public:
    EnumOperation op;
    data val1;
    data val2;
    ByteCode();
    ByteCode(EnumOperation);
    ByteCode(EnumOperation, size_t);
    ByteCode(EnumOperation, size_t, size_t);
};