//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE TestBoostBFT

#ifdef _MSC_VER
#   pragma warning(disable:4505) // unused function
#   pragma warning(disable:4514) // automatically linked headers
#   pragma warning(disable:4710) // automatically linked headers

#   pragma warning(push)	// disable for this header only
#   pragma warning(disable:4265)
#   pragma warning(disable:4347)
#   pragma warning(disable:4365)
#   pragma warning(disable:4548)
#   pragma warning(disable:4571)
#   pragma warning(disable:4625)
#   pragma warning(disable:4626)
#   pragma warning(disable:4640)
#   pragma warning(disable:4668)
#   pragma warning(disable:4820)
#elif defined(__GNUC__)
#   pragma GCC diagnostic ignored "-Wunused-function"

#   pragma GCC diagnostic push
#endif // _MSC_VER

#include <boost/mpl/equal.hpp>
#include <boost/limits.hpp>
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#ifdef _MSC_VER
#   pragma warning(pop)  	// restore original warning level
#elif defined(__GNUC__)
#   pragma GCC diagnostic pop
#endif // _MSC_VER

#include <boost/bft/bft_function.hpp>
#include <boost/bft/fod.hpp>

using namespace boost;
using namespace boost::bft;
namespace bm = boost::mpl;

BOOST_BFT_DEFINE_CLASS(Free);
BOOST_BFT_DEFINE_CLASS(Occupied);
BOOST_BFT_DEFINE_CLASS(Infrastructure);
BOOST_BFT_DEFINE_CLASS(Movable);

typedef fod<Free, Occupied> fodFO;
typedef fod<Free, Occupied, Infrastructure, Movable> fodFOIM;
typedef bft_function<fodFO> dfFO;
typedef bft_function<fodFOIM> dfFOIM;

/*
#include <boost/numeric/interval.hpp>
#include <limits>

//typedef float_interval boost::numeric::interval<float>;
float inf = std::numeric_limits<float>::infinity();
interval_fod<float> ifodR(-inf, +inf);
*/

//==============================================================================
BOOST_AUTO_TEST_SUITE(suite_fod)

BOOST_AUTO_TEST_CASE(test_fod_static_sizes)
{
    typedef fod<Free, Occupied> fodFO;
    typedef fod<Free, Occupied> fodOF;

    //typedef sort<fodFO, less<index_of<fodOF, _1>, index_of<fodOF, _2> > >::type Sorted;

    /*BOOST_STATIC_ASSERT(
    (
    equal<sort<v1, less<index_of<v2, _1>, index_of<v2, _2> > >::type
    ,
    vector<Free, Occupied>
    >::type::value
    )
    );*/
    BOOST_STATIC_ASSERT_MSG((bm::equal<fodFO::type, fodOF::type>::type::value), "ERROR: You have to use the same frames of discernments (fod)!");
    BOOST_STATIC_ASSERT_MSG((fodFO::set_size == 2), "Size of class set (N) in fod<Free, Occupied> should be 2!!!");
    BOOST_STATIC_ASSERT_MSG((fodFO::powerset_size == 4), "Size of class powerset (2^N) in fod<Free, Occupied> should be 4!!!");
    BOOST_CHECK_EQUAL(static_cast<int>(fodFO::set_size), 2);
    BOOST_CHECK_EQUAL(static_cast<int>(fodFO::powerset_size), 4);
}

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
#include <boost/bft/belief.hpp>
#include <boost/bft/to_belief.hpp>
#include <boost/bft/to_mass.hpp>

BOOST_AUTO_TEST_SUITE(suite_belief)

BOOST_AUTO_TEST_CASE(test_to_belief_compiles)
{
    mass<fodFO> m_expected(vacuous);
    belief<fodFO> bel_expected(vacuous);

    belief<fodFO> bel_actual = to_belief(m_expected);
    mass<fodFO> m_actual = to_mass(bel_actual);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(bel_expected[i], bel_actual[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_to_belief_wo_conflict_mass)
{
    mass<fodFO>::container_type ma = {0.0, 0.3, 0.6, 0.1};
    mass<fodFO> m_expected(ma);
    belief<fodFO>::container_type bela = {0.0, 0.3, 0.6, 1.0};
    belief<fodFO> bel_expected(bela);

    belief<fodFO> bel_actual = to_belief(m_expected);
    mass<fodFO> m_actual = to_mass(bel_actual);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(bel_expected[i], bel_actual[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_to_belief_with_conflict_mass)
{
    mass<fodFO>::container_type ma = {0.2, 0.3, 0.4, 0.1};
    mass<fodFO> m_expected(ma);
    belief<fodFO>::container_type bela = {0.0, 0.3, 0.4, 0.8};
    belief<fodFO> bel_expected(bela);

    belief<fodFO> bel_actual = to_belief(m_expected);
    mass<fodFO> m_actual = to_mass(bel_actual);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(bel_expected[i], bel_actual[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
    }
}

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
#include <boost/bft/commonality.hpp>
#include <boost/bft/to_commonality.hpp>

BOOST_AUTO_TEST_SUITE(suite_commonality)

BOOST_AUTO_TEST_CASE(test_to_commonality_compiles)
{
    mass<fodFO> m1;

    commonality<fodFO> q1 = to_commonality(m1);
    mass<fodFO> m2 = to_mass(q1);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        BOOST_CHECK_CLOSE(m1[i], m2[i], 1e-8);
    }
}

BOOST_AUTO_TEST_CASE(test_to_commonality_wo_conflict_mass)
{
    mass<fodFO>::container_type ma = {0.0, 0.3, 0.6, 0.1};
    mass<fodFO> m_expected(ma);
    commonality<fodFO>::container_type qa = {1.0, 0.4, 0.7, 0.1};
    commonality<fodFO> q_expected(qa);

    commonality<fodFO> q_actual = to_commonality(m_expected);
    mass<fodFO> m_actual = to_mass(q_actual);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(q_expected[i], q_actual[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_to_commonality_with_conflict_mass)
{
    mass<fodFO>::container_type ma = {0.2, 0.3, 0.4, 0.1};
    mass<fodFO> m_expected(ma);
    commonality<fodFO>::container_type qa = {1.0, 0.4, 0.5, 0.1};
    commonality<fodFO> q_expected(qa);

    commonality<fodFO> q_actual = to_commonality(m_expected);
    mass<fodFO> m_actual = to_mass(q_actual);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(q_expected[i], q_actual[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
    }
}

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
#include <boost/bft/implicability.hpp>
#include <boost/bft/to_implicability.hpp>

BOOST_AUTO_TEST_SUITE(suite_implicability)

BOOST_AUTO_TEST_CASE(test_to_implicability_compiles)
{
    mass<fodFO> m_expected;
    implicability<fodFO> b_expected;
    implicability<fodFO> b_actual = to_implicability(m_expected);
    mass<fodFO> m_actual = to_mass(b_actual);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(b_expected[i], b_actual[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_to_implicability_wo_conflict_mass)
{
    mass<fodFO>::container_type ma = {0.0, 0.3, 0.6, 0.1};
    mass<fodFO> m_expected(ma);
    implicability<fodFO>::container_type ba = {0.0, 0.3, 0.6, 1.0};
    implicability<fodFO> b_expected(ba);

    implicability<fodFO> b_actual = to_implicability(m_expected);
    mass<fodFO> m_actual = to_mass(b_actual);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(b_expected[i], b_actual[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_to_implicability_with_conflict_mass)
{
    mass<fodFO>::container_type ma = {0.2, 0.3, 0.4, 0.1};
    mass<fodFO> m_expected(ma);
    implicability<fodFO>::container_type ba = {0.2, 0.5, 0.6, 1.0};
    implicability<fodFO> b_expected(ba);

    implicability<fodFO> b_actual = to_implicability(m_expected);
    mass<fodFO> m_actual = to_mass(b_actual);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(b_expected[i], b_actual[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
    }
}

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
#include <boost/bft/to_pignistic.hpp>

BOOST_AUTO_TEST_SUITE(suite_pignistic)

BOOST_AUTO_TEST_CASE(test_to_pignistic_compiles)
{
    mass<fodFO>::container_type ma = {0, 0.6, 0, 0.4};
    mass<fodFO> m(ma);

    bft_function<fodFO>::container_type betPae = {0, 0.8, 0.2, 1};
    bft_function<fodFO> betP_expected(betPae);
    bft_function<fodFO> betP_actual = to_pignistic(m);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(betP_expected[i], betP_actual[i], 1e-10);
    }
}

/*
BOOST_AUTO_TEST_CASE(test_to_pignistic_wo_conflict_mass)
{
mass<fodFO>::container_type ma = {0.0, 0.3, 0.6, 0.1};
mass<fodFO> m_expected(ma);
plausibility<fodFO>::container_type pla = {0.0, 0.4, 0.7, 1.0};
plausibility<fodFO> pl_expected(pla);

plausibility<fodFO> pl_actual = to_plausibility(m_expected);
mass<fodFO> m_actual = to_mass(pl_actual);

for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
//BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
BOOST_CHECK_CLOSE(pl_expected[i], pl_actual[i], 1e-10);
BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
}
}

BOOST_AUTO_TEST_CASE(test_to_pignistic_with_conflict_mass)
{
mass<fodFO>::container_type ma = {0.2, 0.3, 0.4, 0.1};
mass<fodFO> m_expected(ma);
plausibility<fodFO>::container_type pla = {0.0, 0.4, 0.5, 0.8};
plausibility<fodFO> pl_expected(pla);

plausibility<fodFO> pl_actual = to_plausibility(m_expected);
mass<fodFO> m_actual = to_mass(pl_actual);

for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
//BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
BOOST_CHECK_CLOSE(pl_expected[i], pl_actual[i], 1e-10);
BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
}
}
*/

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
#include <boost/bft/plausibility.hpp>
#include <boost/bft/to_plausibility.hpp>

BOOST_AUTO_TEST_SUITE(suite_plausibility)

BOOST_AUTO_TEST_CASE(test_to_plausibility_compiles)
{
    mass<fodFO> m_expected(vacuous);
    plausibility<fodFO> pl_expected(vacuous);

    plausibility<fodFO> pl_actual = to_plausibility(m_expected);
    mass<fodFO> m_actual = to_mass(pl_actual);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix case 1302
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(pl_expected[i], pl_actual[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_to_plausibility_wo_conflict_mass)
{
    mass<fodFO>::container_type ma = {0.0, 0.3, 0.6, 0.1};
    mass<fodFO> m_expected(ma);
    plausibility<fodFO>::container_type pla = {0.0, 0.4, 0.7, 1.0};
    plausibility<fodFO> pl_expected(pla);

    plausibility<fodFO> pl_actual = to_plausibility(m_expected);
    mass<fodFO> m_actual = to_mass(pl_actual);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(pl_expected[i], pl_actual[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_to_plausibility_with_conflict_mass)
{
    mass<fodFO>::container_type ma = {0.2, 0.3, 0.4, 0.1};
    mass<fodFO> m_expected(ma);
    plausibility<fodFO>::container_type pla = {0.0, 0.4, 0.5, 0.8};
    plausibility<fodFO> pl_expected(pla);

    plausibility<fodFO> pl_actual = to_plausibility(m_expected);
    mass<fodFO> m_actual = to_mass(pl_actual);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(pl_expected[i], pl_actual[i], 1e-10);
        BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
    }
}

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

BOOST_AUTO_TEST_SUITE(suite_idx_at)

BOOST_AUTO_TEST_CASE(test_fod_Idx)
{
    BOOST_STATIC_ASSERT( (fod<Free>::Idx<Free>::value == 0) );
    BOOST_CHECK_EQUAL( static_cast<int>(fod<Free>::Idx<Free>::value),  0);

    BOOST_STATIC_ASSERT( (fod<Free, Occupied>::Idx<Free>::value == 0) );
    BOOST_STATIC_ASSERT( (fod<Free, Occupied>::Idx<Occupied>::value == 1) );
}

BOOST_AUTO_TEST_CASE(test_fod_idx)
{
    BOOST_CHECK_EQUAL( (fod<Free, Occupied>::idx<Free>()),  0);
    BOOST_CHECK_EQUAL( (fod<Free, Occupied>::idx<Occupied>()),  1);
}

BOOST_AUTO_TEST_CASE(test_bft_function_Idx)
{
    BOOST_CHECK_EQUAL( static_cast<int>(dfFO::Idx<>::value), 0);
    BOOST_CHECK_EQUAL( static_cast<int>(dfFO::Idx<Free>::value), 1);
    BOOST_CHECK_EQUAL( static_cast<int>(dfFO::Idx<Occupied>::value), 2);
    BOOST_CHECK_EQUAL( static_cast<int>(dfFO::Idx<Free, Occupied>::value), 3);
}

#ifdef _MSC_VER
#   pragma warning(push)	// disable for this part only
#   pragma warning(disable:4347)
#endif // _MSC_VER

BOOST_AUTO_TEST_CASE(test_bft_function_idx)
{
    BOOST_CHECK_EQUAL( (dfFO::idx()), 0);
    BOOST_CHECK_EQUAL( (dfFO::idx<Free>()), 1);
    BOOST_CHECK_EQUAL( (dfFO::idx<Occupied>()), 2);
    BOOST_CHECK_EQUAL( (dfFO::idx<Free, Occupied>()), 3);
}

#ifdef _MSC_VER
#   pragma warning(pop)	// restore original warning level
#endif // _MSC_VER

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
#include <boost/bft/fod_union.hpp>

BOOST_AUTO_TEST_SUITE(suite_fod_union)

BOOST_AUTO_TEST_CASE(test_fod_union)
{
    {
        typedef fod_union<fodFO, fodFO>::type fuFO;
        BOOST_MPL_ASSERT_RELATION(static_cast<int>(fuFO::set_size), ==, 2);
        BOOST_CHECK_EQUAL(static_cast<int>(fuFO::set_size), 2);
    }

    typedef fod<Free> fodF;
    typedef fod<Occupied> fodO;

    {
        typedef fod_union<fodF, fodO>::type fuFO;
        BOOST_MPL_ASSERT_RELATION(static_cast<int>(fuFO::set_size), ==, 2);
        BOOST_MPL_ASSERT((is_same<fuFO, fod<Free, Occupied> >));
    }

    {
        typedef fod_union<fodFO, fodFO>::type fuFO;
        typedef fod_union<fod<Infrastructure>, fod<Movable> >::type fuIM;
        typedef fod_union<fuFO, fuIM>::type fuFOIM;
        BOOST_MPL_ASSERT_RELATION(static_cast<int>(fuFOIM::set_size), ==, 4);
        BOOST_MPL_ASSERT((is_same<fuFO, fod<Free, Occupied> >));
        BOOST_MPL_ASSERT((is_same<fuIM, fod<Infrastructure, Movable> >));
        BOOST_MPL_ASSERT((is_same<fuFOIM, fod<Free, Occupied, Movable, Infrastructure> >)); // FIXME: mind the changed order!
    }
}

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
#include <boost/bft/discounting.hpp>

BOOST_AUTO_TEST_SUITE(suite_discounting)

BOOST_AUTO_TEST_CASE(test_discounting_gives_correct_result)
{
    const mass<fodFO>::container_type ma = {0.2, 0.3, 0.4, 0.1};
    const mass<fodFO> m(ma);

    double alpha = 0.05;
    const mass<fodFO>::container_type mae = {0.19, 0.285, 0.38, 0.145};
    const mass<fodFO> m_expected(mae);
    mass<fodFO> m_actual = m.apply(discounting(alpha));

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
    }
}

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
#include <boost/bft/contextual_discounting.hpp>

BOOST_AUTO_TEST_SUITE(suite_contextual_discounting)

BOOST_AUTO_TEST_CASE(test_contextual_discounting_equals_discounting_when_alphas_of_Omega_equals_alpha_and_rest_of_alphas_are_null)
{
    const mass<fodFO>::container_type ma = {0.2, 0.3, 0.4, 0.1};
    const mass<fodFO> m(ma);

    double alpha = 0.05;
    const mass<fodFO> m_expected = m.apply(discounting(alpha));

    const mass<fodFO>::container_type alphas = {0, 0, 0, alpha};
    mass<fodFO> m_actual = m.apply(contextual_discounting<fodFO>(alphas));

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
    }
}

BOOST_AUTO_TEST_CASE(test_contextual_discounting_gives_correct_result)
{
    const mass<fodFO>::container_type ma = {0, 0.3, 0.7, 0};
    const mass<fodFO> m(ma);

    const mass<fodFO>::container_type mae = {0, 0.27, 0.56, 0.17};
    const mass<fodFO> m_expected(mae);

    const mass<fodFO>::container_type alphas = {0, 0.2, 0.1, 0};
    mass<fodFO> m_actual = m.apply(contextual_discounting<fodFO>(alphas));

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
    }
}

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
#include <boost/bft/fod_union.hpp>
#include <boost/bft/extension.hpp>

BOOST_AUTO_TEST_SUITE(suite_extension)

BOOST_AUTO_TEST_CASE(test_extension)
{
    const mass<fod<Free> >::container_type ma = {0.2, 0.8};
    const mass<fod<Free> > m(ma);

    typedef fod_union<fod<Free>, fod<Occupied> >::type fuFO;
    mass<fuFO> m_actual = extension<fod<Occupied> >(m);
    //	BOOST_MPL_ASSERT_RELATION(fuFO::set_size, ==, 2);
    BOOST_MPL_ASSERT((is_same<fod<Free, Occupied>, fuFO>));

    const mass<fodFO>::container_type mae = {0, 0, 0.2, 0.8};
    const mass<fodFO> m_expected(mae);

    for(std::size_t i = 0; i < fodFO::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
    }
}

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
#include <boost/bft/fod_minus.hpp>
#include <boost/bft/marginalization.hpp>

BOOST_AUTO_TEST_SUITE(suite_marginalization)

BOOST_AUTO_TEST_CASE(test_marginalization)
{
    const mass<fodFO>::container_type ma = {0, 0, 0.2, 0.8};
    const mass<fodFO> m(ma);

    typedef fod_minus<fodFO, fod<Occupied> >::type fmF;
    mass<fmF> m_actual = marginalization<fod<Occupied> >(m);
    BOOST_MPL_ASSERT_RELATION(static_cast<int>(fmF::set_size), ==, 1);
    BOOST_MPL_ASSERT((is_same<fod<Free>, fmF>));

    const mass<fod<Free> >::container_type mae = {0.2, 0.8};
    const mass<fod<Free> > m_expected(mae);

    for(std::size_t i = 0; i < fod<Free>::powerset_size; ++i) {
        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_CLOSE(m_expected[i], m_actual[i], 1e-10);
    }
}

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
