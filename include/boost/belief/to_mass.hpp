//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BELIEF_TO_MASS_HPP
#define BOOST_BELIEF_TO_MASS_HPP

#include <boost/belief/belief.hpp>
#include <boost/belief/communality.hpp>
#include <boost/belief/implicability.hpp>
#include <boost/belief/mass.hpp>
#include <boost/belief/plausibility.hpp>

namespace boost { namespace belief {

template <class FOD, typename T>
mass<FOD, T> to_mass(const belief<FOD, T> & bel)
{
    implicability<FOD, T> b(bel);
    T conflict_mass = 1 - b.values().back();

    for(std::size_t A = 0; A < FOD::powerset_size; ++A) { // for all subsets in powerset 2^FOD
        // add conflict mass to all values
        b[A] = b[A] + conflict_mass;
    }

    mass<FOD, T> m = to_mass(b);
    return m;
}

template <class FOD, typename T>
mass<FOD, T> to_mass(const communality<FOD, T> & q)
{
    mass<FOD, T> m(q);

    for(std::size_t set = 0; set < FOD::set_size; ++set) { // for all sets in frame of discernement (FOD)
        std::size_t powerset = static_cast<std::size_t>(1 << set); // 2^set // set index in powerset 2^FOD
        for(std::size_t A = 0; A < FOD::powerset_size; ++A) { // for all subsets in powerset 2^FOD
            if(is_subset_of(powerset, A)) {
                std::size_t B = set_minus(A, powerset);
                m[B] -= m[A];
            }
        }
    }
    return m;
}

template <class FOD, typename T>
mass<FOD, T> to_mass(const implicability<FOD, T> & b)
{
    mass<FOD, T> m(b);

    // for all sets in frame of discernement (FOD)
    for(std::size_t set = 0; set < FOD::set_size; ++set) {
        // set index in powerset 2^FOD
        std::size_t setIdx = static_cast<std::size_t>(1 << set); // 2^set
        // for all subsets in powerset 2^FOD
        for(std::size_t A = 0; A < FOD::powerset_size; ++A) {
            // is 'set' a subset of 'A'?
            if((setIdx & A) == setIdx) { // AND = intersection
                // 'B' is ('A' without 'set')
                std::size_t B = A ^ setIdx; // XOR = set theory minus operation
                m[A] -= m[B];
            }
        }
    }
    return m;
}

template <class FOD, typename T>
mass<FOD, T> to_mass(const plausibility<FOD, T> & pl)
{
    belief<FOD, T> bel = to_belief(pl);
    mass<FOD, T> m = to_mass(bel);
    return m;
}

} // namespace belief

} // namespace boost

#endif // BOOST_BELIEF_TO_MASS_HPP
