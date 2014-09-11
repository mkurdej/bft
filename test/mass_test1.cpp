//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE test_mass

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
#include <boost/bft/mass.hpp>
#include <boost/bft/to_mass.hpp>

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

BOOST_AUTO_TEST_CASE(test_mass_compiles)
{
    mass<fod2> m;
    for (std::size_t i = 0; i < fod2::powerset_size; ++i) {
        // BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
        BOOST_TEST_CHECKPOINT(
            "Calling [i] with i=" << i); // FIXME: wanted but doesn't work
        BOOST_CHECK_SMALL(m[i], 1e-10);
    }
}

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================
BOOST_AUTO_TEST_SUITE(suite_mass_at)

#ifdef _MSC_VER
#pragma warning(push) // disable for this header only
//#pragma warning(disable : 4347)
#endif // _MSC_VER

BOOST_AUTO_TEST_CASE(test_mass_at)
{
    mass<fod2> m;
    m.at() = 0.15;
    m.at<C1>() = 0.55;
    m.at<C2>() = 0.25;
    m.at<C1, C2>() = 0.05;

    BOOST_CHECK_EQUAL((m.at()), 0.15);
    BOOST_CHECK_EQUAL((m.at<C1>()), 0.55);
    BOOST_CHECK_EQUAL((m.at<C2>()), 0.25);
    BOOST_CHECK_EQUAL((m.at<C1, C2>()), 0.05);

    BOOST_CHECK_EQUAL(m[0], 0.15);
    BOOST_CHECK_EQUAL(m[1], 0.55);
    BOOST_CHECK_EQUAL(m[2], 0.25);
    BOOST_CHECK_EQUAL(m[3], 0.05);
}

BOOST_AUTO_TEST_CASE(test_mass_vacuous_at_const)
{
    const mass<fod2> m(vacuous);

    BOOST_CHECK_EQUAL((m.at()), 0.0);
    BOOST_CHECK_EQUAL((m.at<C1>()), 0.0);
    BOOST_CHECK_EQUAL((m.at<C2>()), 0.0);
    BOOST_CHECK_EQUAL((m.at<C1, C2>()), 1.0);

    BOOST_CHECK_EQUAL(m[0], 0.0);
    BOOST_CHECK_EQUAL(m[1], 0.0);
    BOOST_CHECK_EQUAL(m[2], 0.0);
    BOOST_CHECK_EQUAL(m[3], 1.0);
}

BOOST_AUTO_TEST_SUITE_END()

//==============================================================================

BOOST_AUTO_TEST_SUITE(suite_mass_is_)

BOOST_AUTO_TEST_CASE(test_mass_is_focal)
{
    const mass<fod2>::container_type ma = {0, 0.3, 0.7, 0};
    const mass<fod2> m = ma;

    BOOST_CHECK((!m.is_focal(0)));
    BOOST_CHECK((!m.is_focal()));

    BOOST_CHECK((m.is_focal<C1>()));
    BOOST_CHECK((m.is_focal<C2>()));
    BOOST_CHECK((!m.is_focal<C1, C2>()));
}

#ifdef _MSC_VER
#pragma warning(pop) // restore original warning level
#endif               // _MSC_VER

BOOST_AUTO_TEST_CASE(test_mass_is_normal)
{
    {
        const mass<fod2>::container_type ma = {0, 0.3, 0.7, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_normal()));
    }
    {
        const mass<fod2>::container_type ma = {0.3, 0.3, 0.4, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((!m.is_normal()));
    }
}

BOOST_AUTO_TEST_CASE(test_mass_is_regular)
{
    {
        const mass<fod2>::container_type ma = {0, 0.3, 0.7, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_regular()));
    }
    {
        const mass<fod2>::container_type ma = {0.3, 0.3, 0.4, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((!m.is_regular()));
    }
}

BOOST_AUTO_TEST_CASE(test_mass_is_subnormal)
{
    {
        const mass<fod2>::container_type ma = {0, 0.3, 0.7, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((!m.is_subnormal()));
    }
    {
        const mass<fod2>::container_type ma = {0.3, 0.3, 0.4, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_subnormal()));
    }
}

BOOST_AUTO_TEST_CASE(test_mass_is_dogmatic)
{
    {
        const mass<fod2>::container_type ma = {0, 0.3, 0.7, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_dogmatic()));
    }
    {
        const mass<fod2>::container_type ma = {0, 0.3, 0.4, 0.3};
        const mass<fod2> m(ma);
        BOOST_CHECK((!m.is_dogmatic()));
    }
}

BOOST_AUTO_TEST_CASE(test_mass_is_nondogmatic)
{
    {
        const mass<fod2>::container_type ma = {0, 0.3, 0.7, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((!m.is_nondogmatic()));
    }
    {
        const mass<fod2>::container_type ma = {0, 0.3, 0.4, 0.3};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_nondogmatic()));
    }
}

BOOST_AUTO_TEST_CASE(test_mass_is_vacuous)
{
    {
        const mass<fod2>::container_type ma = {0, 0.3, 0.7, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((!m.is_vacuous()));
    }
    {
        const mass<fod2>::container_type ma = {0, 0.3, 0.4, 0.3};
        const mass<fod2> m(ma);
        BOOST_CHECK((!m.is_vacuous()));
    }
    {
        const mass<fod2>::container_type ma = {0, 0, 0, 1};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_vacuous()));
    }
}

BOOST_AUTO_TEST_CASE(test_mass_is_degenerate)
{
    {
        const mass<fod2>::container_type ma = {0, 0.3, 0.7, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((!m.is_degenerate()));
    }
    {
        const mass<fod2>::container_type ma = {0.3, 0.3, 0.4, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((!m.is_degenerate()));
    }
    {
        const mass<fod2>::container_type ma = {1, 0, 0, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_degenerate()));
    }
}

BOOST_AUTO_TEST_CASE(test_mass_is_categorical)
{
    {
        const mass<fod2>::container_type ma = {0, 0.3, 0.7, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((!m.is_categorical()));
    }
    {
        const mass<fod2>::container_type ma = {1, 0, 0, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_categorical()));
    }
    {
        const mass<fod2>::container_type ma = {0, 1, 0, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_categorical()));
    }
    {
        const mass<fod2>::container_type ma = {0, 0, 1, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_categorical()));
    }
    {
        const mass<fod2>::container_type ma = {0, 0, 0, 1};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_categorical()));
    }
}

BOOST_AUTO_TEST_CASE(test_mass_is_simple)
{
    {
        const mass<fod2>::container_type ma = {0, 0.3, 0.7, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((!m.is_simple()));
    }
    {
        const mass<fod2>::container_type ma = {1, 0, 0, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_simple()));
    }
    {
        const mass<fod2>::container_type ma = {0, 1, 0, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_simple()));
    }
    {
        const mass<fod2>::container_type ma = {0, 0, 1, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_simple()));
    }
    {
        const mass<fod2>::container_type ma = {0, 0, 0, 1};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_simple()));
    }
    {
        const mass<fod2>::container_type ma = {0, 0.3, 0, 0.7};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_simple()));
    }
    {
        const mass<fod4>::container_type ma = {0, 0.3, 0, 0.6, 0.1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};
        const mass<fod4> m(ma);
        BOOST_CHECK((!m.is_simple()));
    }
}

BOOST_AUTO_TEST_CASE(test_mass_is_bayesian)
{
    {
        const mass<fod2>::container_type ma = {0, 0.3, 0.7, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_bayesian()));
    }
    {
        const mass<fod2>::container_type ma = {1, 0, 0, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_bayesian()));
    }
    {
        const mass<fod2>::container_type ma = {0, 1, 0, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_bayesian()));
    }
    {
        const mass<fod2>::container_type ma = {0, 0, 1, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_bayesian()));
    }
    {
        const mass<fod2>::container_type ma = {0, 0, 0, 1};
        const mass<fod2> m(ma);
        BOOST_CHECK((!m.is_bayesian()));
    }
    {
        const mass<fod2>::container_type ma = {0, 0.3, 0, 0.7};
        const mass<fod2> m(ma);
        BOOST_CHECK((!m.is_bayesian()));
    }
    {
        const mass<fod4>::container_type ma = {0, 0.3, 0.2, 0, 0.5, 0, 0, 0};
        const mass<fod4> m(ma);
        BOOST_CHECK((m.is_bayesian()));
    }
    {
        const mass<fod4>::container_type ma = {0, 0.3, 0, 0, 0.5, 0, 0.2, 0};
        const mass<fod4> m(ma);
        BOOST_CHECK((!m.is_bayesian()));
    }
}

BOOST_AUTO_TEST_CASE(test_mass_is_consonant)
{
    {
        const mass<fod2>::container_type ma = {0, 0.3, 0.7, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((!m.is_consonant()));
    }
    {
        const mass<fod2>::container_type ma = {1, 0, 0, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_consonant()));
    }
    {
        const mass<fod2>::container_type ma = {0, 1, 0, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_consonant()));
    }
    {
        const mass<fod2>::container_type ma = {0, 0, 1, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_consonant()));
    }
    {
        const mass<fod2>::container_type ma = {0, 0, 0, 1};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_consonant()));
    }
    {
        const mass<fod2>::container_type ma = {0, 0.3, 0, 0.7};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_consonant()));
    }
    {
        const mass<fod4>::container_type ma = {0, 0.3, 0.2, 0, 0.5, 0, 0, 0};
        const mass<fod4> m(ma);
        BOOST_CHECK((!m.is_consonant()));
    }
    {
        const mass<fod4>::container_type ma = {0, 0.3, 0, 0, 0.5, 0, 0.2, 0};
        const mass<fod4> m(ma);
        BOOST_CHECK((!m.is_consonant()));
    }
    {
        const mass<fod4>::container_type ma = {0.1, 0.3, 0, 0.4, 0, 0, 0, 0.2};
        const mass<fod4> m(ma);
        BOOST_CHECK((m.is_consonant()));
    }
    {
        const mass<fod4>::container_type ma = {0.1, 0, 0, 0, 0.5, 0, 0.2, 0.2};
        const mass<fod4> m(ma);
        BOOST_CHECK((m.is_consonant()));
    }
    {
        const mass<fod4>::container_type ma = {0, 0, 0, 0, 0.3, 0.3, 0.2, 0.2};
        const mass<fod4> m(ma);
        BOOST_CHECK((!m.is_consonant()));
    }
}

BOOST_AUTO_TEST_CASE(test_mass_is_consistent)
{
    {
        const mass<fod2>::container_type ma = {0, 0.3, 0.7, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((!m.is_consistent()));
    }
    {
        const mass<fod2>::container_type ma = {1, 0, 0, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_consistent()));
    }
    {
        const mass<fod2>::container_type ma = {0, 1, 0, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_consistent()));
    }
    {
        const mass<fod2>::container_type ma = {0, 0, 1, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_consistent()));
    }
    {
        const mass<fod2>::container_type ma = {0, 0, 0, 1};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_consistent()));
    }
    {
        const mass<fod2>::container_type ma = {0, 0.3, 0, 0.7};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_consistent()));
    }
    {
        const mass<fod4>::container_type ma = {0, 0.3, 0.2, 0, 0.5, 0, 0, 0};
        const mass<fod4> m(ma);
        BOOST_CHECK((!m.is_consistent()));
    }
    {
        const mass<fod4>::container_type ma = {0, 0.3, 0, 0, 0.5, 0, 0.2, 0};
        const mass<fod4> m(ma);
        BOOST_CHECK((!m.is_consistent()));
    }
    {
        const mass<fod4>::container_type ma = {0.1, 0.3, 0, 0.4, 0, 0, 0, 0.2};
        const mass<fod4> m(ma);
        BOOST_CHECK((m.is_consistent()));
    }
    {
        const mass<fod4>::container_type ma = {0.1, 0, 0, 0, 0.5, 0, 0.2, 0.2};
        const mass<fod4> m(ma);
        BOOST_CHECK((m.is_consistent()));
    }
    {
        const mass<fod4>::container_type ma = {0, 0, 0, 0, 0.3, 0.3, 0.2, 0.2};
        const mass<fod4> m(ma);
        BOOST_CHECK((m.is_consistent()));
    }
}

BOOST_AUTO_TEST_CASE(test_mass_is_partitioned)
{
    {
        const mass<fod2>::container_type ma = {1, 0, 0, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((!m.is_partitioned()));
    }
    {
        const mass<fod2>::container_type ma = {0, 1, 0, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((!m.is_partitioned()));
    }
    {
        const mass<fod2>::container_type ma = {0, 0, 0, 1};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_partitioned()));
    }
    {
        const mass<fod2>::container_type ma = {0, 0.3, 0.7, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_partitioned()));
    }
    {
        const mass<fod2>::container_type ma = {0.1, 0.2, 0.7, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.is_partitioned()));
    }
    {
        const mass<fod2>::container_type ma = {0, 0.3, 0.4, 3};
        const mass<fod2> m(ma);
        BOOST_CHECK((!m.is_partitioned()));
    }
}

BOOST_AUTO_TEST_CASE(test_mass_has_internal_conflict)
{
    {
        const mass<fod2>::container_type ma = {0, 0.3, 0.7, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.has_internal_conflict()));
    }
    {
        const mass<fod2>::container_type ma = {1, 0, 0, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((m.has_internal_conflict()));
    }
    {
        const mass<fod2>::container_type ma = {0, 1, 0, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((!m.has_internal_conflict()));
    }
    {
        const mass<fod2>::container_type ma = {0, 0, 1, 0};
        const mass<fod2> m(ma);
        BOOST_CHECK((!m.has_internal_conflict()));
    }
    {
        const mass<fod2>::container_type ma = {0, 0, 0, 1};
        const mass<fod2> m(ma);
        BOOST_CHECK((!m.has_internal_conflict()));
    }
    {
        const mass<fod2>::container_type ma = {0, 0.3, 0, 0.7};
        const mass<fod2> m(ma);
        BOOST_CHECK((!m.has_internal_conflict()));
    }
    {
        const mass<fod4>::container_type ma = {0, 0.3, 0.2, 0, 0.5, 0, 0, 0};
        const mass<fod4> m(ma);
        BOOST_CHECK((m.has_internal_conflict()));
    }
    {
        const mass<fod4>::container_type ma = {0, 0.3, 0, 0, 0.5, 0, 0.2, 0};
        const mass<fod4> m(ma);
        BOOST_CHECK((m.has_internal_conflict()));
    }
    {
        const mass<fod4>::container_type ma = {0.1, 0.3, 0, 0.4, 0, 0, 0, 0.2};
        const mass<fod4> m(ma);
        BOOST_CHECK((m.has_internal_conflict()));
    }
    {
        const mass<fod4>::container_type ma = {0.1, 0, 0, 0, 0.5, 0, 0.2, 0.2};
        const mass<fod4> m(ma);
        BOOST_CHECK((m.has_internal_conflict()));
    }
    {
        const mass<fod4>::container_type ma = {0, 0, 0, 0, 0.3, 0.3, 0.2, 0.2};
        const mass<fod4> m(ma);
        BOOST_CHECK((!m.has_internal_conflict()));
    }
}

BOOST_AUTO_TEST_SUITE_END()
