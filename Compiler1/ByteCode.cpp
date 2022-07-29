#include "ByteCode.h"

ByteCode::ByteCode():
    op{EnumOperation::NOP},
    val1{static_cast<data>(0)},
    val2{static_cast<data>(0)}
{}
ByteCode::ByteCode(EnumOperation oper):
    op{oper},
    val1{static_cast<data>(0)},
    val2{static_cast<data>(0)}
{}
ByteCode::ByteCode(EnumOperation oper, size_t v1):
    op{oper},
    val1{static_cast<data>(v1)},
    val2{static_cast<data>(0)}
{}
ByteCode::ByteCode(EnumOperation oper, size_t v1, size_t v2):
    op{oper},
    val1{static_cast<data>(v1)},
    val2{static_cast<data>(v2)}
{}