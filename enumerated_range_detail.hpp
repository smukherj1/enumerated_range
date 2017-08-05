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
    /**
     * The enumerated forward style iterator implementation
     */
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
        ENUMERATED_ITER(INNER_ITER_T inner_iter, INDEX_T start = 0) : m_iter(inner_iter), m_idx(start) { }
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

    /**
     * Utility class to extract traits for the enumerated range
     */
    template
    <typename T, typename INDEX_T>
    class RANGE_TRAITS
    {
        using inner_iterator = typename boost::range_iterator<T>::type;
        using inner_reference = typename std::iterator_traits<inner_iterator>::reference;
        using inner_value_type = typename std::iterator_traits<inner_iterator>::value_type;
    public:
        // Reference type of the enumerated iterator
        using reference = std::pair<INDEX_T, inner_reference>;
        // Value type of the enumerated iterator
        using value_type = std::pair<INDEX_T, inner_value_type>;
        // The enumerated iterator
        using iterator = ENUMERATED_ITER<inner_iterator, INDEX_T, value_type, reference>;
        // The enumerated range type
        using range_type = boost::iterator_range<iterator>;
    };

    /**
     * Makes the begin iterator for the enumerated range
     */
    template
    <typename T, typename INDEX_T>
    auto make_begin(T&& t, INDEX_T start = 0) -> typename RANGE_TRAITS<T, INDEX_T>::iterator
    {
        using RETURN_T = typename RANGE_TRAITS<T, INDEX_T>::iterator;
        return RETURN_T(std::begin(std::forward<T>(t)), start);
    }

    /**
     * Makes the end iterator for the enumerated range
     */
    template
    <typename T, typename INDEX_T>
    auto make_end(T&& t) -> typename RANGE_TRAITS<T, INDEX_T>::iterator
    {
        return std::end(std::forward<T>(t));
    }
} /* namespace DETAIL */
} /* namespace ENUMERATED_RANGE */