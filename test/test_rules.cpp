//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE test_mass

#ifdef _MSC_VER
#   pragma warning(disable:4505) // unused function

#   pragma warning(push)	// disable for this header only
#   pragma warning(disable:4265)
#   pragma warning(disable:4365)
#   pragma warning(disable:4347)
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

#include <boost/test/unit_test.hpp>
#include <boost/belief/mass.hpp>
#include <boost/math/special_functions/fpclassify.hpp>

#ifdef _MSC_VER
#   pragma warning(pop)  	// restore original warning level
#elif defined(__GNUC__)
#   pragma GCC diagnostic pop
#endif // _MSC_VER

using namespace boost;
using namespace boost::belief;

BOOST_BELIEF_DEFINE_CLASS(C1);
BOOST_BELIEF_DEFINE_CLASS(C2);
BOOST_BELIEF_DEFINE_CLASS(C3);
BOOST_BELIEF_DEFINE_CLASS(C4);

typedef fod<C1, C2> fod2;
typedef fod<C1, C2, C3> fod3;

typedef fod2 fodFO;
typedef fod3 fodABC;

//==============================================================================
#include <boost/belief/rule_conjunctive.hpp>

BOOST_AUTO_TEST_SUITE(suite_rule_conjunctive)

BOOST_AUTO_TEST_CASE(test_rule_conjunctive_has_neutral_element)
{
    rule_conjunctive rule;

    const mass<fodFO>::container_type ma1 = {0, 0.3, 0, 0.7};
    const mass<fodFO> m1(ma1);
    const mass<fodFO> m_neutral_element(vacuous);
    const mass<fodFO> & m_expected = m1;

    mass<fodFO> m_actual = m1.apply(rule, m_neutral_element);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_rule_conjunctive_is_commutative)
{
    rule_conjunctive rule;

    const mass<fodFO>::container_type ma1 = {0, 0.3, 0.7, 0};
    const mass<fodFO> m1(ma1);
    const mass<fodFO>::container_type ma2 = {0, 0.5, 0.4, 0.1};
    const mass<fodFO> m2(ma2);

    const mass<fodFO>::container_type mae = {0.47, 0.18, 0.35, 0.0};
    const mass<fodFO> m_expected(mae);
    mass<fodFO> m_actual12 = m1.apply(rule, m2);
    mass<fodFO> m_actual21 = m2.apply(rule, m1);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_actual12[i], m_actual21[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual12[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual21[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_rule_conjunctive_is_associative)
{
    rule_conjunctive rule;

    const mass<fodFO>::container_type ma1 = {0, 0.3, 0.7, 0};
    const mass<fodFO> m1(ma1);
    const mass<fodFO>::container_type ma2 = {0, 0.5, 0.4, 0.1};
    const mass<fodFO> m2(ma2);
    const mass<fodFO>::container_type ma3 = {0.1, 0.2, 0.7, 0};
    const mass<fodFO> m3(ma3);

    const mass<fodFO>::container_type mae = {0.719, 0.036, 0.245, 0.0};
    const mass<fodFO> m_expected(mae);
    mass<fodFO> m_actual12_3 = m1.apply(rule, m2).apply(rule, m3);
    mass<fodFO> m_actual1_23 = m1.apply(rule, m2.apply(rule, m3));

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_actual12_3[i], m_actual1_23[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual12_3[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual1_23[i], 1e-10);
    }
}

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
#include <boost/belief/rule_dempster.hpp>

BOOST_AUTO_TEST_SUITE(suite_rule_dempster)

BOOST_AUTO_TEST_CASE(test_rule_dempster_has_neutral_element)
{
    rule_dempster rule;

    const mass<fodFO>::container_type ma1 = {0, 0.3, 0, 0.7};
    const mass<fodFO> m1(ma1);
    const mass<fodFO> m_neutral_element(vacuous);
    const mass<fodFO> & m_expected = m1;

    mass<fodFO> m_actual = m1.apply(rule, m_neutral_element);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_rule_dempster_is_commutative)
{
    rule_dempster rule;

    const mass<fodFO>::container_type ma1 = {0, 0.3, 0.7, 0};
    const mass<fodFO> m1(ma1);
    const mass<fodFO>::container_type ma2 = {0, 0.5, 0.4, 0.1};
    const mass<fodFO> m2(ma2);

    const mass<fodFO>::container_type mae = {0, 0.18 / 0.53, 0.35 / 0.53, 0};
    const mass<fodFO> m_expected(mae);
    mass<fodFO> m_actual12 = m1.apply(rule, m2);
    mass<fodFO> m_actual21 = m2.apply(rule, m1);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_actual12[i], m_actual21[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual12[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual21[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_rule_dempster_is_associative)
{
    rule_dempster rule;

    const mass<fodFO>::container_type ma1 = {0, 0.3, 0.7, 0};
    const mass<fodFO> m1(ma1);
    const mass<fodFO>::container_type ma2 = {0, 0.5, 0.4, 0.1};
    const mass<fodFO> m2(ma2);
    const mass<fodFO>::container_type ma3 = {0.1, 0.2, 0.7, 0};
    const mass<fodFO> m3(ma3);

    const mass<fodFO>::container_type mae = {0, 0.036 / 0.281, 0.245 / 0.281, 0.0};
    const mass<fodFO> m_expected(mae);
    mass<fodFO> m_actual12_3 = m1.apply(rule, m2).apply(rule, m3);
    mass<fodFO> m_actual1_23 = m1.apply(rule, m2.apply(rule, m3));

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_actual12_3[i], m_actual1_23[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual12_3[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual1_23[i], 1e-10);
    }
}

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
#include <boost/belief/rule_disjunctive.hpp>

BOOST_AUTO_TEST_SUITE(suite_rule_disjunctive)

BOOST_AUTO_TEST_CASE(test_rule_disjunctive_has_neutral_element)
{
    rule_disjunctive rule;

    const mass<fodFO>::container_type ma1 = {0, 0.66, 0.24, 0.1};
    const mass<fodFO> m1(ma1);
    const mass<fodFO> m_neutral_element(degenerate);
    const mass<fodFO> & m_expected = m1;

    mass<fodFO> m_actual = m1.apply(rule, m_neutral_element);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_rule_disjunctive_is_commutative)
{
    rule_disjunctive rule;

    const mass<fodFO>::container_type ma1 = {0, 0.3, 0.7, 0};
    const mass<fodFO> m1(ma1);
    const mass<fodFO>::container_type ma2 = {0, 0.5, 0.4, 0.1};
    const mass<fodFO> m2(ma2);

    const mass<fodFO>::container_type mae = {0, 0.15, 0.28, 0.57}; // TODO: check
    const mass<fodFO> m_expected(mae);
    mass<fodFO> m_actual12 = m1.apply(rule, m2);
    mass<fodFO> m_actual21 = m2.apply(rule, m1);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_actual12[i], m_actual21[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual12[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual21[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_rule_disjunctive_is_associative)
{
    rule_disjunctive rule;

    const mass<fodFO>::container_type ma1 = {0, 0.3, 0.7, 0};
    const mass<fodFO> m1(ma1);
    const mass<fodFO>::container_type ma2 = {0, 0.5, 0.4, 0.1};
    const mass<fodFO> m2(ma2);
    const mass<fodFO>::container_type ma3 = {0.1, 0.2, 0.7, 0};
    const mass<fodFO> m3(ma3);

    const mass<fodFO>::container_type mae = {0, 0.045, 0.224, 0.731}; // TODO: check
    const mass<fodFO> m_expected(mae);
    mass<fodFO> m_actual12_3 = m1.apply(rule, m2).apply(rule, m3);
    mass<fodFO> m_actual1_23 = m1.apply(rule, m2.apply(rule, m3));

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_actual12_3[i], m_actual1_23[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual12_3[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual1_23[i], 1e-10);
    }
}

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
#include <boost/belief/rule_dubois_prade.hpp>

BOOST_AUTO_TEST_SUITE(suite_rule_dubois_prade)

BOOST_AUTO_TEST_CASE(test_rule_dubois_prade_is_equivalent_to_conjunctive_when_no_conflict)
{
    rule_dubois_prade rule;

    const mass<fodFO>::container_type ma1 = {0, 0.6, 0, 0.4};
    const mass<fodFO> m1(ma1);
    const mass<fodFO>::container_type ma2 = {0, 0.8, 0, 0.2};
    const mass<fodFO> m2(ma2);

    const mass<fodFO>::container_type mae = {0, 0.92, 0, 0.08};
    const mass<fodFO> m_expected(mae);
    mass<fodFO> m_actual_conj = m1.apply(rule_conjunctive(), m2);
    mass<fodFO> m_actual_dp = m1.apply(rule, m2);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_actual_conj[i], m_actual_dp[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual_conj[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual_dp[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_rule_dubois_prade_is_equivalent_to_disjunctive_when_total_conflict)
{
    rule_dubois_prade rule;

    const mass<fodFO>::container_type ma1 = {0, 1, 0, 0};
    const mass<fodFO> m1(ma1);
    const mass<fodFO>::container_type ma2 = {0, 0, 1, 0};
    const mass<fodFO> m2(ma2);

    const mass<fodFO>::container_type mae = {0, 0, 0, 1};
    const mass<fodFO> m_expected(mae);
    mass<fodFO> m_actual_disj = m1.apply(rule_disjunctive(), m2);
    mass<fodFO> m_actual_dp = m1.apply(rule, m2);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_actual_disj[i], m_actual_dp[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual_disj[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual_dp[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_rule_dubois_prade_is_commutative)
{
    rule_dubois_prade rule;

    const mass<fodFO>::container_type ma1 = {0, 0.3, 0.7, 0};
    const mass<fodFO> m1(ma1);
    const mass<fodFO>::container_type ma2 = {0, 0.5, 0.4, 0.1};
    const mass<fodFO> m2(ma2);

    const mass<fodFO>::container_type mae = {0, 0.18, 0.35, 0.47}; // TODO: check
    const mass<fodFO> m_expected(mae);
    mass<fodFO> m_actual12 = m1.apply(rule, m2);
    mass<fodFO> m_actual21 = m2.apply(rule, m1);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_actual12[i], m_actual21[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual12[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual21[i], 1e-10);
    }
}

// test_rule_dubois_prade_is_not_associative

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
#include <boost/belief/conjunctive_decomposition.hpp>

BOOST_AUTO_TEST_SUITE(suite_conjunctive_decomposition)

BOOST_AUTO_TEST_CASE(test_conjunctive_decomposition_gives_correct_result)
{
    conjunctive_decomposition decomposition;

    const mass<fodFO>::container_type ma = {0, 0.3, 0, 0.7};
    const mass<fodFO> m(ma);

    const dst_function<fodFO>::container_type wae = {1, 0.7, 1, std::numeric_limits<double>::quiet_NaN()};
    const dst_function<fodFO> w_expected(wae);
    dst_function<fodFO> w_actual = m.apply(decomposition);

    for(std::size_t i = 0; i < fodFO::powerset_size-1; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(w_expected[i], w_actual[i], 1e-10);
    }
    BOOST_CHECK(math::isnan(w_expected.values().back()));
}

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
#include <boost/belief/rule_conjunctive_cautious.hpp>

BOOST_AUTO_TEST_SUITE(suite_rule_conjunctive_cautious)

// test_rule_conjunctive_cautious_has_not_neutral_element

BOOST_AUTO_TEST_CASE(test_rule_conjunctive_cautious_is_commutative)
{
    typedef fodABC fod;
    rule_conjunctive_cautious rule;

    const mass<fod>::container_type ma1 = {0, 0, 0, 0.3, 0, 0, 0.5, 0.2};
    const mass<fod> m1(ma1);
    const mass<fod>::container_type ma2 = {0, 0, 0.3, 0, 0, 0, 0.4, 0.3};
    const mass<fod> m2(ma2);

    const mass<fod>::container_type mae = {0, 0, 0.6, 0.12, 0, 0, 0.2, 0.08};
    const mass<fod> m_expected(mae);
    mass<fod> m_actual12 = m1.apply(rule, m2);
    mass<fod> m_actual21 = m2.apply(rule, m1);

    for(std::size_t i = 0; i < fod::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_actual12[i], m_actual21[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual12[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual21[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_rule_conjunctive_cautious_is_associative)
{
    typedef fodABC fod;
    rule_conjunctive_cautious rule;

    const mass<fod>::container_type ma1 = {0, 0, 0, 0.3, 0, 0, 0.5, 0.2};
    const mass<fod> m1(ma1);
    const mass<fod>::container_type ma2 = {0, 0, 0.3, 0, 0, 0, 0.4, 0.3};
    const mass<fod> m2(ma2);
    const mass<fod>::container_type ma3 = {0, 0.2, 0, 0, 0, 0, 0.3, 0.5};
    const mass<fod> m3(ma3);

    mass<fod> m_actual12_3 = m1.apply(rule, m2).apply(rule, m3);
    mass<fod> m_actual1_23 = m1.apply(rule, m2.apply(rule, m3));

    for(std::size_t i = 0; i < fod::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_actual12_3[i], m_actual1_23[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_rule_conjunctive_cautious_is_idempotent)
{
    typedef fodABC fod;
    rule_conjunctive_cautious rule;

    const mass<fod>::container_type ma1 = {0, 0, 0, 0.3, 0, 0, 0.5, 0.2};
    const mass<fod> m1(ma1);
    const mass<fod>::container_type ma2 = {0, 0, 0.3, 0, 0, 0, 0.4, 0.3};
    const mass<fod> m2(ma2);

    const mass<fod>::container_type mae = {0, 0, 0.6, 0.12, 0, 0, 0.2, 0.08};
    const mass<fod> m_expected(mae);
    mass<fod> m_actual12 = m1.apply(rule, m2);
    mass<fod> m_actual121 = m_actual12.apply(rule, m1);

    for(std::size_t i = 0; i < fod::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_actual12[i], m_actual121[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual12[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual121[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_rule_conjunctive_is_distributive_wrt_rule_conjunctive_cautious)
{
    // C - conjunctive, P - conjunctive cautious
    // m1 C (m2 P m3) <==> (m1 C m2) P (m1 C m3)
    typedef fodABC fod;

    const mass<fod>::container_type ma1 = {0, 0, 0, 0.3, 0, 0, 0.5, 0.2};
    const mass<fod> m1(ma1);
    const mass<fod>::container_type ma2 = {0, 0, 0.3, 0, 0, 0, 0.4, 0.3};
    const mass<fod> m2(ma2);
    const mass<fod>::container_type ma3 = {0, 0.2, 0, 0, 0, 0, 0.3, 0.5};
    const mass<fod> m3(ma3);

    mass<fod> m_actual1_C_2P3 = m1
        .apply(rule_conjunctive(),
        m2.apply(rule_conjunctive_cautious(), m3));
    mass<fod> m_actual1C2_P_1C3 = m1.apply(rule_conjunctive(), m2)
        .apply(rule_conjunctive_cautious(),
        m1.apply(rule_conjunctive(), m3));

    for(std::size_t i = 0; i < fod::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_actual1_C_2P3[i], m_actual1C2_P_1C3[i], 1e-10);
    }
}

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
#include <boost/belief/disjunctive_decomposition.hpp>

BOOST_AUTO_TEST_SUITE(suite_disjunctive_decomposition)

BOOST_AUTO_TEST_CASE(test_disjunctive_decomposition_gives_correct_result)
{
    typedef fodABC fod;
    disjunctive_decomposition decomposition;

    const mass<fod>::container_type ma = {0.1, 0, 0, 0.3, 0, 0, 0.6, 0};
    const mass<fod> m(ma);

    const dst_function<fod>::container_type vae = {std::numeric_limits<double>::quiet_NaN(), 1, 1, 0.25, 1, 1, 1./7, 2.8};
    const dst_function<fod> v_expected(vae);
    dst_function<fod> v_actual = m.apply(decomposition);

    BOOST_CHECK(math::isnan(v_expected.values().front()));
    for(std::size_t i = 1; i < fod::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(v_expected[i], v_actual[i], 1e-10);
    }
}

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
#include <boost/belief/rule_disjunctive_bold.hpp>

BOOST_AUTO_TEST_SUITE(suite_rule_disjunctive_bold)

// test_rule_disjunctive_bold_has_not_neutral_element

BOOST_AUTO_TEST_CASE(test_rule_disjunctive_bold_is_commutative)
{
    typedef fodABC fod;
    rule_disjunctive_bold rule;

    const mass<fod>::container_type ma1 = {0.1, 0, 0, 0.3, 0, 0, 0.6, 0};
    const mass<fod> m1(ma1);
    const mass<fod>::container_type ma2 = {0.1, 0, 0.5, 0, 0, 0, 0.4, 0};
    const mass<fod> m2(ma2);

    const mass<fod>::container_type mae = {0.0059523809523809538, 0, 0.029761904761904767, 0.10714285714285712, 0, 0, 0.21428571428571427, 0.64285714285714279};
    const mass<fod> m_expected(mae);
    mass<fod> m_actual12 = m1.apply(rule, m2);
    mass<fod> m_actual21 = m2.apply(rule, m1);

    for(std::size_t i = 0; i < fod::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_actual12[i], m_actual21[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual12[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual21[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_rule_disjunctive_bold_is_associative)
{
    typedef fodABC fod;
    rule_disjunctive_bold rule;

    const mass<fod>::container_type ma1 = {0.1, 0, 0, 0.3, 0, 0, 0.6, 0};
    const mass<fod> m1(ma1);
    const mass<fod>::container_type ma2 = {0.1, 0, 0.5, 0, 0, 0, 0.4, 0};
    const mass<fod> m2(ma2);
    const mass<fod>::container_type ma3 = {0.2, 0, 0.3, 0.2, 0, 0, 0, 0.3};
    const mass<fod> m3(ma3);

    mass<fod> m_actual12_3 = m1.apply(rule, m2).apply(rule, m3);
    mass<fod> m_actual1_23 = m1.apply(rule, m2.apply(rule, m3));

    for(std::size_t i = 0; i < fod::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_actual12_3[i], m_actual1_23[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_rule_disjunctive_bold_is_idempotent)
{
    typedef fodABC fod;
    rule_disjunctive_bold rule;

    const mass<fod>::container_type ma1 = {0.1, 0, 0, 0.3, 0, 0, 0.6, 0};
    const mass<fod> m1(ma1);
    const mass<fod>::container_type ma2 = {0.1, 0, 0.5, 0, 0, 0, 0.4, 0};
    const mass<fod> m2(ma2);

    const mass<fod>::container_type mae = {0.0059523809523809538, 0, 0.029761904761904767, 0.10714285714285712, 0, 0, 0.21428571428571427, 0.64285714285714279};
    const mass<fod> m_expected(mae);
    mass<fod> m_actual12 = m1.apply(rule, m2);
    mass<fod> m_actual121 = m_actual12.apply(rule, m1);

    for(std::size_t i = 0; i < fod::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_actual12[i], m_actual121[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual12[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual121[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_rule_disjunctive_is_distributive_wrt_rule_disjunctive_bold)
{
    // C - disjunctive, P - disjunctive bold
    // m1 C (m2 P m3) <==> (m1 C m2) P (m1 C m3)
    typedef fodABC fod;

    const mass<fod>::container_type ma1 = {0.1, 0, 0, 0.3, 0, 0, 0.6, 0};
    const mass<fod> m1(ma1);
    const mass<fod>::container_type ma2 = {0.1, 0, 0.5, 0, 0, 0, 0.4, 0};
    const mass<fod> m2(ma2);
    const mass<fod>::container_type ma3 = {0.2, 0, 0.3, 0.2, 0, 0, 0, 0.3};
    const mass<fod> m3(ma3);

    mass<fod> m_actual1_C_2P3 = m1
        .apply(rule_disjunctive(),
        m2.apply(rule_disjunctive_bold(), m3));
    mass<fod> m_actual1C2_P_1C3 = m1.apply(rule_disjunctive(), m2)
        .apply(rule_disjunctive_bold(),
        m1.apply(rule_disjunctive(), m3));

    for(std::size_t i = 0; i < fod::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_actual1_C_2P3[i], m_actual1C2_P_1C3[i], 1e-10);
    }
}

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
#include <boost/belief/rule_normalization_inagaki.hpp>
#include <boost/belief/rule_yager.hpp>

BOOST_AUTO_TEST_SUITE(suite_rule_inagaki)

BOOST_AUTO_TEST_CASE(test_rule_inagaki_equals_rule_yager_when_k_equals_0)
{
    const mass<fodFO>::container_type ma1 = {0, 0.3, 0.7, 0};
    const mass<fodFO> m1(ma1);
    const mass<fodFO>::container_type ma2 = {0, 0.5, 0.4, 0.1};
    const mass<fodFO> m2(ma2);

    const mass<fodFO> m_expected = m1.apply(rule_yager(), m2);
    const mass<fodFO> m = m1.apply(rule_conjunctive(), m2);
    const mass<fodFO> m_actual = m.apply(rule_normalization_inagaki(0));

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_rule_inagaki_equals_rule_dempster_when_k_equals_1_over_1_minus_conflict_mass)
{
    const mass<fodFO>::container_type ma1 = {0, 0.3, 0.7, 0};
    const mass<fodFO> m1(ma1);
    const mass<fodFO>::container_type ma2 = {0, 0.5, 0.4, 0.1};
    const mass<fodFO> m2(ma2);

    const mass<fodFO> m_expected = m1.apply(rule_dempster(), m2);
    const mass<fodFO> m = m1.apply(rule_conjunctive(), m2);
    double k = 1 / (1 - m.values().front());
    const mass<fodFO> m_actual = m.apply(rule_normalization_inagaki(k));

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(2-m_expected[i], 2-m_actual[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_rule_inagaki_extra_rule_gives_correct_result)
{
    const mass<fodFO>::container_type ma1 = {0, 0.3, 0.5, 0.2};
    const mass<fodFO> m1(ma1);
    const mass<fodFO>::container_type ma2 = {0, 0.5, 0.4, 0.1};
    const mass<fodFO> m2(ma2);

    const mass<fodFO>::container_type mae = {0/*0.37*/, 0.28 * (1 + 0.37/0.61), 0.33 * (1 + 0.37/0.61), 0.02};
    const mass<fodFO> m_expected(mae);
    const mass<fodFO> m = m1.apply(rule_conjunctive(), m2);
    double k = 1 / (1 - m.values().front() - m.values().back());
    const mass<fodFO> m_actual = m.apply(rule_normalization_inagaki(k));

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
    }
}

// TODO: rule_inagaki_throws_when_k_greater_than_1_over_1_minus_conflict_mass_minus_unknown_mass

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
#include <boost/belief/rule_normalization.hpp>

BOOST_AUTO_TEST_SUITE(suite_rule_normalization)

// TODO: what behaviour should have rule_normalization when mass<EmptySet>() == 1.0 (total conflict)?

//BOOST_AUTO_TEST_CASE(test_rule_normalization_throws_when_total_conflict)
//{
//	rule_normalization rule;
//
//	const mass<fodFO>::container_type ma1 = {1, 0, 0, 0};
//	const mass<fodFO> m1(ma1);
//	mass<fodFO> m_actual = m1.apply(rule);
//
//	for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
//		//BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
//		BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
//		BOOST_CHECK_CLOSE(m1[i], m_actual[i], 1e-10);
//	}
//}

BOOST_AUTO_TEST_CASE(test_rule_normalization_is_correct_wo_conflict)
{
    rule_normalization rule;

    const mass<fodFO>::container_type ma1 = {0, 0.3, 0.4, 0.3};
    const mass<fodFO> m1(ma1);

    const mass<fodFO> m_expected(ma1);
    mass<fodFO> m_actual = m1.apply(rule);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_rule_normalization_is_correct_with_conflict)
{
    rule_normalization rule;

    const mass<fodFO>::container_type ma1 = {0.2, 0.3, 0.4, 0.1};
    const mass<fodFO> m1(ma1);

    const mass<fodFO>::container_type mae = {0, 3./8, 4./8, 1./8}; // TODO: check
    const mass<fodFO> m_expected(mae);
    mass<fodFO> m_actual = m1.apply(rule);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
    }
}

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
#include <boost/belief/rule_pcr5.hpp>

BOOST_AUTO_TEST_SUITE(suite_rule_pcr5)

BOOST_AUTO_TEST_CASE(test_rule_pcr5_is_commutative)
{
    rule_pcr5 rule;

    const mass<fodFO>::container_type ma1 = {0, 0.6, 0, 0.4};
    const mass<fodFO> m1(ma1);
    const mass<fodFO>::container_type ma2 = {0, 0, 0.3, 0.7};
    const mass<fodFO> m2(ma2);

    const mass<fodFO>::container_type mae = {0, 0.54, 0.18, 0.28};
    const mass<fodFO> m_expected(mae);
    mass<fodFO> m_actual12 = m1.apply(rule, m2);
    mass<fodFO> m_actual21 = m2.apply(rule, m1);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_actual12[i], m_actual21[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual12[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual21[i], 1e-10);
    }
}

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
#include <boost/belief/rule_yager.hpp>

BOOST_AUTO_TEST_SUITE(suite_rule_yager)

BOOST_AUTO_TEST_CASE(test_rule_yager_gives_correct_result)
{
    rule_yager rule;

    const mass<fodFO>::container_type ma1 = {0, 0.3, 0.7, 0};
    const mass<fodFO> m1(ma1);
    const mass<fodFO>::container_type ma2 = {0, 0.5, 0.4, 0.1};
    const mass<fodFO> m2(ma2);

    const mass<fodFO>::container_type mae = {0, 0.18, 0.35, 0.47};
    const mass<fodFO> m_expected(mae);
    mass<fodFO> m_actual12 = m1.apply(rule, m2);
    mass<fodFO> m_actual21 = m2.apply(rule, m1);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_actual12[i], m_actual21[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual12[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual21[i], 1e-10);
    }
}

BOOST_AUTO_TEST_SUITE_END()
