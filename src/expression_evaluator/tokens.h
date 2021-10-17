#pragma once

#include <variant>

#include "common.h"
#include "operators.h"

namespace expression_evaluator::tokens {

struct LeftBracket {
};

struct RightBracket {
};

struct OpToken {
    operators::Operator op;
    bool is_unary;
};

struct Token {
    typedef std::variant <OpToken, TNumber, LeftBracket, RightBracket> TokenType;

    Token(TokenType t) : token(std::move(t)) {}

    template<typename T>
    inline bool Is() const {
        return std::holds_alternative<T>(token);
    }

    template<typename T>
    inline const T *TryAs() const {
        return std::get_if<T>(&token);
    }

    template<typename T>
    inline T *TryAs() {
        return std::get_if<T>(&token);
    }

    template<typename T>
    inline const T &As() const {
        return std::get<T>(token);
    }

    TokenType token;
};

}  // namespace expressions_evaluator
