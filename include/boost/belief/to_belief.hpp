//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DST_TO_BELIEF_HPP
#define BOOST_DST_TO_BELIEF_HPP

#include <boost/dst/belief.hpp>
#include <boost/dst/plausibility.hpp>
#include <boost/dst/mass.hpp>
#include <boost/dst/to_implicability.hpp>
#include <boost/foreach.hpp>

namespace boost { namespace dst {

template <class FOD, typename T>
belief<FOD, T> to_belief(const mass<FOD, T> & m)
{
    mass<FOD, T> m_without_conflict(m);
    m_without_conflict[0] = 0; // set 0 to conflict mass
    belief<FOD, T> bel(to_implicability(m_without_conflict));
    return bel;
}

template <class FOD, typename T>
belief<FOD, T> to_belief(const plausibility<FOD, T> & pl)
{
    belief<FOD, T> bel(pl);
    std::reverse(bel.values().begin(), bel.values().end());
    BOOST_FOREACH(T & v, bel.values()) {
        v = 1 - v;
    }
    return bel;
}

} // namespace dst

} // namespace boost

#endif // BOOST_DST_TO_BELIEF_HPP
