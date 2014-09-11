// Copyright (c) 2011-2014
// Marek Kurdej
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_BFT_DETAIL_TO_VOID_HPP
#define BOOST_BFT_DETAIL_TO_VOID_HPP

namespace boost
{
namespace bft
{
namespace detail
{

template <typename T>
struct to_void
{
    typedef void type;
};

} // namespace detail

} // namespace bft

} // namespace boost

#endif // BOOST_BFT_DETAIL_TO_VOID_HPP
