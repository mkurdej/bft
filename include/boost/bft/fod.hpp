//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BFT_FOD_HPP
#define BOOST_BFT_FOD_HPP

#include <boost/bft/boost_bft_define_class.hpp>
#include <boost/bft/private/emptytype.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/type_traits/is_same.hpp>

#ifdef _MSC_VER
#   pragma warning(push)	// disable for these headers only
#   pragma warning(disable:4668)
#endif // _MSC_VER

#include <boost/mpl/erase_key.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/vector.hpp>

#ifdef _MSC_VER
#   pragma warning(pop)  	// restore original warning level
#endif // _MSC_VER

namespace boost { namespace bft {

// definition of fod class
template <class S0 = detail::EmptyType, class S1 = detail::EmptyType, class S2 = detail::EmptyType, class S3 = detail::EmptyType, class S4 = detail::EmptyType, class S5 = detail::EmptyType, class S6 = detail::EmptyType, class S7 = detail::EmptyType, class S8 = detail::EmptyType, class S9 = detail::EmptyType>
class fod
{
    typedef mpl::vector<S0, S1, S2, S3, S4, S5, S6, S7, S8, S9> template_types;
    /// set of classes, constructed from a list of potentially non-unique types, can contain EmptyType
    typedef typename mpl::fold<template_types, mpl::set0<>, mpl::insert<mpl::_1, mpl::_2> >::type types_with_empty_type;

public:
    typedef fod<S0, S1, S2, S3, S4, S5, S6, S7, S8, S9> this_type;

    /// set of classes, constructed from a list of potentially non-unique types
    typedef typename mpl::erase_key<types_with_empty_type, detail::EmptyType>::type type;

    /// cardinality of the frame of discernment
    BOOST_STATIC_CONSTANT(std::size_t, set_size = mpl::size<type>::value);
    /// cardinality of the powerset of the frame of discernment
    BOOST_STATIC_CONSTANT(std::size_t, powerset_size = 1 << set_size);

    template <typename T, typename Dummy = void>
    struct Idx
    {
        enum {
            value
            = is_same<T, S0>::value * 0
            + is_same<T, S1>::value * 1
            + is_same<T, S2>::value * 2
            + is_same<T, S3>::value * 3
            + is_same<T, S4>::value * 4
            + is_same<T, S5>::value * 5
            + is_same<T, S6>::value * 6
            + is_same<T, S7>::value * 7
            + is_same<T, S8>::value * 8
            + is_same<T, S9>::value * 9
        };

    private:
        typedef ::boost::mpl::has_key<types_with_empty_type, T> has_key;
        BOOST_MPL_ASSERT(
            ( has_key )
            );
    };

    template <typename Dummy>
    struct Idx< ::boost::bft::detail::EmptyType, Dummy >
    {
        BOOST_STATIC_CONSTANT(int, value = 0);
    };

    template <typename T>
    static int idx()
    {
        return Idx<T>::value;
    }

};

// allow user to configure the floating-point tolerance
#ifndef BOOST_BFT_FP_TOLERANCE
# define BOOST_BFT_FP_TOLERANCE 1e-10
#endif
namespace detail {
namespace /* anonymous */ {
double tolerance = BOOST_BFT_FP_TOLERANCE;

template <typename T> void quiet_warning()
{
    (void) tolerance;
}

} // namespace
} // namespace detail

} // namespace bft

} // namespace boost

#endif // BOOST_BFT_FOD_HPP
