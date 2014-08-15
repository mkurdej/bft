//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BELIEFS_PRIVATE_TO_VOID_HPP
#define BOOST_BELIEFS_PRIVATE_TO_VOID_HPP

namespace boost { namespace beliefs { namespace aux {

template<typename T>
struct to_void
{
    typedef void type;
};

} // namespace aux

} // namespace beliefs

} // namespace boost

#endif // BOOST_BELIEFS_PRIVATE_TO_VOID_HPP
