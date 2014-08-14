//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BELIEF_TO_COMMUNALITY_HPP
#define BOOST_BELIEF_TO_COMMUNALITY_HPP

#include <boost/belief/communality.hpp>
#include <boost/belief/mass.hpp>

namespace boost { namespace belief {

template <class FOD, typename T>
communality<FOD, T> to_communality(const mass<FOD, T> & m)
{
    communality<FOD, T> q(m);

    for(std::size_t set = 0; set < FOD::set_size; ++set) { // for all sets in frame of discernement (FOD)
        std::size_t powerset = static_cast<std::size_t>(1 << set); // 2^set // set index in powerset 2^FOD
        for(std::size_t A = 0; A < FOD::powerset_size; ++A) { // for all subsets in powerset 2^FOD
            if(is_subset_of(powerset, A)) {
                std::size_t B = set_minus(A, powerset);
                q[B] += q[A];
            }
        }
    }
    return q;
}

} // namespace belief

} // namespace boost

#endif // BOOST_BELIEF_TO_COMMUNALITY_HPP
