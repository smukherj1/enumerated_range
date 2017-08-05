#pragma once

#include <enumerated_range_detail.hpp>

namespace ENUMERATED_RANGE
{

template
<typename T, typename INDEX_T = std::size_t>
auto make_range(T&& input_sequence) -> typename DETAIL::RANGE_TRAITS<T, INDEX_T>::range_type
{
    return boost::make_iterator_range(
        DETAIL::make_begin<T, INDEX_T>(input_sequence),
        DETAIL::make_end<T, INDEX_T>(input_sequence)
    );
}

} /* namespace ENUMERATED_RANGE */