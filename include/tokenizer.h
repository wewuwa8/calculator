#pragma once

#include <istream>
#include <exception>
#include <cctype>

enum class TokenType {
    kEof = '\0',
    kUnknown,
    kNumber,
    kOpenBracket = '(',
    kCloseBracket = ')',
    kMul = '*',
    kDiv = '/',
    kAdd = '+',
    kSub = '-',
};

class Tokenizer {
public:
    Tokenizer(std::istream* in) : in_(in) {
        if (in_ == nullptr) {
            throw std::invalid_argument("Tokenizer cannot be constructed from nullptr");
        }
        Next();
    }

    void Next() {
        /* skip spaces */
        while (in_->peek() != EOF && std::isspace(in_->peek())) {
            in_->get();
        }
        char c = in_->peek();

        if (c == EOF) {
            token_type_ = TokenType::kEof;
            return;
        }

        if (isdigit(c)) {
            token_type_ = TokenType::kNumber;
            double integer_part = 0;
            double fraction_part = 0;
            while (in_->peek() != EOF && isdigit(in_->peek())) {
                integer_part = 10 * integer_part + (in_->get() - '0');
            }

            // handle floats
            if (in_->peek() == '.' || in_->peek() == ',') {
                in_->get();
                double denom = 0.1;
                if (!isdigit(in_->peek())) {
                    throw std::runtime_error("Expected digit after point in floating number");
                }
                while (in_->peek() != EOF && isdigit(in_->peek())) {
                    fraction_part += denom * (in_->get() - '0');
                    denom *= 0.1;
                }
            }
            value_ = integer_part + fraction_part;
            return;
        }

        switch (c) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '(':
            case ')':
                in_->get();
                token_type_ = static_cast<TokenType>(c);
                return;
        }

        throw std::runtime_error("Unexpected symbol");        
    }

    TokenType GetToken() const noexcept {
        return token_type_;
    }

    double GetValue() const noexcept {
        return value_;
    }

    bool Eof() const noexcept {
        return token_type_ == TokenType::kEof;
    }

    TokenType GetTokenAndNext() {
        auto retval = token_type_;
        Next();
        return retval;
    }

    double GetValueAndNext() {
        auto retval = value_;
        Next();
        return retval;
    }

private:
    std::istream* in_;
    double value_;
    TokenType token_type_;
};
