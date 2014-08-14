//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BELIEF_TO_IMPLICABILITY_HPP
#define BOOST_BELIEF_TO_IMPLICABILITY_HPP

#include <boost/belief/implicability.hpp>
#include <boost/belief/mass.hpp>

namespace boost { namespace belief {

template <class FOD, typename T>
implicability<FOD, T> to_implicability(const mass<FOD, T> & m)
{
    implicability<FOD, T> b(m);

    for(std::size_t set = 0; set < FOD::set_size; ++set) { // for all sets in frame of discernement (FOD)
        std::size_t powerset = static_cast<std::size_t>(1 << set); // 2^set // set index in powerset 2^FOD
        for(std::size_t A = 0; A < FOD::powerset_size; ++A) { // for all subsets in powerset 2^FOD
            if(is_subset_of(powerset, A)) {
                std::size_t B = set_minus(A, powerset);
                b[A] += b[B];
            }
        }
    }
    return b;
}

} // namespace belief

} // namespace boost

#endif // BOOST_BELIEF_TO_IMPLICABILITY_HPP
