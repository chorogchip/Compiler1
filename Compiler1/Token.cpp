#include "Token.h"

Token::Token(EnumTokenType type): type_(type), val_() {}
Token::Token(EnumTokenType type, char val): type_(type), val_("") {
    val_ += val;
}
Token::Token(EnumTokenType type, std::string& val): type_(type), val_(val) {}
Token::Token(EnumTokenType type, std::string&& val): type_(type) {
    this->val_ = std::move(val);
}
Token::Token(const Token& t): type_(t.type_), val_(t.val_) {}

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
bool Token::typeIsEquals(const Token& t) const {
    return this->type_ == t.type_;
}
bool Token::stringIsEquals(const char* str) const {
    int s = static_cast<int>(this->val_.size());
    int i;
    for (i = 0; i != s; ++i)
        if (this->val_[i] != str[i])
            return false;
    return str[i] == '\0';   
}
std::ostream& operator<<(std::ostream& ostr, const Token& t) {
    return ostr << "type:[" << (int)t.type_ << "] / val:[" << t.val_ << "] ";
}