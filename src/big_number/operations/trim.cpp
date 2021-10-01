#include "operations.h"

namespace big_num::operations {

void TrimUnchecked(TVector &values) {
    while (!values.empty() && values.back() == 0) {
        values.pop_back();
    }
}

}  // namespace operations