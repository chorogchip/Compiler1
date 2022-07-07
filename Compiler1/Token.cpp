#include "Token.h"

Token::Token(EnumTokenType type, std::string& val) {
    this->type_ = type;
    this->val_ = val;
}
Token::Token(EnumTokenType type, std::string&& val) {
    this->type_ = type;
    this->val_ = std::move(val);
}
Token::Token(const Token& t) {
    this->type_ = t.type_;
    this->val_ = t.val_;
}
Token& Token::operator=(const Token& t) {
    this->type_ = t.type_;
    this->val_ = t.val_;
    return *this;
}
Token::~Token() {}

bool Token::operator==(const Token& t) const {
    return this->type_ == t.type_ && this->val_ == t.val_;
}
bool Token::typeIsEquals(EnumTokenType type) const {
    return this->type_ == type;
}