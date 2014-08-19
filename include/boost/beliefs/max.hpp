//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BELIEFS_MAX_HPP
#define BOOST_BELIEFS_MAX_HPP

#include <boost/beliefs/dst_function.hpp>
#include <boost/math/tr1.hpp> // BOOST_PREVENT_MACRO_SUBSTITUTION

namespace boost { namespace beliefs {

template <class FOD, typename T>
dst_function<FOD, T> (max) BOOST_PREVENT_MACRO_SUBSTITUTION (const dst_function<FOD, T> & f1, const dst_function<FOD, T> & f2)
{
    dst_function<FOD, T> f_result;
    for(int A = 0; A < FOD::powerset_size; ++A) {
        f_result[A] = std::max(f1[A], f2[A]);
    }
    return f_result;
}

} // namespace beliefs

} // namespace boost

#endif // BOOST_BELIEFS_MAX_HPP
