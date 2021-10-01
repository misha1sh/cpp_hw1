#include "operations.h"

#include <cassert>

namespace big_num::operations {

TVector SubUnchecked(const TVector &left, const TVector &right) {
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

}  // namespace operations