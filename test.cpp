#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include <array>

#include "enumerated_range.hpp"

#define BOOST_TEST_MODULE enumerated_range_tests
#include <boost/test/unit_test.hpp>

namespace
{

    std::vector<int> ivec = {0, 1, 2, 3, 4};
    std::array<int, 5> iarr = {0, 1, 2, 3, 4};
    int icarr[] = {0, 1, 2, 3, 4};

} /* namespace anynymous */

BOOST_AUTO_TEST_CASE(check_empty_sequence)
{
    int iters = 0;
    for(auto item : std::vector<int>())
    {
        (void)item;
        ++iters;
    }
    BOOST_TEST(iters == 0);
}

BOOST_AUTO_TEST_CASE(check_iteration_value)
{
    for(auto item : ENUMERATED_RANGE::make_range(ivec))
    {
        // The index is equal to the value so we can just
        // check for that
        BOOST_TEST(static_cast<int>(item.first) == item.second);
    }
    for(auto item : ENUMERATED_RANGE::make_range(iarr))
    {
        // The index is equal to the value so we can just
        // check for that
        BOOST_TEST(static_cast<int>(item.first) == item.second);
    }
    for(auto item : ENUMERATED_RANGE::make_range(icarr))
    {
        // The index is equal to the value so we can just
        // check for that
        BOOST_TEST(static_cast<int>(item.first) == item.second);
    }
}