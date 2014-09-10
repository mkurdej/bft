//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE test_mass

#ifdef _MSC_VER
#pragma warning(push) // disable for this header only
#pragma warning(disable : 4265)
#pragma warning(disable : 4365)
#pragma warning(disable : 4389)
#pragma warning(disable : 4548)
#pragma warning(disable : 4571)
#pragma warning(disable : 4625)
#pragma warning(disable : 4626)
#pragma warning(disable : 4640)
#pragma warning(disable : 4668)
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#endif // _MSC_VER

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/bft/bft_function.hpp>
#include <boost/bft/fod.hpp>
#include <boost/utility/binary.hpp>

#ifdef _MSC_VER
#pragma warning(pop) // restore original warning level
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif // _MSC_VER

using namespace boost;
using namespace boost::bft;

typedef fod<int> fod_t;

//==============================================================================
BOOST_AUTO_TEST_SUITE(suite_set_operations)

BOOST_AUTO_TEST_CASE(test_set_union)
{
    BOOST_CHECK_EQUAL(set_union(BOOST_BINARY(0000), BOOST_BINARY(0001)),
                      BOOST_BINARY(0001));
    BOOST_CHECK_EQUAL(set_union(BOOST_BINARY(1001), BOOST_BINARY(1101)),
                      BOOST_BINARY(1101));
}

BOOST_AUTO_TEST_CASE(test_set_minus)
{
    BOOST_CHECK_EQUAL(set_minus(BOOST_BINARY(0101), BOOST_BINARY(0001)),
                      BOOST_BINARY(0100));
    BOOST_CHECK_EQUAL(set_minus(BOOST_BINARY(0000), BOOST_BINARY(0001)),
                      BOOST_BINARY(0000));
    BOOST_CHECK_EQUAL(set_minus(BOOST_BINARY(1011), BOOST_BINARY(0001)),
                      BOOST_BINARY(1010));
    BOOST_CHECK_EQUAL(
        set_minus(BOOST_BINARY(1111 1101), BOOST_BINARY(1111 0000)),
        BOOST_BINARY(0000 1101));
}

BOOST_AUTO_TEST_CASE(test_set_xor)
{
    BOOST_CHECK_EQUAL(set_xor(BOOST_BINARY(0101), BOOST_BINARY(0001)),
                      BOOST_BINARY(0100));
    BOOST_CHECK_EQUAL(set_xor(BOOST_BINARY(0000), BOOST_BINARY(0001)),
                      BOOST_BINARY(0001));
    BOOST_CHECK_EQUAL(set_xor(BOOST_BINARY(1011), BOOST_BINARY(0001)),
                      BOOST_BINARY(1010));
    BOOST_CHECK_EQUAL(set_xor(BOOST_BINARY(1111 1101), BOOST_BINARY(1111 0000)),
                      BOOST_BINARY(0000 1101));
}

BOOST_AUTO_TEST_CASE(test_count_elements)
{
    BOOST_CHECK_EQUAL(1U, count_elements(BOOST_BINARY(0100)));
    BOOST_CHECK_EQUAL(5U, count_elements(BOOST_BINARY(0110 1101)));
}

BOOST_AUTO_TEST_CASE(test_is_emptyset)
{
    BOOST_CHECK(is_emptyset(BOOST_BINARY(0000)));

    BOOST_CHECK(!is_emptyset(BOOST_BINARY(0001)));
    BOOST_CHECK(!is_emptyset(BOOST_BINARY(0010)));
    BOOST_CHECK(!is_emptyset(BOOST_BINARY(0100)));
    BOOST_CHECK(!is_emptyset(BOOST_BINARY(1101)));
}

BOOST_AUTO_TEST_CASE(test_is_superset_of)
{
    BOOST_CHECK(is_superset_of(BOOST_BINARY(0000), BOOST_BINARY(0000)));
    BOOST_CHECK(is_superset_of(BOOST_BINARY(0001), BOOST_BINARY(0000)));
    BOOST_CHECK(is_superset_of(BOOST_BINARY(1101), BOOST_BINARY(0000)));

    BOOST_CHECK(is_superset_of(BOOST_BINARY(0001), BOOST_BINARY(0001)));
    BOOST_CHECK(is_superset_of(BOOST_BINARY(1101), BOOST_BINARY(0001)));
    BOOST_CHECK(!is_superset_of(BOOST_BINARY(1100), BOOST_BINARY(0001)));
}

BOOST_AUTO_TEST_SUITE_END()
