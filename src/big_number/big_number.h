#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <sstream>

#include "common.h"

namespace big_num {

class BigNumber {
public:
    BigNumber();
    explicit BigNumber(const std::string& number);
    template <typename Arithmetic,
              typename = typename std::enable_if<std::is_arithmetic<Arithmetic>::value, Arithmetic>::type>
    BigNumber(const Arithmetic number) : BigNumber(std::to_string(number)) {}
    BigNumber(const BigNumber& other) = default;
    BigNumber(BigNumber&& other) = default;
    BigNumber& operator=(const BigNumber& bigNumber) = default;
    BigNumber& operator=(BigNumber&& bigNumber) = default;

    std::string ToString() const;

    BigNumber operator+(const BigNumber& other) const;
    BigNumber operator-(const BigNumber& other) const;

    BigNumber operator*(const BigNumber& other) const;
    BigNumber operator/(const BigNumber& other) const;
    BigNumber operator%(const BigNumber& other) const;

    BigNumber operator+() const;
    BigNumber operator-() const;

    bool operator<(const BigNumber& other) const;
    bool operator>(const BigNumber& other) const;
    bool operator<=(const BigNumber& other) const;
    bool operator>=(const BigNumber& other) const;
    bool operator==(const BigNumber& other) const;

    friend std::istream& operator>>(std::istream& in, BigNumber& bigNumber);
    friend std::ostream& operator<<(std::ostream& out, const BigNumber& bigNumber);
private:
    using TSign = common::TSign;
    using TValue = common::TValue;
    using TVector = common::TVector;

    BigNumber(TSign sign, std::vector<TValue> values);
    void Trim();
    static TSign Compare(const BigNumber& left, const BigNumber& right);

    TSign sign_;
    TVector values_;
};

}  // namespace big_num
