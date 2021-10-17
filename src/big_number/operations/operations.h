#pragma once

#include <cstdint>
#include <vector>

#include "../common.h"

namespace big_num::operations {
    using namespace common;
    TVector SumUnchecked(const TVector& left, const TVector& right);
    TVector SubUnchecked(const TVector& left, const TVector& right);
    TVector MulUncheckedNaive(const TVector& left, const TVector& right);
    std::pair<TVector, uint32_t> DivByNumUnchecked(const TVector& left, uint32_t right);
    TVector DivUnchecked(const TVector& value, const TVector& divider);
    TSign CompareUnchecked(const TVector& left, const TVector& right);
    void TrimUnchecked(TVector& values);
}  // namespace operations
