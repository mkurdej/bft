//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE test_rule_jeffrey_dempster

#ifdef _MSC_VER
#   pragma warning(disable:4505) // unused function
#   pragma warning(disable:4347)

#   pragma warning(push)	// disable for this header only
#   pragma warning(disable:4265)
#   pragma warning(disable:4365)
#   pragma warning(disable:4548)
#   pragma warning(disable:4571)
#   pragma warning(disable:4625)
#   pragma warning(disable:4626)
#   pragma warning(disable:4640)
#   pragma warning(disable:4668)
#elif defined(__GNUC__)
#   pragma GCC diagnostic ignored "-Wunused-function"

#   pragma GCC diagnostic push
#endif // _MSC_VER

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/bft/rule_conjunctive.hpp>
#include <boost/bft/rule_jeffrey_dempster.hpp>

#ifdef _MSC_VER
#   pragma warning(pop)  	// restore original warning level
#elif defined(__GNUC__)
#   pragma GCC diagnostic pop
#endif // _MSC_VER

using namespace boost;
using namespace boost::bft;

BOOST_BFT_DEFINE_CLASS(C1);
BOOST_BFT_DEFINE_CLASS(C2);
BOOST_BFT_DEFINE_CLASS(C3);
BOOST_BFT_DEFINE_CLASS(C4);
BOOST_BFT_DEFINE_CLASS(C5);
BOOST_BFT_DEFINE_CLASS(C6);
BOOST_BFT_DEFINE_CLASS(C7);
BOOST_BFT_DEFINE_CLASS(C8);

typedef fod<C1, C2> fod2;
typedef fod<C1, C2, C3> fod3;

//==============================================================================
BOOST_AUTO_TEST_SUITE(suite_rule_jeffrey_dempster)

BOOST_AUTO_TEST_CASE(test_rule_jeffrey_dempster_has_neutral_element)
{
    rule_jeffrey_dempster rule;

    typedef fod2 fod_t;

    const mass<fod_t>::container_type ma1 = {0, 0.3, 0, 0.7};
    const mass<fod_t> m1(ma1);
    const mass<fod_t> m_neutral_element(vacuous);
    const mass<fod_t> & m_expected = m1;

    mass<fod_t> m_actual12 = m1.apply(rule, m_neutral_element);
    mass<fod_t> m_actual21 = m_neutral_element.apply(rule, m1);

    for(std::size_t i = 0; i < fod_t::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_expected[i], m_actual12[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual21[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_rule_jeffrey_dempster_is_equivalent_to_conjunctive_when_no_conflict)
{
    rule_jeffrey_dempster rule;

    typedef fod2 fod_t;

    const mass<fod_t>::container_type ma1 = {0, 0.6, 0, 0.4};
    const mass<fod_t> m1(ma1);
    const mass<fod_t>::container_type ma2 = {0, 0.8, 0, 0.2};
    const mass<fod_t> m2(ma2);

    const mass<fod_t>::container_type mae = {0, 0.92, 0, 0.08};
    const mass<fod_t> m_expected(mae);
    mass<fod_t> m_actual_conj = m1.apply(rule_conjunctive(), m2);
    mass<fod_t> m_actual_dp = m1.apply(rule, m2);

    for(std::size_t i = 0; i < fod_t::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_actual_conj[i], m_actual_dp[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual_conj[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual_dp[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_rule_jeffrey_dempster_Ma2011_example_6)
{
    rule_jeffrey_dempster rule;

    typedef fod3 fod_t;

    const mass<fod_t>::container_type ma1 = {0, 0.3, 0, 0.7, 0, 0, 0, 0};
    const mass<fod_t> m1(ma1);
    const mass<fod_t>::container_type ma2 = {0, 0.3, 0, 0.5, 0.2, 0, 0, 0};
    const mass<fod_t> m2(ma2);

    const mass<fod_t>::container_type mae = {0, 0.45, 0, 0.35, 0.2, 0, 0, 0};
    const mass<fod_t> m_expected(mae);
    mass<fod_t> m_actual = m1.apply(rule, m2);

    for(std::size_t i = 0; i < fod_t::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_rule_jeffrey_dempster_Ma2011_example_7)
{
    rule_jeffrey_dempster rule;

    typedef fod<C1,C2,C3,C4,C5,C6,C7,C8> fod_t;

    mass<fod_t> m1;
    {
        m1.at<C1, C8>() = 0.2;
        m1.at<C1, C2>() = 0.4;
        m1.at<C3>() = 0.3;
        m1.at<C6, C7>() = 0.1;
    }

    mass<fod_t> m2;
    {
        m2.at<C1, C2>() = 0.5;
        m2.at<C4, C5>() = 0.3;
        m2.at<C6>() = 0.2;
    }

    mass<fod_t> m_expected;
    {
        m_expected.at<C1>() = 1 / 6.0;
        m_expected.at<C1, C2>() = 1 / 3.0;
        m_expected.at<C4, C5>() = 0.3;
        m_expected.at<C6>() = 0.2;
    }

    mass<fod_t> m_actual = m1.apply(rule, m2);

    for(std::size_t i = 0; i < fod_t::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_rule_jeffrey_dempster_Ma2011_example_10)
{
    rule_jeffrey_dempster rule;

    typedef fod<C1,C2,C3,C4> fod_t;

    mass<fod_t> m1;
    {
        m1.at<C1>() = 0.3;
        m1.at<C1, C2>() = 0.3;
        m1.at<C3>() = 0.1;
        m1.at<C4>() = 0.3;
    }

    mass<fod_t> m2;
    {
        m2.at<C1, C3>() = 0.6;
        m2.at<C2, C4>() = 0.4;
    }

    mass<fod_t> m3;
    {
        m3.at<C1, C3>() = 0.2;
        m3.at<C2>() = 0.3;
        m3.at<C4>() = 0.5;
    }

    mass<fod_t> m_expected;
    {
        m_expected.at<C1>() = 6.0 / 35.0;
        m_expected.at<C2>() = 0.3;
        m_expected.at<C3>() = 1.0 / 35.0;
        m_expected.at<C4>() = 0.5;
    }

    mass<fod_t> m_actual_123 = m1.apply(rule, m2).apply(rule, m3);
    mass<fod_t> m_actual_13 = m1.apply(rule, m3);

    for(std::size_t i = 0; i < fod_t::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_expected[i], m_actual_123[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual_13[i], 1e-10);
        BOOST_CHECK_CLOSE(m_actual_123[i], m_actual_13[i], 1e-10);
    }
}

BOOST_AUTO_TEST_SUITE_END()
