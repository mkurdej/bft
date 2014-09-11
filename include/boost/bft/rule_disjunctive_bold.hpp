// Copyright (c) 2011-2014
// Marek Kurdej
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_BFT_RULE_DISJUNCTIVE_BOLD_HPP
#define BOOST_BFT_RULE_DISJUNCTIVE_BOLD_HPP

#include <boost/bft/disjunctive_decomposition.hpp>
#include <boost/bft/mass.hpp>
#include <boost/bft/max.hpp>
#include <boost/bft/rule_base.hpp>
#include <boost/bft/rule_disjunctive.hpp>
#include <boost/bft/detail/is_small.hpp>

namespace boost
{
namespace bft
{

struct rule_disjunctive_bold : public rule_base
{
    std::string to_string() const
    {
        return "bold disjunctive rule";
    }

    template <class FOD, typename T>
    mass<FOD, T>
    operator()(const mass<FOD, T>& m1, const mass<FOD, T>& m2) const
    {
        // compute canonical disjunctive decompositions v_1(A), v_2(A)
        disjunctive_decomposition decomposition;
        const bft_function<FOD, T> v1 = m1.apply(decomposition);
        const bft_function<FOD, T> v2 = m2.apply(decomposition);

        // find minimum weight decomposition v_1(A) \vee v_2(A)
        bft_function<FOD, T> v_min12 = min(v1, v2);

        // compute disjunctive combination of GSBBA A^{v_1(A) \vee v_2(A)}
        mass<FOD, T> m_result(degenerate);
        rule_disjunctive rule;
        for (std::size_t A = 1; A < FOD::powerset_size; ++A) {
            if (detail::is_small(1 - v_min12[A], detail::tolerance)) {
                continue;
            }
            m_result = m_result.apply(
                rule, mass<FOD, T>::create_mass_from_disjunctive_weight(
                          A, v_min12[A]));
        }
        return m_result;
    }
};

} // namespace bft

} // namespace boost

#endif // BOOST_BFT_RULE_DISJUNCTIVE_BOLD_HPP
