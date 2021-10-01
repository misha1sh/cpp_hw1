#include <functional>
#include <iostream>
#include <map>

#include <src/big_number/big_number.h>

bool ValidateNumber(const std::string& number) {
    if (number.empty()) {
        std::cout << "Error: got empty string instead of number" << std::endl;
        return false;
    }

    size_t num_begin = 0;
    if (number[0] == '-') {
        num_begin++;
    }

    for (size_t i = num_begin; i < number.size(); i++) {
        if (number[i] < '0' || number[i] > '9') {
            std::cerr << "Error: got invalid character at pos " << i << "'" << number[i] << "'. Expected digit";
            return false;
        }
    }

    return true;
}

typedef std::function<std::string(const big_num::BigNumber&, const big_num::BigNumber&)> Operation;

bool ValidateOperation(const std::string& operation, const std::map<std::string, Operation>& operations) {
    if (operations.find(operation) != operations.end()) {
        return true;
    }
    std::cout << "Error: got invalid operation '" << operation << "'. Supported operations: ";
    for (const auto& op : operations) {
        std::cout << op.first << " ";
    }
    std::cout << std::endl;

    return false;
}

namespace supported_operations {
    auto bool_op(std::function<bool(const big_num::BigNumber&, const big_num::BigNumber&)> op) {
        return [op](const big_num::BigNumber& num1, const big_num::BigNumber& num2) {
            if (op(num1, num2)) {
                return "True";
            }
            return "False";
        };
    }
}

int main() {
    std::map<std::string, Operation> operations = {
        {"==", supported_operations::bool_op(
            [](const big_num::BigNumber& num1, const big_num::BigNumber& num2) {
                return num1 == num2;
        })},
        {"<=", supported_operations::bool_op(
            [](const big_num::BigNumber& num1, const big_num::BigNumber& num2) {
                return num1 <= num2;
        })},
        {">=", supported_operations::bool_op(
            [](const big_num::BigNumber& num1, const big_num::BigNumber& num2) {
                return num1 >= num2;
        })},
        {"<", supported_operations::bool_op(
            [](const big_num::BigNumber& num1, const big_num::BigNumber& num2) {
                return num1 < num2;
        })},
        {">", supported_operations::bool_op(
            [](const big_num::BigNumber& num1, const big_num::BigNumber& num2) {
                return num1 > num2;
        })},
        {"+", [](const big_num::BigNumber& num1, const big_num::BigNumber& num2) {
            return (num1 + num2).ToString();
        }},
        {"-", [](const big_num::BigNumber& num1, const big_num::BigNumber& num2) {
            return (num1 - num2).ToString();
        }},
        {"*", [](const big_num::BigNumber& num1, const big_num::BigNumber& num2) {
            return (num1 * num2).ToString();
        }},
        {"/", [](const big_num::BigNumber& num1, const big_num::BigNumber& num2) {
            try {
                return (num1 / num2).ToString();
            } catch (std::overflow_error& error) {
                return std::string(error.what());
            }
        }},
        {"%", [](const big_num::BigNumber& num1, const big_num::BigNumber& num2) {
            try {
                return (num1 % num2).ToString();
            } catch (std::overflow_error& error) {
                return std::string(error.what());
            }
        }},
    };

    std::string s1, op, s2;

    std::cout << "input first number: ";
    std::cin >> s1;
    if (!ValidateNumber(s1)) {
        return -1;
    }

    std::cout << "input operation: ";
    std::cin >> op;
    if (!ValidateOperation(op, operations)) {
        return -1;
    }


    std::cout << "input second number: ";
    std::cin >> s2;
    if (!ValidateNumber(s2)) {
        return -1;
    }

    big_num::BigNumber num1(s1);
    big_num::BigNumber num2(s2);

    std::cout << "result: " << (operations[op])(num1, num2);

    return 0;
}