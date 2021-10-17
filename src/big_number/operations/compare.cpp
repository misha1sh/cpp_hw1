#include "operations.h"

namespace big_num::operations {

TSign CompareUnchecked(const TVector &left, const TVector &right) {
    if (left.size() != right.size()) {
        return left.size() < right.size() ? -1 : 1;
    }

    for (long long i = static_cast<long long>(left.size()) - 1; i >= 0; i--) {
        if (left[i] != right[i]) {
            return left[i] < right[i] ? -1 : 1;
        }
    }
    return 0;
}

}  // namespace operations
