#pragma once

enum class EnumCharType {
    WHITESPACE,
    DIGIT,
    ALPHABET,
    SYMBOL,
    END_INPUT,
    ERROR,
};

class UtilChar {
public:
    static constexpr bool isWhiteSpace(char c) {
        return c == ' ' || c == '\n' || c == '\r' || c == '\t';
    }
    static constexpr bool isAplhabetOrUnderBar(char c) {
        return 'a' <= c && c <= 'z' ||
               'A' <= c && c <= 'Z' ||
                           c == '_';
    }
    static constexpr bool isDigit(char c) {
        return '0' <= c && c <= '9';
    }
    static constexpr bool isSpecialSymbol(char c) {
        switch(c) {
        case '!': case '@': case '#': case '$': case '%': case '^': case '&': case '*':
        case '(': case ')': case '-': case '+': case '=': case '`': case '~':
        case'\'': case'\"': case ':': case ';': case '{': case '}': case '[': case ']':
        case '<': case '>': case ',': case '.': case '?': case '/': case '|': case'\\':
            return true;
        default: return false;
        }
    }
    static constexpr bool isEndOfFile(char c) {
        return c == -1 || c == '\0';
    }
    static constexpr EnumCharType getCharType(char c) {
        if (UtilChar::isWhiteSpace(c)) return EnumCharType::WHITESPACE;
        else if (UtilChar::isDigit(c)) return EnumCharType::DIGIT;
        else if (UtilChar::isAplhabetOrUnderBar(c)) return EnumCharType::ALPHABET;
        else if (UtilChar::isSpecialSymbol(c)) return EnumCharType::SYMBOL;
        else if (UtilChar::isEndOfFile(c)) return EnumCharType::END_INPUT;
        else return EnumCharType::ERROR;
    }
};