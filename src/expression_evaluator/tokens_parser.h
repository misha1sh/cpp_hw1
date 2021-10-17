#pragma once

#include <map>
#include <vector>
#include <string>
#include <string_view>

#include "tokens.h"

namespace expression_evaluator::tokens {

class TokensParser {
public:
    explicit TokensParser(const std::vector<operators::Operator>& operators);

    std::vector<Token> ParseString(const std::string& input) const;
private:
    std::optional<std::pair<Token, size_t>>
        FindNextToken(const std::string &input, size_t token_start) const;
    std::optional<Token> ParseToken(const std::string_view &token) const;

    std::map<std::string, operators::Operator> supported_operators_;
};

}  // expression_evaluator::tokens
