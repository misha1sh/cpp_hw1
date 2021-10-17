#pragma once

#include <map>
#include <string>
#include <vector>

#include "operators.h"
#include "tokens_parser.h"

namespace expression_evaluator {

class ExpressionsEvaluator {
public:
    explicit ExpressionsEvaluator(const std::vector<operators::Operator>& operators)
        : tokens_parser_(operators) {
    }
    ExpressionsEvaluator() : ExpressionsEvaluator(operators::CreateDefaultOperators()) {
    }

    TNumber EvaluateExpression(const std::string& expression) const;

private:
    tokens::TokensParser tokens_parser_;
};

}  // namespace expression_evaluator

