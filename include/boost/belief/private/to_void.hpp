//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BELIEF_PRIVATE_TO_VOID_HPP
#define BOOST_BELIEF_PRIVATE_TO_VOID_HPP

namespace boost { namespace belief { namespace aux {

template<typename T>
struct to_void
{
    typedef void type;
};

} // namespace aux

} // namespace belief

} // namespace boost

#endif // BOOST_BELIEF_PRIVATE_TO_VOID_HPP
