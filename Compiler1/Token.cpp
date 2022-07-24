#include "Token.h"

Token::Token(EnumTokenType type): type_{type}, val_{} {}
Token::Token(EnumTokenType type, char val): type_{type}, val_({val}) {}
Token::Token(EnumTokenType type, std::string const &val): type_{type}, val_(val) {}
Token::Token(EnumTokenType type, std::string &&val): type_{type}, val_(std::move(val)) {}
Token::Token(Token const &t): type_{t.type_}, val_{t.val_} {}

Token &Token::operator=(Token const &t) {
    type_ = t.type_;
    val_ = t.val_;
    return *this;
}
Token::~Token() {}

bool Token::operator==(Token const &t) const {
    return type_ == t.type_ && val_ == t.val_;
}
bool Token::typeIsEquals(EnumTokenType type) const {
    return type_ == type;
}
bool Token::typeIsEquals(Token const &t) const {
    return type_ == t.type_;
}
bool Token::stringIsEquals(char const *str) const {
    int s{static_cast<int>(val_.size())};
    int i;
    for (i = 0; i != s; ++i)
        if (val_[i] != str[i])
            return false;
    return str[i] == '\0';   
}
std::ostream &operator<<(std::ostream &ostr, Token const &t) {
    return ostr << "type:[" << static_cast<int>(t.type_) << "] / val:[" << t.val_ << "] ";
}
std::string &&Token::move_string() noexcept {
    return std::move(val_);
}