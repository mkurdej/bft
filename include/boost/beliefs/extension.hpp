//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BELIEFS_EXTENSION_HPP
#define BOOST_BELIEFS_EXTENSION_HPP

#include <boost/beliefs/fod_union.hpp>
#include <boost/beliefs/mass.hpp>

namespace boost { namespace beliefs {

/// Vacuous extension of a mass function.
template <typename FOD2, typename FOD1, typename T>
mass<typename fod_union<FOD1, FOD2>::type, T> extension(const mass<FOD1, T> & m)
{
    typedef typename fod_union<FOD1, FOD2>::type FOD_UNION;
    mass<FOD_UNION, T> m_extended;

    // FIXME: works only when FOD_UNION is equivalent to *FOD1.append(FOD2)*
    std::size_t fod_diff = set_minus(FOD_UNION::powerset_size - 1, FOD1::powerset_size - 1);
    for(std::size_t A = 0; A < FOD1::powerset_size; ++A) {
        std::size_t B = A | fod_diff;
        m_extended[B] = m[A];
    }

    return m_extended;
}

} // namespace beliefs

} // namespace boost

#endif // BOOST_BELIEFS_EXTENSION_HPP
