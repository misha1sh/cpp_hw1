#include "operations.h"

#include <cassert>

namespace big_num::operations {

TVector MulUncheckedNaive(const TVector &left, const TVector &right) {

    TVector res(left.size() + right.size());
    TLongValue carry = 0;
    for (size_t i = 0; i < left.size(); i++) {
        for (size_t j = 0; j < right.size() || carry; j++) {
            TLongValue mult = res[i + j];
            if (j < right.size()) {
                mult += static_cast<TLongValue>(left[i]) * right[j];
            }
            mult += carry;

            res[i + j] = mult % BASE;
            carry = mult / BASE;
        }
    }

    assert(carry == 0);

    TrimUnchecked(res);

    return res;
}

}  // namespace operations