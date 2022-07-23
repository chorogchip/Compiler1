#include "LexialAnalyzer.h"

LexialAnalyzer::LexialAnalyzer(std::istream& input_stream):
    cr_{input_stream}
{}

void LexialAnalyzer::startReading() {
    cr_.getC();
}
Token LexialAnalyzer::getToken() {
    cr_.flushWhiteSpace();
    switch (cr_.getNextCharType()) {
    case EnumCharType::END_INPUT: return Token(EnumTokenType::T_EOF);
    case EnumCharType::DIGIT:     return Token(EnumTokenType::T_LITERAL_INT, this->readDigit());
    case EnumCharType::ALPHABET:
        return this->filterKeywordsFromAlphabetToken(
            Token(EnumTokenType::T_VARIABLE, this->readAlphabet()));
    case EnumCharType::SYMBOL: return this->readSymbol();
    case EnumCharType::ERROR:  return Token(EnumTokenType::T_ERROR_ON_READER, cr_.getC());
    default:                   return Token(EnumTokenType::T_ERROR_ON_ANALYZER, cr_.getC());
    }
    return Token(EnumTokenType::T_ERROR_ON_ANALYZER);
}

std::string LexialAnalyzer::readDigit() {
    std::string res = {""};
    do res += cr_.getC();
    while (cr_.getNextCharType() == EnumCharType::DIGIT ||
           cr_.getNextCharType() == EnumCharType::ALPHABET);
    return res;
}
std::string LexialAnalyzer::readAlphabet() {
    std::string res = {""};
    do res += cr_.getC();
    while (cr_.getNextCharType() == EnumCharType::DIGIT ||
           cr_.getNextCharType() == EnumCharType::ALPHABET);
    return res;
}
Token LexialAnalyzer::filterKeywordsFromAlphabetToken(const Token& t) const {
         if (t.stringIsEquals("int"))      return Token{EnumTokenType::T_DATATYPE, Token::STR_INT};
    else if (t.stringIsEquals("if"))       return Token{EnumTokenType::T_IF};
    else if (t.stringIsEquals("else"))     return Token{EnumTokenType::T_ELSE};
    else if (t.stringIsEquals("while"))    return Token{EnumTokenType::T_WHILE};
    else if (t.stringIsEquals("for"))      return Token{EnumTokenType::T_FOR};
    else if (t.stringIsEquals("do"))       return Token{EnumTokenType::T_DO};
    else if (t.stringIsEquals("read"))     return Token{EnumTokenType::T_READ};
    else if (t.stringIsEquals("write"))    return Token{EnumTokenType::T_WRITE};
    else if (t.stringIsEquals("writec"))   return Token{EnumTokenType::T_WRITEC};
    else if (t.stringIsEquals("goto"))     return Token{EnumTokenType::T_GOTO};
    else if (t.stringIsEquals("label"))    return Token{EnumTokenType::T_LABEL};
    else return t;
}
Token LexialAnalyzer::readSymbol() {
    std::string ret = "";
    ret += cr_.getC();
    switch (ret[0]) {
    case '|': if (cr_.nextCharIs('|')) return Token{EnumTokenType::T_OPERATION_BIN, ret + cr_.getC()};
         else return Token{EnumTokenType::T_OPERATION_BIN, ret};
    case '&': if (cr_.nextCharIs('&')) return Token{EnumTokenType::T_OPERATION_BIN, ret + cr_.getC()};
         else return Token{EnumTokenType::T_OPERATION_BOTH, ret};
    case '^': return Token{EnumTokenType::T_OPERATION_BIN, ret};
    case '>': if (cr_.nextCharIs('=')) return Token{EnumTokenType::T_OPERATION_BIN, ret + cr_.getC()};
         else if (cr_.nextCharIs('>')) return Token{EnumTokenType::T_OPERATION_BIN, ret + cr_.getC()};
         else return Token{EnumTokenType::T_OPERATION_BIN, ret};
    case '<': if (cr_.nextCharIs('=')) return Token{EnumTokenType::T_OPERATION_BIN, ret + cr_.getC()};
         else if (cr_.nextCharIs('<')) return Token{EnumTokenType::T_OPERATION_BIN, ret + cr_.getC()};
         else return Token{EnumTokenType::T_OPERATION_BIN, ret};
    case '!': if (cr_.nextCharIs('=')) return Token{EnumTokenType::T_OPERATION_BIN, ret + cr_.getC()};
            else return Token{EnumTokenType::T_OPERATION_UN, ret};
    case '=': if (cr_.nextCharIs('=')) return Token{EnumTokenType::T_OPERATION_BIN, ret + cr_.getC()};
            else return Token{EnumTokenType::T_ASSIGN, ret};
    case '+': return Token{EnumTokenType::T_OPERATION_BOTH, ret};
    case '-': return Token{EnumTokenType::T_OPERATION_BOTH, ret};
    case '*': return Token{EnumTokenType::T_OPERATION_BIN, ret};
    case '/': return Token{EnumTokenType::T_OPERATION_BIN, ret};
    case '%': return Token{EnumTokenType::T_OPERATION_BIN, ret};
    case '~': return Token{EnumTokenType::T_OPERATION_UN, ret};

    case '(': return Token{EnumTokenType::T_PAREN_L, ret};
    case ')': return Token{EnumTokenType::T_PAREN_R, ret};
    case '{': return Token{EnumTokenType::T_BRACE_L, ret};
    case '}': return Token{EnumTokenType::T_BRACE_R, ret};
    case ':': return Token{EnumTokenType::T_COLON, ret};
    case ';': return Token{EnumTokenType::T_SEMICOLON, ret};
    default:  return Token{EnumTokenType::T_ERROR_ON_ANALYZER, ret};
    }
    return Token{EnumTokenType::T_ERROR_ON_ANALYZER, ret};
}