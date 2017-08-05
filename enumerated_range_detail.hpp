#pragma once

#include <utility>
#include <tuple>
#include <iterator>
#include <type_traits>

#include <boost/range.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/iterator/iterator_facade.hpp>

namespace ENUMERATED_RANGE
{
namespace DETAIL
{

    template
    <typename INNER_ITER_T, typename INDEX_T, typename VALUE_T, typename REF_T>
    class ENUMERATED_ITER : public boost::iterator_facade<
            ENUMERATED_ITER<INNER_ITER_T, INDEX_T, VALUE_T, REF_T>,
            VALUE_T,
            boost::forward_traversal_tag,
            REF_T
        >
    {
    public:
        ENUMERATED_ITER(INNER_ITER_T inner_iter) : m_iter(inner_iter), m_idx(0) { }
    private:
        private:
        friend class boost::iterator_core_access;

        using MY_TYPE = ENUMERATED_ITER<INNER_ITER_T, INDEX_T, VALUE_T, REF_T>;

        REF_T dereference() const
        {
            return REF_T(m_idx, *m_iter);
        }

        bool equal(const MY_TYPE& other) const
        {
            return m_iter == other.m_iter;
        }

        void increment()
        {
            ++m_iter;
            ++m_idx;
        }

        INNER_ITER_T m_iter;
        INDEX_T m_idx;
    };

    template
    <typename T, typename INDEX_T>
    class RANGE_TRAITS
    {
        using inner_iterator = typename boost::range_iterator<T>::type;
        using inner_reference = typename std::iterator_traits<inner_iterator>::reference;
        using inner_value_type = typename std::iterator_traits<inner_iterator>::value_type;
    public:
        using reference = std::pair<INDEX_T, inner_reference>;
        using value_type = std::pair<INDEX_T, inner_value_type>;
        using iterator = ENUMERATED_ITER<inner_iterator, INDEX_T, value_type, reference>;
        using range_type = boost::iterator_range<iterator>;
    };

    template
    <typename T, typename INDEX_T>
    auto make_begin(T&& t) -> typename RANGE_TRAITS<T, INDEX_T>::iterator
    {
        return std::begin(t);
    }

    template
    <typename T, typename INDEX_T>
    auto make_end(T&& t) -> typename RANGE_TRAITS<T, INDEX_T>::iterator
    {
        return std::end(t);
    }
} /* namespace DETAIL */
} /* namespace ENUMERATED_RANGE */