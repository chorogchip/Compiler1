#include "ByteCode.h"

ByteCode::ByteCode():
    op{EnumOperation::NOP},
    val1{0U},
    val2{0U}
{}
ByteCode::ByteCode(EnumOperation oper):
    op{oper},
    val1{0U},
    val2{0U}
{}
ByteCode::ByteCode(EnumOperation oper, size_t v1):
    op{oper},
    val1{v1},
    val2{0U}
{}
ByteCode::ByteCode(EnumOperation oper, size_t v1, size_t v2):
    op{oper},
    val1{v1},
    val2{v2}
{}