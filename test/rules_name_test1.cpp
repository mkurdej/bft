//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE test_rules

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
#include <boost/bft/mass.hpp>
#include <boost/math/special_functions/fpclassify.hpp>

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
typedef fod<C1, C2, C3> fod3;

typedef fod2 fodFO;
typedef fod3 fodABC;

//==============================================================================
//#include <boost/bft/conjunctive_decomposition.hpp>
//#include <boost/bft/disjunctive_decomposition.hpp>
#include <boost/bft/rule_conjunctive.hpp>
#include <boost/bft/rule_conjunctive_cautious.hpp>
#include <boost/bft/rule_dempster.hpp>
#include <boost/bft/rule_disjunctive.hpp>
#include <boost/bft/rule_disjunctive_bold.hpp>
#include <boost/bft/rule_dubois_prade.hpp>
#include <boost/bft/rule_normalization.hpp>
#include <boost/bft/rule_normalization_inagaki.hpp>
#include <boost/bft/rule_pcr5.hpp>
#include <boost/bft/rule_yager.hpp>

//==============================================================================
BOOST_AUTO_TEST_SUITE(suite_name)

#define BOOST_BFT_CHECK_OBJ_NAME(rule_obj, name) \
    BOOST_CHECK_EQUAL(rule_obj.to_string(), name)

#define BOOST_BFT_CHECK_NAME(rule, name) \
    BOOST_CHECK_EQUAL(rule().to_string(), name)

BOOST_AUTO_TEST_CASE(test_name)
{
    //conjunctive_decomposition decomposition;
    //disjunctive_decomposition decomposition;
    BOOST_BFT_CHECK_NAME(rule_conjunctive, "conjunctive rule");
    BOOST_BFT_CHECK_NAME(rule_conjunctive_cautious, "cautious conjunctive rule");
    BOOST_BFT_CHECK_NAME(rule_dempster, "Dempster rule");
    BOOST_BFT_CHECK_NAME(rule_disjunctive, "disjunctive rule");
    BOOST_BFT_CHECK_NAME(rule_disjunctive_bold, "bold disjunctive rule");
    BOOST_BFT_CHECK_NAME(rule_dubois_prade, "Dubois-Prade adaptative rule");
    BOOST_BFT_CHECK_NAME(rule_normalization, "normalization rule");
    BOOST_BFT_CHECK_OBJ_NAME(rule_normalization_inagaki(0), "Inagaki normalization rule");
    BOOST_BFT_CHECK_NAME(rule_pcr5, "Proportional Conflict Redistribution Rule no. 5");
    BOOST_BFT_CHECK_NAME(rule_yager, "Yager rule");
}

BOOST_AUTO_TEST_SUITE_END()
