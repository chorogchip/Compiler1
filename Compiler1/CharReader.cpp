#include "CharReader.h"

CharReader::CharReader(std::istream& input_stream)
    : istr_(input_stream), c_('\0') {

}
CharReader::~CharReader() {}
char CharReader::getC() {
    char c = this->c_;
    istr_.read(&c_, 1);
    //std::cout << "read :" << (int)c_ << "\n";
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
    return this->c_ == c;
}