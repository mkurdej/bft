//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BFT_TO_PLAUSIBILITY_HPP
#define BOOST_BFT_TO_PLAUSIBILITY_HPP

#include <algorithm>
#include <boost/bft/belief.hpp>
#include <boost/bft/plausibility.hpp>
#include <boost/bft/mass.hpp>
#include <boost/bft/to_belief.hpp>
#include <boost/foreach.hpp>

namespace boost { namespace bft {

template <class FOD, typename T>
plausibility<FOD, T> to_plausibility(const belief<FOD, T> & bel)
{
    plausibility<FOD, T> pl(bel);
    std::reverse(pl.values().begin(), pl.values().end());
    T conflict_mass = 1 - pl[0];
    BOOST_FOREACH(T & v, pl.values()) {
        v = 1 - v - conflict_mass;
    }
    return pl;
}

template <class FOD, typename T>
plausibility<FOD, T> to_plausibility(const mass<FOD, T> & m)
{
    belief<FOD, T> bel = to_belief(m);
    plausibility<FOD, T> pl = to_plausibility(bel);
    return pl;
}

} // namespace bft

} // namespace boost

#endif // BOOST_BFT_TO_PLAUSIBILITY_HPP
