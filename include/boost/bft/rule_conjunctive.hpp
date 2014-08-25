//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BFT_RULE_CONJUNCTIVE_HPP
#define BOOST_BFT_RULE_CONJUNCTIVE_HPP

#include <boost/bft/commonality.hpp>
#include <boost/bft/mass.hpp>
#include <boost/bft/rule_base.hpp>
#include <boost/bft/to_commonality.hpp>
#include <boost/bft/to_mass.hpp>

namespace boost { namespace bft {

struct rule_conjunctive
        : public rule_base
{
    std::string to_string() const
    {
        return "conjunctive rule";
    }

    template <class FOD, typename T>
    commonality<FOD, T> operator()(commonality<FOD, T> const& q1, commonality<FOD, T> const& q2) const
    {
        commonality<FOD, T> q12;
        for (std::size_t i = 0; i < FOD::powerset_size; ++i) {
            q12[i] = q1[i] * q2[i];
        }
        return q12;
    }

    template <class FOD, typename T>
    mass<FOD, T> operator()(mass<FOD, T> const& m1, mass<FOD, T> const& m2) const
    {
        commonality<FOD, T> q1 = to_commonality(m1);
        commonality<FOD, T> q2 = to_commonality(m2);
        commonality<FOD, T> q12 = operator()(q1, q2);
        return to_mass(q12);
    }

    // TODO: BOOST_STATIC_ASSERT_MSG(TODO, "FOD1 must be compatible with FOD2")
    // different fod classes can represent the same frame of discernment

    /*
    template <class FOD1, FOD2>
    mass<FOD3> operator()(mass<FOD1> const& m1, mass<FOD2> const& m2) const
    {
        return A < B;
    }
    */
};

} // namespace bft

} // namespace boost

#endif // BOOST_BFT_RULE_CONJUNCTIVE_HPP
