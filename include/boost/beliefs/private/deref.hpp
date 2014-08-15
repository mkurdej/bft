//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BELIEFS_PRIVATE_DEREF_HPP
#define BOOST_BELIEFS_PRIVATE_DEREF_HPP

#include <boost/beliefs/private/to_void.hpp>
#include <boost/mpl/deref.hpp>

namespace boost { namespace beliefs { namespace aux {

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

} // namespace aux

} // namespace beliefs

} // namespace boost

#endif // BOOST_BELIEFS_PRIVATE_DEREF_HPP
