#include <functional>
#include <iostream>
#include <map>
#include <variant>
#include <stack>

#include <big_number.h>
#include <evaluator.h>



int main() {
    expression_evaluator::ExpressionsEvaluator evaluator;

    std::cout << "type expression: ";

    std::string expression;
    std::getline(std::cin, expression);

    try {
        std::cout << "Calculation result: " << evaluator.EvaluateExpression(expression);
    } catch (std::exception& exception) {
        std::cout << "Error. "  << exception.what();
    }

    return 0;
}