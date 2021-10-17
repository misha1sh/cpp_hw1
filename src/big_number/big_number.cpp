#include "big_number.h"

#include <algorithm>
#include <charconv>
#include <iomanip>
#include <stdexcept>

#include "operations/operations.h"

#include "iostream"
namespace big_num {

using namespace common;

BigNumber::BigNumber() : BigNumber(0) {
}

unsigned int StringViewToInt(const std::string_view& str_view) {
    unsigned int res;
    auto error = std::from_chars(str_view.begin(), str_view.end(), res);
    if (error.ec == std::errc::invalid_argument || error.ptr != str_view.end()) {
        throw std::invalid_argument{"invalid_argument"};
    }
    else if (error.ec == std::errc::result_out_of_range) {
        throw std::out_of_range{"out_of_range"};
    }

    return res;
}

BigNumber::BigNumber(const std::string_view &number) {
    long long begin_pos = 0;
    if (number[0] == '-') {
        sign_ = -1;
        begin_pos = 1;
    } else {
        sign_ = 1;
    }

    for (long long i = number.size(); i > begin_pos; i -= 9) {
        if (i - begin_pos < 9) {
            values_.push_back(StringViewToInt(number.substr(begin_pos, i - begin_pos)));
        } else {
            values_.push_back(StringViewToInt(number.substr(i - 9, 9)));
        }
    }

    if (values_.empty()) {
        throw std::invalid_argument("No values given");
    }

    Trim();
}

BigNumber BigNumber::operator+(const BigNumber &other) const {
    if (sign_ == other.sign_) {
        return {sign_, operations::SumUnchecked(values_, other.values_)};
    }

    if (sign_ < 0 && other.sign_ > 0) {
        auto comp = operations::CompareUnchecked(values_, other.values_);
        if (comp <= 0) {
            // abs(*this) <= abs(other)
            return {1, operations::SubUnchecked(other.values_, values_)};
        } else {
            // abs(*this) > abs(other)
            return {-1, operations::SubUnchecked(values_, other.values_)};
        }
    }

    // sign_ > 0 && other.sign_ < 0
    return other + *this;
}

BigNumber::BigNumber(TSign sign, TVector values)
        : sign_(sign), values_(std::move(values)) {
    Trim();
}


int8_t BigNumber::Compare(const BigNumber &left, const BigNumber &right) {
    if (left.sign_ > 0 && right.sign_ > 0) {
        return operations::CompareUnchecked(left.values_, right.values_);
    }
    if (left.sign_ < 0 && right.sign_ > 0) {
        return -1;
    }
    if (left.sign_ > 0 && right.sign_ < 0) {
        return 1;
    }
    // left.sign_ <= 0 && right.sign_ <= 0
    return static_cast<TSign>(-operations::CompareUnchecked(left.values_, right.values_));
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
    std::stringstream out;
    out << *this;
    return out.str();
}


void BigNumber::Trim() {
    operations::TrimUnchecked(values_);

    // sign of zero is 1
    if (values_.empty()) {
        sign_ = 1;
    }
}


BigNumber BigNumber::operator*(const BigNumber& other) const {
    return {
        static_cast<TSign>(sign_ * other.sign_),
        operations::MulUncheckedNaive(values_, other.values_)
    };
}


BigNumber BigNumber::operator/(const BigNumber &other) const {
    if (other == BigNumber(0)) {
        throw std::overflow_error("Divide by zero error");
    }
    return {
        static_cast<TSign>(sign_ * other.sign_),
        operations::DivUnchecked(values_, other.values_)
    };
}

BigNumber BigNumber::operator%(const BigNumber &other) const {
    BigNumber div = *this / other;
    return *this - div * other;
}

std::istream &operator>>(std::istream &in, BigNumber &bigNumber) {
    std::string num;
    in >> num;
    bigNumber = BigNumber(num);
    return in;
}

std::ostream &operator<<(std::ostream &out, const BigNumber &bigNumber) {
    if (bigNumber.values_.empty()) {
        out << "0";
    } else {
        if (bigNumber.sign_ < 0) {
            out << "-";
        }
        out << bigNumber.values_.back();
        for (long long i = static_cast<long long>(bigNumber.values_.size()) - 2; i >= 0; i--) {
            out << std::setfill('0') << std::setw(9) << bigNumber.values_[i];
        }
    }

    return out;
}

}  // namespace big_num

