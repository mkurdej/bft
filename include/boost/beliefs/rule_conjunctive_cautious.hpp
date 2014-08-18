//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BELIEFS_RULE_CONJUNCTIVE_CAUTIOUS_HPP
#define BOOST_BELIEFS_RULE_CONJUNCTIVE_CAUTIOUS_HPP

#include <boost/beliefs/conjunctive_decomposition.hpp>
#include <boost/beliefs/mass.hpp>
#include <boost/beliefs/min.hpp>
#include <boost/beliefs/rule_base.hpp>
#include <boost/beliefs/rule_conjunctive.hpp>
#include <boost/test/floating_point_comparison.hpp>

namespace boost { namespace beliefs {

struct rule_conjunctive_cautious
        : public rule_base
{
    std::string to_string() const
    {
        return "cautious conjunctive rule";
    }
    
    template <class FOD, typename T>
    mass<FOD, T> operator()(const mass<FOD, T> & m1, const mass<FOD, T> & m2) const
    {
        // compute canonical conjunctive decompositions w_1(A), w_2(A)
        conjunctive_decomposition decomposition;
        const dst_function<FOD, T> w1 = m1.apply(decomposition);
        const dst_function<FOD, T> w2 = m2.apply(decomposition);

        // find minimum weight decomposition w_1(A) \wedge w_2(A)
        dst_function<FOD, T> w_min12 = min(w1, w2);

        // compute conjunctive combination of GSBBA A^{w_1(A) \wedge w_2(A)}
        mass<FOD, T> m_result(vacuous);
        rule_conjunctive rule;
        for(std::size_t A = 0; A < FOD::powerset_size - 1; ++A) {
            if(boost::math::fpc::is_small(1 - w_min12[A], aux::tolerance)) {
                continue;
            }
            m_result = m_result.apply(rule, mass<FOD, T>::create_mass_from_conjunctive_weight(A, w_min12[A]));
        }
        return m_result;
    }
};

} // namespace beliefs

} // namespace boost

#endif // BOOST_BELIEFS_RULE_CONJUNCTIVE_CAUTIOUS_HPP
