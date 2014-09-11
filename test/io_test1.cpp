// Copyright (c) 2011-2014
// Marek Kurdej
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#ifdef _MSC_VER
#pragma warning(disable : 4505) // unused function

#pragma warning(push) // disable for this header only
#pragma warning(disable : 4265)
#pragma warning(disable : 4365)
//#pragma warning(disable : 4347)
#pragma warning(disable : 4350)
#pragma warning(disable : 4548)
#pragma warning(disable : 4571)
#pragma warning(disable : 4625)
#pragma warning(disable : 4626)
#pragma warning(disable : 4640)
#pragma warning(disable : 4668)
#pragma warning(disable : 4996)
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-function"

#pragma GCC diagnostic push
#endif // _MSC_VER

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#ifdef _MSC_VER
#pragma warning(pop) // restore original warning level
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif // _MSC_VER

//==============================================================================
#include <boost/bft/io.hpp>
#include <boost/bft/mass.hpp>

#include <sstream>

using namespace boost::bft;

//==============================================================================
BOOST_BFT_DEFINE_CLASS(C1);
BOOST_BFT_DEFINE_CLASS(C2);
BOOST_BFT_DEFINE_CLASS(C3);

typedef fod<C1, C2> fod2;
typedef fod<C1, C2, C3> fod3;

typedef fod2 fodFO;
typedef fod3 fodABC;

//==============================================================================
BOOST_AUTO_TEST_SUITE(suite_name)

#ifndef BOOST_NO_CWCHAR

#define BOOST_BFT_TEST_IO(v, expected)                      \
{                                                           \
    std::ostringstream ss;                                  \
    ss << v;                                                \
    BOOST_CHECK_EQUAL(ss.str(), expected);                  \
}                                                           \
{                                                           \
    std::wostringstream ss;                                 \
    ss << v;                                                \
    BOOST_CHECK(ss.str() == BOOST_PP_CAT(L, expected));     \
}                                                           \
/**/

#else // BOOST_NO_CWCHAR

#define BOOST_BFT_TEST_IO(v, expected)                      \
{                                                           \
    std::ostringstream ss;                                  \
    ss << v;                                                \
    BOOST_CHECK_EQUAL(ss.str(), expected);                  \
}                                                           \
/**/

#endif // BOOST_NO_CWCHAR

BOOST_AUTO_TEST_CASE(test_io)
{
    const mass<fodFO>::container_type ma1 = {0, 0.3, 0.7, 0};
    const mass<fodFO> m1(ma1);
    BOOST_BFT_TEST_IO(m1, "[0, 0.3, 0.7, 0]");
    const mass<fodABC>::container_type ma2 = {0, 0.3, 0.3, 0, 0.2, 0.1, 0, 0.1};
    const mass<fodABC> m2(ma2);
    BOOST_BFT_TEST_IO(m2, "[0, 0.3, 0.3, 0, 0.2, 0.1, 0, 0.1]");
}

#undef BOOST_BFT_TEST_IO

BOOST_AUTO_TEST_SUITE_END()
