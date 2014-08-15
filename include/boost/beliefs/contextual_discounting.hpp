//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BELIEFS_CONTEXTUAL_DISCOUNTING_HPP
#define BOOST_BELIEFS_CONTEXTUAL_DISCOUNTING_HPP

#include <boost/foreach.hpp>
#include <boost/beliefs/mass.hpp>
#include <boost/beliefs/rule_disjunctive.hpp>

namespace boost { namespace beliefs {

/// Performs \alpha-discounting, i.e. non-Omega masses are discounted by the factor 1-\alpha.
///
/// \alpha-discounting gives: // FIXME
/// {}^\alpha m(A) = (1-\alpha) m(A)         , \forall A \subset Omega
/// {}^\alpha m(\Omega) = (1-\alpha) m(\Omega) + \alpha
template <typename FOD, typename T = double>
struct contextual_discounting
{
    typedef T value_type;
    typedef T container_type[FOD::powerset_size];

    // =============================================================================
    contextual_discounting(const container_type & alphas)
        : m_discount(degenerate)
    {
        for(std::size_t A = 0; A < FOD::powerset_size; ++A) {
            T alpha = alphas[A];
            if(test_tools::check_is_small(alpha, aux::tolerance)) {
                continue;
            }

            BOOST_ASSERT(alpha >= 0);
            BOOST_ASSERT(alpha <= 1);

            mass<FOD, T> m_a;
            m_a[0] = 1 - alpha;
            m_a[A] = alpha;

            this->m_discount = this->m_discount.apply(rule_disjunctive(), m_a);
        }
    }

    // =============================================================================
    void operator()(mass<FOD, T> & m) const
    {
        m = m.apply(rule_disjunctive(), this->m_discount);
    }

    // =============================================================================
    mass<FOD, T> operator()(const mass<FOD, T> & m) const
    {
        mass<FOD, T> m_out(m);
        operator()(m_out);
        return m_out;
    }

private:
    mass<FOD, T> m_discount;
};

} // namespace beliefs

} // namespace boost

#endif // BOOST_BELIEFS_CONTEXTUAL_DISCOUNTING_HPP
