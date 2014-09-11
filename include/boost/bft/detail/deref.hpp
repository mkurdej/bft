// Copyright (c) 2011-2014
// Marek Kurdej
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_BFT_DETAIL_DEREF_HPP
#define BOOST_BFT_DETAIL_DEREF_HPP

#include <boost/bft/detail/emptytype.hpp>
#include <boost/bft/detail/to_void.hpp>
#include <boost/mpl/deref.hpp>

namespace boost
{
namespace bft
{
namespace detail
{

template <class T, class U = EmptyType, class Enable = void>
struct deref
{
    typedef EmptyType type;
};

template <class T, class U>
struct deref<T, U, typename to_void<typename T::type>::type>
{
    typedef typename mpl::deref<T>::type type;
};

} // namespace detail

} // namespace bft

} // namespace boost

#endif // BOOST_BFT_DETAIL_DEREF_HPP
