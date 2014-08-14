//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BELIEF_CONJUNCTIVE_DECOMPOSITION_HPP
#define BOOST_BELIEF_CONJUNCTIVE_DECOMPOSITION_HPP

#include <boost/assert.hpp>
#include <boost/belief/communality.hpp>
#include <boost/belief/mass.hpp>
#include <boost/belief/to_communality.hpp>
#include <boost/limits.hpp>
#include <cmath>

namespace boost { namespace belief {

struct conjunctive_decomposition
{
    typedef std::size_t size_type;

    template <class FOD, typename T>
    /*dst_function*/mass<FOD, T> operator()(const mass<FOD, T> & m) const
    {
        communality<FOD, T> q = to_communality(m);
        return mass<FOD, T>(operator()(q));
    }

    template <class FOD, typename T>
    /*dst_function*/communality<FOD, T> operator()(const communality<FOD, T> & q) const
    {
        BOOST_ASSERT_MSG(q.is_nondogmatic(), "mass function should be non-dogmatic to be decomposed!");
        communality<FOD, T> w;
        w.values().assign(1);
        w.values().back() = std::numeric_limits<T>::quiet_NaN();

        for(size_type A = 0; A < FOD::powerset_size - 1; ++A) {
            size_type element_count_A = count_elements(A);
            for(size_type B = A; B < FOD::powerset_size; ++B) {
                if(is_superset_of(B, A)) {
                    size_type element_count_B = count_elements(B);
                    long exponent = ((element_count_B - element_count_A + 1) % 2 == 0) ? 1 /*even*/ : -1 /*odd*/;
                    w[A] *= std::pow(q[B], exponent);
                }
            }
        }
        return w;
    }
};

} // namespace belief

} // namespace boost

#endif // BOOST_BELIEF_CONJUNCTIVE_DECOMPOSITION_HPP
