#include "operations.h"

#include <cassert>

namespace big_num::operations {

std::pair<TVector, uint32_t> DivByNumUnchecked(const TVector &left, const uint32_t right) {
    assert(right < BASE);
    TVector res(left.size());

    TLongValue carry = 0;
    for (long long i = static_cast<long long>(left.size()) - 1; i != -1; i--) {
        TLongValue cur = left[i] + carry * BASE;
        res[i] = cur / right;
        carry = cur % right;
    }

    return {res, carry};
}

TVector DivUnchecked(const TVector &value, const TVector& divider) {
    TVector l = {0};
    TVector r = SumUnchecked(value, {1});
    // l + 1 < r
    while (CompareUnchecked(SumUnchecked(l, {1}), r) < 0) {
        // m = (l + r) / 2
        TVector m = DivByNumUnchecked(SumUnchecked(l, r), 2).first;
        TVector multM = MulUncheckedNaive(m, divider);
        TSign comp = CompareUnchecked(value, multM);

        if (comp < 0) {  //  value < divider * m
            r = m;
        } else {  // value >= divider * m
            l = m;
        }
    }
    return l;
}

}  // namespace operations
