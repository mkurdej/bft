//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BELIEFS_TO_COMMUNALITY_HPP
#define BOOST_BELIEFS_TO_COMMUNALITY_HPP

#include <boost/beliefs/communality.hpp>
#include <boost/beliefs/mass.hpp>

namespace boost { namespace beliefs {

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

} // namespace beliefs

} // namespace boost

#endif // BOOST_BELIEFS_TO_COMMUNALITY_HPP
