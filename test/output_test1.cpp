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
#pragma warning(disable : 4548)
#pragma warning(disable : 4571)
#pragma warning(disable : 4625)
#pragma warning(disable : 4626)
#pragma warning(disable : 4640)
#pragma warning(disable : 4668)
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-function"

#pragma GCC diagnostic push
#endif // _MSC_VER

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/bft/bft_function.hpp>
#include <boost/bft/io.hpp>
#include <boost/bft/mass.hpp>
#include <sstream>

#ifdef _MSC_VER
#pragma warning(pop) // restore original warning level
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif // _MSC_VER

using namespace boost;
using namespace boost::bft;

BOOST_BFT_DEFINE_CLASS(C1);
BOOST_BFT_DEFINE_CLASS(C2);
BOOST_BFT_DEFINE_CLASS(C3);
BOOST_BFT_DEFINE_CLASS(C4);

typedef fod<C1, C2> fod2;
typedef fod<C1, C2, C3, C4> fod4;

//==============================================================================
BOOST_AUTO_TEST_SUITE(suite_mass)

#ifndef BOOST_NO_CWCHAR

#define BOOST_BFT_TEST_OUTPUT(v, expected)                                     \
    \
{                                                                       \
        std::ostringstream os;                                                 \
        os FORMATTERS << v;                                                    \
        BOOST_CHECK_EQUAL(os.str(), expected);                                 \
    \
}                                                                       \
    \
{                                                                       \
        std::wostringstream os;                                                \
        os FORMATTERS << v;                                                    \
        BOOST_CHECK(os.str() == BOOST_PP_CAT(L, expected));                    \
    \
} \                                                                           \
/**/

#else

#define BOOST_BFT_TEST_OUTPUT(v, expected)                                     \
    \
{                                                                       \
        std::ostringstream os;                                                 \
        os FORMATTERS << v;                                                    \
        BOOST_CHECK_EQUAL(os.str(), expected);                                 \
    \
} \                                                                           \
/**/

#endif

BOOST_AUTO_TEST_CASE(test_bft_function_output_stream_operator)
{ // no format specified
#define FORMATTERS
    BOOST_BFT_TEST_OUTPUT(bft_function<fod2>(), "[0, 0, 0, 0]");
    BOOST_BFT_TEST_OUTPUT(mass<fod2>(), "[0, 0, 0, 0]");
    BOOST_BFT_TEST_OUTPUT(mass<fod2>(vacuous), "[0, 0, 0, 1]");
    BOOST_BFT_TEST_OUTPUT(mass<fod2>(degenerate), "[1, 0, 0, 0]");
}

BOOST_AUTO_TEST_SUITE_END()
