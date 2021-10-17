#include "operations.h"

namespace big_num::operations {

TVector SumUnchecked(const TVector &left, const TVector &right) {
    const size_t length = std::max(left.size(), right.size());

    std::vector <TValue> res;
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

}  // namespace operations
