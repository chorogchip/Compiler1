#pragma once
#include"EnumOperation.h"
class ByteCode {
public:
    EnumOperation op;
    size_t val1;
    size_t val2;
    ByteCode();
    ByteCode(EnumOperation);
    ByteCode(EnumOperation, size_t);
    ByteCode(EnumOperation, size_t, size_t);
};