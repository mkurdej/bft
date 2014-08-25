//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BFT_RULE_PCR5_HPP
#define BOOST_BFT_RULE_PCR5_HPP

#include <boost/assert.hpp>
#include <boost/bft/mass.hpp>
#include <boost/bft/rule_base.hpp>

namespace boost { namespace bft {

/// Proportional Conflict Redistribution Rule no. 5
struct rule_pcr5
        : public rule_base
{
    std::string to_string() const
    {
        return "Proportional Conflict Redistribution Rule no. 5";
    }


    template <class FOD, typename T>
    mass<FOD, T> operator()(const mass<FOD, T> & m1, const mass<FOD, T> & m2) const
    {
        mass<FOD, T> m_result;

        for(std::size_t B = 0; B < FOD::powerset_size; ++B) {
            if(m1[B] < detail::tolerance) {
                continue;
            }
            for(std::size_t C = 0; C < FOD::powerset_size; ++C) {
                if(m2[C] < detail::tolerance) {
                    continue;
                }
                std::size_t A = set_intersection(B, C);
                if(is_emptyset(A)) {
                    // redistribute conflicting mass to m[B] and m[C] proportionally to m1[B], m2[C]
                    T proportion_denominator = m1[B] + m2[C];
                    BOOST_ASSERT_MSG( (proportion_denominator > detail::tolerance), "denominator is close to zero!");
                    T conflict_mass = m1[B] * m2[C];
                    m_result[B] += conflict_mass * (m1[B] / proportion_denominator);
                    m_result[C] += conflict_mass * (m2[C] / proportion_denominator);
                } else {
                    // conjunctive
                    m_result[A] += m1[B] * m2[C];
                }
            }
        }
        return m_result;
    }
};

} // namespace bft

} // namespace boost

#endif // BOOST_BFT_RULE_PCR5_HPP
