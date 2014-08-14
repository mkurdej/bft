//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BELIEF_RULE_DUBOIS_PRADE_HPP
#define BOOST_BELIEF_RULE_DUBOIS_PRADE_HPP

#include <boost/belief/mass.hpp>
#include <boost/belief/rule_base.hpp>

namespace boost { namespace belief {

struct rule_dubois_prade
        : public rule_base
{
    std::string to_string() const
    {
        return "Dubois-Prade adaptative rule";
    }

    template <class FOD, typename T>
    mass<FOD, T> operator()(const mass<FOD, T> & m1, const mass<FOD, T> & m2) const
    {
        mass<FOD, T> m_result;

        for(std::size_t B = 0; B < FOD::powerset_size; ++B) {
            for(std::size_t C = 0; C < FOD::powerset_size; ++C) {
                std::size_t A = set_intersection(B, C);
                if(is_emptyset(A)) {
                    A = set_union(B, C);
                }
                m_result[A] += m1[B] * m2[C];
            }
        }
        return m_result;
    }
};

} // namespace belief

} // namespace boost

#endif // BOOST_BELIEF_RULE_DUBOIS_PRADE_HPP
