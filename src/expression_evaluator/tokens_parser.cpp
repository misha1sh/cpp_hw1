#include "tokens_parser.h"

#include <string_view>

namespace expression_evaluator::tokens {

inline bool IsDigit(char c) {
    return '0' <= c && c <= '9';
}

inline bool IsSpace(char c) {
    return c == ' ' || c == '\t';
}

std::string_view TrimSpaces(const std::string_view &token) {
    size_t first_not_space_pos;
    for (first_not_space_pos = 0; first_not_space_pos < token.size(); first_not_space_pos++) {
        if (!IsSpace(token[first_not_space_pos])) {
            break;
        }
    }
    if (first_not_space_pos == token.size()) {
        return "";
    }

    size_t last_not_space_pos;
    for (last_not_space_pos = token.size() - 1; last_not_space_pos >= 0; last_not_space_pos--) {
        if (!IsSpace(token[last_not_space_pos])) {
            break;
        }
    }

    return token.substr(first_not_space_pos, last_not_space_pos - first_not_space_pos + 1);
}

void SetUnaryAttributes(std::vector<Token> &tokens) {
    bool last_was_op = true;
    for (auto &token : tokens) {
        if (auto *op = token.TryAs<OpToken>()) {
            op->is_unary = last_was_op;
            last_was_op = true;
        } else if (token.Is<LeftBracket>()) {
            // we can use unary operator after left bracket
            last_was_op = true;
        } else {
            last_was_op = false;
        }
    }
}

std::optional<Token> TokensParser::ParseToken(const std::string_view &token) const {
    if (token == "(") {
        return std::make_optional<Token>(LeftBracket{});
    } else if (token == ")") {
        return std::make_optional<Token>(RightBracket{});
    } else if (auto op = supported_operators_.find(std::string(token));
               op != supported_operators_.end()) {
        return std::make_optional<Token>(OpToken{op->second, false});
    } else if (IsDigit(token[0])) {
        try {
            return std::make_optional<Token>(TNumber(token));
        } catch (const std::invalid_argument &argument) {
            return std::nullopt;
        }
    }
    return std::nullopt;
}

std::optional<std::pair<Token, size_t>>
TokensParser::FindNextToken(const std::string &input, size_t token_start) const {
    std::optional<std::pair<Token, size_t>> prev_good_token;
    for (size_t i = token_start; i < input.size(); i++) {
        auto new_token = ParseToken(TrimSpaces(input.substr(token_start, i - token_start + 1)));
        if (new_token) {
            prev_good_token = {
                    *new_token,
                    i + 1
            };
        }
    }

    return prev_good_token;
}

std::vector<Token> TokensParser::ParseString(const std::string &input) const {
    std::vector<Token> res;
    size_t token_start = 0;
    while (token_start < input.size()) {
        auto token = FindNextToken(input, token_start);
        if (token.has_value()) {
            res.push_back(token->first);
            token_start = token->second;
        } else {
            throw std::logic_error("Unable to parse expression: `" + input.substr(token_start) + "`");
        }
    }

    SetUnaryAttributes(res);

    return res;

}

TokensParser::TokensParser(
        const std::vector<operators::Operator> &operators)
    : supported_operators_() {
    for (auto& op : operators) {
        supported_operators_.insert({op.name, op});
    }
}

}  // namespace expression_evaluator::tokens
