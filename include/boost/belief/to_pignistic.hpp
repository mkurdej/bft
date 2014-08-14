//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DST_TO_PIGNISTIC_HPP
#define BOOST_DST_TO_PIGNISTIC_HPP

#include <boost/assert.hpp>
#include <boost/dst/dst_function.hpp>
#include <boost/dst/mass.hpp>

namespace boost { namespace dst {

template <class FOD, typename T>
dst_function<FOD, T> to_pignistic(const mass<FOD, T> & m)
{
    BOOST_ASSERT_MSG(! m.is_degenerate(), "mass function cannot be degenerate!");
    dst_function<FOD, T> betP;

    T conflict_normalization_factor = 1. / (1 - m[0]);
    for(std::size_t Y = 1; Y < FOD::powerset_size; ++Y) {
        std::size_t element_count_Y = count_elements(Y);
        for(std::size_t X = 1; X < FOD::powerset_size; ++X) {
            std::size_t element_count_XinterY = count_elements(set_intersection(X, Y));
            T proportion = 1.0 * static_cast<T>(element_count_XinterY) / static_cast<T>(element_count_Y);
            betP[X] += proportion * m[Y] * conflict_normalization_factor;
        }
    }
    return betP;
}

} // namespace dst

} // namespace boost

#endif // BOOST_DST_TO_PIGNISTIC_HPP
