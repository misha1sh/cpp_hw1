#include "big_number.h"
#include <algorithm>

#include <cassert>
#include <cstdlib>
#include <iomanip>
#include <sstream>

namespace big_num {

BigNumber::BigNumber(const std::string &number) {
    long long begin_pos = 0;
    if (number[0] == '-') {
        sign_ = -1;
        begin_pos = 1;
    } else {
        sign_ = 1;
    }

    for (long long i = number.size(); i > begin_pos; i -= 9) {
        if (i - begin_pos < 9) {
            values_.push_back(std::stoi(number.substr(begin_pos, i - begin_pos)));
        } else {
            values_.push_back(std::stoi(number.substr(i - 9, 9)));
        }
    }

    Trim();
}

BigNumber BigNumber::operator+(const BigNumber &other) const {
    if (sign_ == other.sign_) {
        return {sign_, SumUnchecked(values_, other.values_)};
    }

    if (sign_ < 0 && other.sign_ > 0) {
        auto comp = CompareUnchecked(values_, other.values_);
        if (comp <= 0) {
            // abs(*this) <= abs(other)
            return {1, SubUnchecked(other.values_, values_)};
        } else {
            // abs(*this) > abs(other)
            return {-1, SubUnchecked(values_, other.values_)};
        }
    }

    // sign_ > 0 && other.sign_ < 0
    return other + *this;
}

BigNumber::BigNumber(TSign sign, std::vector<TValue> values)
        : sign_(sign), values_(std::move(values)) {
    Trim();
}


BigNumber::TVector BigNumber::SumUnchecked(const BigNumber::TVector &left, const BigNumber::TVector &right) {
    const size_t length = std::max(left.size(), right.size());

    std::vector<TValue> res;
    res.reserve(length);

    TLongValue carry = 0;
    for (size_t i = 0; i < length || carry; i++) {
        TLongValue sum = carry;
        if (i < left.size()) {
            sum += left[i];
        }
        if (i < right.size()) {
            sum += right[i];
        }

        carry = sum / BASE;
        res.push_back(sum % BASE);
    }

    return res;
}

BigNumber::TVector BigNumber::SubUnchecked(const BigNumber::TVector &left, const BigNumber::TVector &right) {
    const size_t length = std::max(left.size(), right.size());

    TVector res;
    res.reserve(length);

    TLongValue carry = 0;
    for (size_t i = 0; i < length; i++) {
        TLongValue sum = carry;
        if (i < left.size()) {
            sum += left[i];
        }
        if (i < right.size()) {
            sum -= right[i];
        }

        if (sum < 0) {
            sum += BASE;
            carry = -1;
        } else {
            carry = 0;
        }

        res.push_back(sum % BASE);
    }

    assert(carry == 0);

    return res;
}

int8_t BigNumber::CompareUnchecked(const BigNumber::TVector &left, const BigNumber::TVector &right) {
    if (left.size() != right.size()) {
        return left.size() < right.size() ? -1 : 1;
    }

    for (long long i = left.size() - 1; i >= 0; i--) {
        if (left[i] != right[i]) {
            return left[i] < right[i] ? -1 : 1;
        }
    }
    return 0;
}

int8_t BigNumber::Compare(const BigNumber &left, const BigNumber &right) {
    if (left.sign_ > 0 && right.sign_ > 0) {
        return CompareUnchecked(left.values_, right.values_);
    }
    if (left.sign_ < 0 && right.sign_ > 0) {
        return -1;
    }
    if (left.sign_ > 0 && right.sign_ < 0) {
        return 1;
    }
    // left.sign_ <= 0 && right.sign_ <= 0
    return -CompareUnchecked(left.values_, right.values_);
}


BigNumber BigNumber::operator-(const BigNumber &other) const {
    return (*this) + (-other);
}

BigNumber BigNumber::operator+() const {
    return *this;
}

BigNumber BigNumber::operator-() const {
    return {(int8_t) -sign_, values_};
}

bool BigNumber::operator<(const BigNumber &other) const {
    return Compare(*this, other) == -1;
}

bool BigNumber::operator>(const BigNumber &other) const {
    return Compare(*this, other) == 1;
}

bool BigNumber::operator<=(const BigNumber &other) const {
    return Compare(*this, other) <= 0;
}

bool BigNumber::operator>=(const BigNumber &other) const {
    return Compare(*this, other) >= 0;
}

bool BigNumber::operator==(const BigNumber &other) const {
    return Compare(*this, other) == 0;
}

std::string BigNumber::ToString() const {
    if (values_.empty()) {
        return "0";
    }

    std::stringstream out;
    out << values_.back();
    for (long long i = values_.size() - 2; i >= 0; i--) {
        out << std::setfill('0') << std::setw(9) << values_[i];
    }

    std::string res(out.str());
    if (sign_ < 0) {
        res = '-' + res;
    }

    return res;
}

void BigNumber::Trim() {
    while (!values_.empty() && values_.back() == 0) {
        values_.pop_back();
    }

    // sign of zero is 1
    if (values_.empty()) {
        sign_ = 1;
    }
}

}  // namespace big_num

