#pragma once
#include<iostream>

enum class EnumOperation : unsigned short {
    NOP = 0x0001,
    END = 0x0002,

    JMC = 0x0011,
    JIC = 0x0012,
    JNC = 0x0013,
    JMP = 0x0014,
    JIF = 0x0015,
    JNF = 0x0016,

    MOC = 0x0021,
    MOV = 0x0022,
    MOP = 0x0023,
    MOA = 0x0024,

    NEG = 0x0031,
    NOT = 0x0032,
    MNS = 0x0033,

    ADD = 0x0041,
    SUB = 0x0042,
    MUL = 0x0043,
    DIV = 0x0044,
    MOD = 0x0045,
    SHL = 0x0046,
    SHR = 0x0047,
    AND = 0x0048,
    ORR = 0x0049,
    XOR = 0x004A,
    BAN = 0x004B,
    BOR = 0x004C,

    EQL = 0x0061,
    NEQ = 0x0062,
    CMP = 0x0063,
    CME = 0x0064,
    RCP = 0x0065,
    RCE = 0x0066,

    RDI = 0x0091,
    RDC = 0x0092,
    GET = 0x0093,
    WRI = 0x0094,
    WRC = 0x0095,
    PUT = 0x0096,
};
