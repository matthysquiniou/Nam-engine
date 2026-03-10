#pragma once
#include <BaseTypes.h>

namespace nam
{
    template<typename DenseType>
    struct SparseSetPage {
        static constexpr u32 PAGE_SIZE = 4096;

        DenseType m_data[PAGE_SIZE] = {};
        u32 m_entities[PAGE_SIZE] = {};
        u32 m_count = 0;
    };
}
