#include "CharReader.h"

CharReader::CharReader(std::istream &input_stream):
    istr_{input_stream},
    c_{'\0'}
{}

char CharReader::getC() {
    char c{c_};
    istr_.read(&c_, 1);
    return c;
}
EnumCharType CharReader::getNextCharType() const {
    return UtilChar::getCharType(c_);
}
void CharReader::flushWhiteSpace() {
    while (this->getNextCharType() == EnumCharType::WHITESPACE)
        this->getC();
}
bool CharReader::nextCharIs(char c) const {
    return c_ == c;
}