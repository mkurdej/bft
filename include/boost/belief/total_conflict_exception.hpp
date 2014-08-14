//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DST_TOTAL_CONFLICT_EXCEPTION_HPP
#define BOOST_DST_TOTAL_CONFLICT_EXCEPTION_HPP

#include <boost/exception/exception.hpp>

namespace boost { namespace dst {

struct total_conflict_exception
        : virtual boost::exception
        , virtual std::exception
{
};

} // namespace dst

} // namespace boost

#endif // BOOST_DST_TOTAL_CONFLICT_EXCEPTION_HPP
