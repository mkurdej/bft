//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BFT_DETAIL_IS_SMALL_HPP
#define BOOST_BFT_DETAIL_IS_SMALL_HPP

#include <boost/version.hpp>
#include <boost/test/floating_point_comparison.hpp>

namespace boost { namespace bft { namespace detail {

template<typename FPT>
inline bool
is_small( FPT fpv, FPT tolerance )
{
#if BOOST_VERSION >= 105700
    return math::fpc::is_small( fpv, tolerance );
#else
    return test_tools::check_is_small( fpv, tolerance );
#endif
}

} // namespace detail

} // namespace bft

} // namespace boost

#endif // BOOST_BFT_DETAIL_IS_SMALL_HPP
