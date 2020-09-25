#pragma once

#include <exception>

#include <tokenizer.h>

/*
    number: CONSTANT | (expr)
    factor: number | +factor | -factor
    term: factor | factor * term | factor / term
    expr: term | term + expr | term - expr
*/

class Parser {
public:
    Parser(Tokenizer* tokenizer) : tok_(tokenizer) {
        if (tok_ == nullptr) {
            throw std::invalid_argument("Parser cannot be constructed from nullptr");
        }
    }

    double Evaluate() {
        if (tok_->Eof()) {
            return 0;
        }
        auto result = Expr();
        if (!tok_->Eof()) {
            throw std::runtime_error("Expected end of stream");
        }
        return result;
    }

private:
    double Number() {
        auto token = tok_->GetToken();
        if (token == TokenType::kNumber) {
            return tok_->GetValueAndNext();
        }
        if (token != TokenType::kOpenBracket) {
            throw std::runtime_error("Expected open bracket");
        }
        tok_->Next();
        auto expr = Expr();
        auto close = tok_->GetTokenAndNext();
        if (close != TokenType::kCloseBracket) {
            throw std::runtime_error("Expected close bracket");
        }
        return expr;
    }

    double Fact() {
        auto token = tok_->GetToken();
        if (token == TokenType::kAdd || token == TokenType::kSub) {
            tok_->Next();
            auto fact = Fact();
            if (token == TokenType::kSub) {
                return -fact;
            }
            return fact;
        }
        auto number = Number();
        return number;
    }

    double Term() {
        double fact = Fact();
        auto token = tok_->GetToken();
        if (token == TokenType::kMul || token == TokenType::kDiv) {
            tok_->Next();
            auto term = Term();
            if (token == TokenType::kMul) {
                return fact * term;
            }
            if (term == 0) {
                throw std::runtime_error("Division by zero");
            }
            return fact / term;
        }
        return fact;
    }

    double Expr() {
        double res = Term();
        auto token = tok_->GetToken();
        if (token == TokenType::kAdd || token == TokenType::kSub) {
            tok_->Next();
            auto expr = Expr();
            if (token == TokenType::kAdd) {
                return res + expr;
            }
            return res - expr;
        }
        return res;
    }

private:
    Tokenizer* tok_;
};
