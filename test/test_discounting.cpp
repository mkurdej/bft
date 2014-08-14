//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE test_discounting

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
#include <boost/dst/contextual_discounting.hpp>
#include <boost/dst/discounting.hpp>
#include <boost/math/special_functions/fpclassify.hpp>

#ifdef _MSC_VER
#   pragma warning(pop)  	// restore original warning level
#elif defined(__GNUC__)
#   pragma GCC diagnostic pop
#endif // _MSC_VER

using namespace boost;
using namespace boost::dst;

BOOST_DST_DEFINE_CLASS(C1);
BOOST_DST_DEFINE_CLASS(C2);
BOOST_DST_DEFINE_CLASS(C3);
BOOST_DST_DEFINE_CLASS(C4);

typedef fod<C1, C2> fod2;
typedef fod<C1, C2, C3> fod3;

typedef fod2 fodFO;
typedef fod3 fodABC;

//==============================================================================
#include <boost/dst/rule_conjunctive.hpp>

BOOST_AUTO_TEST_SUITE(suite_rule_discounting)

BOOST_AUTO_TEST_CASE(test_discounting_2_classes)
{
    const mass<fodFO>::container_type ma1 = {0, 0.3, 0.7, 0};
    const mass<fodFO> m1(ma1);
    const mass<fodFO>::container_type mae = {0, 0.27, 0.63, 0.1};
    const mass<fodFO> m_expected(mae);

    discounting discount(0.1);
    mass<fodFO> m1_discounted = m1.apply(discount);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_expected[i], m1_discounted[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_discounting_Mercier2006_Ex1)
{
    // Example 1 from [Mercier2006]
    const mass<fodABC>::container_type ma1 = {0, 0.5 /*a*/, 0 /*h*/, 0 /*ah*/, 0.5 /*r*/, 0 /*ar*/, 0 /*hr*/, 0.0 /*ahr*/};
    const mass<fodABC> m1(ma1);
    const mass<fodABC>::container_type mae = {0, 0.3 /*a*/, 0 /*h*/, 0 /*ah*/, 0.3 /*r*/, 0 /*ar*/, 0 /*hr*/, 0.4 /*ahr*/};
    const mass<fodABC> m_expected(mae);

    discounting discount(0.4);
    mass<fodABC> m1_discounted = m1.apply(discount);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_expected[i], m1_discounted[i], 1e-10);
    }
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(suite_rule_contextual_discounting)

BOOST_AUTO_TEST_CASE(test_contextual_discounting_same_as_discounting)
{
    const mass<fodFO>::container_type ma1 = {0, 0.3, 0.7, 0};
    const mass<fodFO> m1(ma1);

    discounting discount(0.1);
    mass<fodFO> m1_discounted = m1.apply(discount);

    const mass<fodFO>::container_type alphas = {0, 0 /*A*/, 0 /*B*/, 0.1 /*AB*/};
    contextual_discounting<fodFO> context_discount(alphas);
    mass<fodFO> m1_context_discounted = m1.apply(context_discount);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m1_context_discounted[i], m1_discounted[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_contextual_discounting_Mercier2006_Ex2C1)
{
    // Example 2 Case 1 from [Mercier2006]
    const mass<fodABC>::container_type ma1 = {0, 0.5 /*a*/, 0 /*h*/, 0 /*ah*/, 0.5 /*r*/, 0 /*ar*/, 0 /*hr*/, 0 /*ahr*/};
    const mass<fodABC> m1(ma1);
    const mass<fodABC>::container_type mae = {0, 0.5 /*a*/, 0 /*h*/, 0 /*ah*/, 0.3 /*r*/, 0 /*ar*/, 0.2 /*hr*/, 0 /*ahr*/};
    const mass<fodABC> m_expected(mae);

    const mass<fodABC>::container_type alphas = {0, 0.4 /*a*/, 0 /*h*/, 0 /*ah*/, 0 /*r*/, 0 /*ar*/, 0 /*hr*/, 0 /*ahr*/};
    contextual_discounting<fodABC> context_discount(alphas);
    mass<fodABC> m1_context_discounted = m1.apply(context_discount);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_expected[i], m1_context_discounted[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_contextual_discounting_Mercier2006_Ex2C2)
{
    // Example 2 Case 2 from [Mercier2006]
    const mass<fodABC>::container_type ma1 = {0, 0.5 /*a*/, 0 /*h*/, 0 /*ah*/, 0.5 /*r*/, 0 /*ar*/, 0 /*hr*/, 0 /*ahr*/};
    const mass<fodABC> m1(ma1);
    const mass<fodABC>::container_type mae = {0, 0.2 /*a*/, 0 /*h*/, 0.3 /*ah*/, 0.2 /*r*/, 0 /*ar*/, 0.3 /*hr*/, 0 /*ahr*/};
    const mass<fodABC> m_expected(mae);

    const mass<fodABC>::container_type alphas = {0, 0 /*a*/, 0.6 /*h*/, 0 /*ah*/, 0 /*r*/, 0 /*ar*/, 0 /*hr*/, 0 /*ahr*/};
    contextual_discounting<fodABC> context_discount(alphas);
    mass<fodABC> m1_context_discounted = m1.apply(context_discount);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_expected[i], m1_context_discounted[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_contextual_discounting_Mercier2006_Ex2C3)
{
    // Example 2 Case 3 from [Mercier2006]
    const mass<fodABC>::container_type ma1 = {0, 0.5 /*a*/, 0 /*h*/, 0 /*ah*/, 0.5 /*r*/, 0 /*ar*/, 0 /*hr*/, 0.0 /*ahr*/};
    const mass<fodABC> m1(ma1);
    const mass<fodABC>::container_type mae = {0, 0.2 /*a*/, 0 /*h*/, 0.3 /*ah*/, 0.12 /*r*/, 0.08 /*ar*/, 0.18 /*hr*/, 0.12 /*ahr*/};
    const mass<fodABC> m_expected(mae);

    const mass<fodABC>::container_type alphas = {0, 0.4 /*a*/, 0.6 /*h*/, 0 /*ah*/, 0 /*r*/, 0 /*ar*/, 0 /*hr*/, 0 /*ahr*/};
    contextual_discounting<fodABC> context_discount(alphas);
    mass<fodABC> m1_context_discounted = m1.apply(context_discount);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_expected[i], m1_context_discounted[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_contextual_discounting_Mercier2006_Ex3)
{
    // Example 3 from [Mercier2006]
    const mass<fodABC>::container_type ma1 = {0, 0.5 /*a*/, 0 /*h*/, 0 /*ah*/, 0.5 /*r*/, 0 /*ar*/, 0 /*hr*/, 0.0 /*ahr*/};
    const mass<fodABC> m1(ma1);
    const mass<fodABC>::container_type mae = {0, 0.45 /*a*/, 0 /*h*/, 0 /*ah*/, 0.18 /*r*/, 0.27 /*ar*/, 0.02 /*hr*/, 0.08 /*ahr*/};
    const mass<fodABC> m_expected(mae);

    const mass<fodABC>::container_type alphas = {0, 0.6 /*a*/, 0 /*h*/, 0 /*ah*/, 0 /*r*/, 0 /*ar*/, 0.1 /*hr*/, 0 /*ahr*/};
    contextual_discounting<fodABC> context_discount(alphas);
    mass<fodABC> m1_context_discounted = m1.apply(context_discount);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_expected[i], m1_context_discounted[i], 1e-10);
    }
}

BOOST_AUTO_TEST_SUITE_END()
