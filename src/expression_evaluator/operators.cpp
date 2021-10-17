#include "operators.h"

namespace expression_evaluator::operators {

std::vector<Operator> CreateDefaultOperators() {
    return {
            Operator("==", 0)
                    .BiBool([](const TNumber &num1, const TNumber &num2) {
                        return num1 == num2;
                    }),
            Operator("<=", 0)
                    .BiBool([](const TNumber &num1, const TNumber &num2) {
                        return num1 <= num2;
                    }),
            Operator(">=", 0)
                    .BiBool([](const TNumber &num1, const TNumber &num2) {
                        return num1 >= num2;
                    }),
            Operator("<", 0)
                    .BiBool([](const TNumber &num1, const TNumber &num2) {
                        return num1 < num2;
                    }),
            Operator(">", 0)
                    .BiBool([](const TNumber &num1, const TNumber &num2) {
                        return num1 > num2;
                    }),
            Operator("+", 1)
                    .Bi([](const TNumber &num1, const TNumber&num2) {
                        return num1 + num2;
                    })
                    .Mono([](const TNumber &num) {
                        return +num;
                    }),
            Operator("-", 1)
                    .Bi([](const TNumber &num1, const TNumber &num2) {
                        return num1 - num2;
                    })
                    .Mono([](const TNumber &num) {
                        return -num;
                    }),
            Operator("*", 2)
                    .Bi([](const TNumber &num1, const TNumber &num2) {
                        return num1 * num2;
                    }),
            Operator("/", 2)
                    .Bi([](const TNumber &num1, const TNumber &num2) {
                        return num1 / num2;
                    }),
            Operator("%", 2)
                    .Bi([](const TNumber &num1, const TNumber &num2) {
                        return num1 % num2;
                    }),
    };
}

}  // namespace expression_evaluator::operations
