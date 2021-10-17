#pragma once

#include "functional"

#include "common.h"

namespace expression_evaluator::operators {

typedef std::function<TNumber(const TNumber&)> MonoOperation;
typedef std::function<TNumber(const TNumber&, const TNumber&)> BiOperation;

struct Operator {
    std::string name;
    int priority;
    std::optional<MonoOperation> mono_operation;
    std::optional<BiOperation> bi_operation;

    explicit Operator(std::string name_, int priority_)
            : name(std::move(name_)), priority(priority_), mono_operation(), bi_operation() {
    }

    Operator &Mono(MonoOperation mono_operation_) {
        mono_operation = mono_operation_;
        return *this;
    }

    Operator &Bi(BiOperation bi_operation_) {
        bi_operation = bi_operation_;
        return *this;
    }

    Operator &BiBool(std::function<bool(const TNumber&, const TNumber&)> op) {
        bi_operation = [op](const TNumber&num1, const TNumber&num2) {
            if (op(num1, num2)) {
                return TNumber(1);
            }
            return TNumber(0);
        };
        return *this;
    }
};

std::vector<operators::Operator> CreateDefaultOperators();

}  // namespace expression_evaluator::operators
