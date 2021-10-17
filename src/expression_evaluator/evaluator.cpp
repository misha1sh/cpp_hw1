#include "evaluator.h"

#include <stack>


namespace expression_evaluator {

using namespace tokens;

void ApplyTopOperator(std::stack<big_num::BigNumber>& numbers, std::stack<Token>& operators) {
    if (operators.empty()) {
        throw std::logic_error("Unable to apply operator");
    }
    const auto token = operators.top().As<OpToken>();
    const auto& op = token.op;
    const bool is_unary = token.is_unary;
    operators.pop();
    if (is_unary) {
        if (!op.mono_operation) {
            throw std::logic_error("Operator " + op.name + " is not unary");
        }
        if (numbers.empty()) {
            throw std::logic_error("Unable to apply unary operator " + op.name);
        }

        auto old_number = numbers.top();
        auto new_number = (*op.mono_operation)(old_number);
        numbers.pop();
        numbers.push(new_number);
    } else {
        if (!op.bi_operation) {
            throw std::logic_error("Operator " + op.name + " is not binary");
        }
        if (numbers.size() < 2) {
            throw std::logic_error("Unable to apply binary operator " + op.name);
        }

        auto old_number1 = numbers.top();
        numbers.pop();
        auto old_number2 = numbers.top();
        numbers.pop();
        auto new_number = (*op.bi_operation)(old_number2, old_number1);
        numbers.push(new_number);
    }
}

void ApplyOperatorWithLowerPriority(std::stack<big_num::BigNumber>& numbers, std::stack<Token>& operators,
                                    const int priority) {
    while (!operators.empty()) {
        auto *prev_op = operators.top().TryAs<OpToken>();
        if (prev_op && !prev_op->is_unary &&
            prev_op->op.priority >= priority) {
            ApplyTopOperator(numbers, operators);
        } else {
            break;
        }

    }
}

void ApplyUnaryOperators(std::stack<big_num::BigNumber>& numbers, std::stack<Token>& operators) {
    while (!operators.empty()) {
        auto *prev_op = operators.top().TryAs<OpToken>();
        if (prev_op && prev_op->is_unary) {
            ApplyTopOperator(numbers, operators);
        } else {
            break;
        }
    }
}

void ApplyOperatorsTillLeftBracket(std::stack<big_num::BigNumber>& numbers, std::stack<Token>& operators) {
    while (!operators.empty() && !operators.top().Is<LeftBracket>()) {
        ApplyTopOperator(numbers, operators);
    }

    if (operators.empty()) {
        throw std::logic_error("Unable to find matching `(` to `)`");
    }
    operators.pop(); // pop `(`
}

void ApplyRemainingOperators(std::stack<big_num::BigNumber>& numbers, std::stack<Token>& operators) {
    while (!operators.empty()) {
        if (operators.top().Is<LeftBracket>()) {
            throw std::logic_error("Unable to find matching `)` to `(`");
        }
        ApplyTopOperator(numbers, operators);
    }
}

TNumber ExpressionsEvaluator::EvaluateExpression(const std::string &expression) const {

    const auto tokens = tokens_parser_.ParseString(expression);

    std::stack<TNumber> numbers;
    std::stack<Token> operators;
    for (const auto &token : tokens) {
        if (auto *op = token.TryAs<OpToken>()) {
            if (op->is_unary) {
                operators.push(token);
            } else {
                ApplyOperatorWithLowerPriority(numbers, operators, op->op.priority);
                operators.push(token);
            }

            continue;
        }

        if (auto *num = token.TryAs<TNumber>()) {
            numbers.push(*num);
            ApplyUnaryOperators(numbers, operators);

        } else if (token.Is<LeftBracket>()) {
            operators.push(token);
        } else if (token.Is<RightBracket>()) {
            ApplyOperatorsTillLeftBracket(numbers, operators);
        }

    }

    ApplyRemainingOperators(numbers, operators);

    if (numbers.empty()) {
        throw std::logic_error("There is no number");
    }

    if (numbers.size() > 1) {
        throw std::logic_error("Too many numbers");
    }

    return numbers.top();
}

}  // namespace expressions_evaluator
