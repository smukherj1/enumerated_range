#pragma once

#include <enumerated_range_detail.hpp>

namespace ENUMERATED_RANGE
{


/**
 * Header only library that implements a C++ equivalent of python's
 * in-built "enumerate" utility. See https://docs.python.org/2/library/functions.html#enumerate
 *
 * Basically given a forward iterable sequence, this library returns a forward
 * iterable range over a pair of the following types:-
 * first_type:- The iteration index (The starting value and type of this can be configured)
 * second_type:- This is the reference type of the sequence being enumerated
 *
 * So calling ENUMERATED_RANGE::make_range on
 * std::vector<int>
 * will return a range where each element of is type
 * std::pair<std::size_t, int&>
 *
 * make_range can be templated to change the index type. The index type
 * is default initialized with 0 so compilation will fail unless the new index
 * type is integer assignable.
 * So to iterate over a vector of ints where the index is also of type int
 * and starts from 1 one may do the following:-
 * using SEQUENCE = std::vector<int>;
 * SEQUENCE seq = {0, 1, 2, 3, 4};
 * for(auto t : ENUMERATED_RANGE::make_range<SEQUENCE, int>(seq, 1))
 *
 *
 * Note that the individual elements are reference types. Hence, the objects
 * may be mutated. If the enumrated range is passed in a const sequence, the
 * objects will be const references as well. However, the pair itself is
 * a tempoary. Hence you can't bind a lvalue reference to it. ie the following
 * will not be possible:-
 * for(auto& t : ENUMERATED_RANGE::make_range(...))
 * But the following are possible:-
 * for(const auto& t : ENUMERATED_RANGE::make_range(...))
 * for(auto t : ENUMERATED_RANGE::make_range(...))
 *
 * WARNING: Even though element mutation is allowed, care must be taken to
 * not do any operation on the containers that might invalidate their
 * iterators. The behavior of the enumerated range is undefined in this case.
 */

template
<typename T, typename INDEX_T = std::size_t>
using TRAITS = DETAIL::RANGE_TRAITS<T, INDEX_T>;

template
<typename T, typename INDEX_T = std::size_t>
using RANGE_T = typename TRAITS<T, INDEX_T>::range_type;

template
<typename T, typename INDEX_T = std::size_t>
auto make_range(T&& input_sequence, INDEX_T start = 0) -> RANGE_T<T, INDEX_T>
{
    return boost::make_iterator_range(
        DETAIL::make_begin<T, INDEX_T>(input_sequence, start),
        DETAIL::make_end<T, INDEX_T>(input_sequence)
    );
}

} /* namespace ENUMERATED_RANGE */