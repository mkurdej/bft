//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BELIEF_DISJUNCTIVE_DECOMPOSITION_HPP
#define BOOST_BELIEF_DISJUNCTIVE_DECOMPOSITION_HPP

#include <boost/assert.hpp>
#include <boost/belief/implicability.hpp>
#include <boost/belief/mass.hpp>
#include <boost/belief/to_implicability.hpp>
#include <boost/limits.hpp>

namespace boost { namespace belief {

struct disjunctive_decomposition
{
    typedef std::size_t size_type;

    // =============================================================================
    template <class FOD, typename T>
    /*dst_function*/mass<FOD, T> operator()(const mass<FOD, T> & m) const
    {
        implicability<FOD, T> b = to_implicability(m);
        return mass<FOD, T>(operator()(b));
    }

    template <class FOD, typename T>
    /*dst_function*/implicability<FOD, T> operator()(const implicability<FOD, T> & b) const
    {
        BOOST_ASSERT_MSG(b.is_subnormal(), "mass function should be subnormal to be decomposed!");
        dst_function<FOD, T> v;
        v.values().assign(1);
        v.values().front() = std::numeric_limits<T>::quiet_NaN();

        for(size_type A = 1; A < FOD::powerset_size; ++A) {
            size_type element_count_A = count_elements(A);
            for(size_type B = 0; B <= A; ++B) {
                if(is_subset_of(B, A)) {
                    size_type element_count_B = count_elements(B);
                    long exponent = ((element_count_A - element_count_B + 1) % 2 == 0) ? 1 /*even*/ : -1 /*odd*/;
                    v[A] *= std::pow(b[B], exponent);
                }
            }
        }
        return implicability<FOD, T>(v);
    }

    /*
        function [ v ] = weightDisjunctive(m)
            w = MassFunction.weightConjunctive(m(end:-1:1));
            v = w(end:-1:1);
        end
        */

};

} // namespace belief

} // namespace boost

#endif // BOOST_BELIEF_DISJUNCTIVE_DECOMPOSITION_HPP
