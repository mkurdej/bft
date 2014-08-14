//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DST_PRIVATE_TO_VOID_HPP
#define BOOST_DST_PRIVATE_TO_VOID_HPP

namespace boost { namespace dst { namespace aux {

template<typename T>
struct to_void
{
    typedef void type;
};

} // namespace aux

} // namespace dst

} // namespace boost

#endif // BOOST_DST_PRIVATE_TO_VOID_HPP
