//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BELIEFS_RULE_JEFFREY_DEMPSTER_HPP
#define BOOST_BELIEFS_RULE_JEFFREY_DEMPSTER_HPP

#include <boost/beliefs/mass.hpp>
#include <boost/beliefs/plausibility.hpp>
#include <boost/beliefs/to_plausibility.hpp>
#include <boost/beliefs/rule_base.hpp>

namespace boost { namespace beliefs {

// @see @article{Ma_Liu_Dubois_Prade_2011, title={Bridging Jeffrey's rule, AGM revision and Dempster conditioning in the theory of evidence}, journal={International Journal of Artificial Intelligence Tools}, author={Ma, Jianbing and Liu, Weiru and Dubois, Didier and Prade, Henri}, year={2011}, pages={1-29}}
struct rule_jeffrey_dempster
        : public rule_base
{
    std::string to_string() const
    {
        return "Jeffrey-Dempster revision rule";
    }

    /// @param m_prior	Prior mass.
    /// @param m_new	New evidence mass.
    template <class FOD, typename T>
    mass<FOD, T> operator()(const mass<FOD, T> & m_prior, const mass<FOD, T> & m_new) const
    {
        mass<FOD, T> m_result;
        plausibility<FOD, T> pl_prior = to_plausibility(m_prior);

        for (std::size_t B = 0; B < FOD::powerset_size; ++B) {
            for (std::size_t C = 0; C < FOD::powerset_size; ++C) {
                std::size_t A = set_intersection(B, C);

                T sigma_prior;
                if (boost::math::fpc::is_small(pl_prior[C], aux::tolerance)) {
                    sigma_prior = (B == C);
                } else {
                    sigma_prior = m_prior[B] / pl_prior[C];
                }
                m_result[A] += sigma_prior * m_new[C];
            }
        }
        m_result[0] = 0;
        return m_result;
    }
};

} // namespace beliefs

} // namespace boost

#endif // BOOST_BELIEFS_RULE_JEFFREY_DEMPSTER_HPP
