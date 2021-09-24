#pragma once

#include <vector>
#include <cstdint>
#include <string>

namespace big_num {

class BigNumber {

public:
    explicit BigNumber(const std::string& number);
    BigNumber(const BigNumber& other) = default;
    BigNumber(BigNumber&& other) = default;

    std::string ToString() const;

    BigNumber operator+(const BigNumber& other) const;
    BigNumber operator-(const BigNumber& other) const;

    BigNumber operator+() const;
    BigNumber operator-() const;

    bool operator<(const BigNumber& other) const;
    bool operator>(const BigNumber& other) const;
    bool operator<=(const BigNumber& other) const;
    bool operator>=(const BigNumber& other) const;
    bool operator==(const BigNumber& other) const;

private:
    using TValue = unsigned int;
    using TLongValue = long long;
    using TVector = std::vector<TValue>;
    using TSign = int8_t;
    static const long long BASE = 1e9;

    BigNumber(TSign sign, std::vector<TValue> values);

    static TVector SumUnchecked(const TVector& left, const TVector& right);
    static TVector SubUnchecked(const TVector& left, const TVector& right);
    static TSign CompareUnchecked(const TVector& left, const TVector& right);
    static TSign Compare(const BigNumber& left, const BigNumber& right);

    void Trim();

    TSign sign_;
    std::vector<TValue> values_;
};

}  // namespace big_num
