//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BELIEFS_RULE_CONJUNCTIVE_HPP
#define BOOST_BELIEFS_RULE_CONJUNCTIVE_HPP

#include <boost/beliefs/communality.hpp>
#include <boost/beliefs/mass.hpp>
#include <boost/beliefs/rule_base.hpp>
#include <boost/beliefs/to_communality.hpp>
#include <boost/beliefs/to_mass.hpp>

namespace boost { namespace beliefs {

struct rule_conjunctive
        : public rule_base
{
    std::string to_string() const
    {
        return "conjunctive rule";
    }

    template <class FOD, typename T>
    communality<FOD, T> operator()(communality<FOD, T> const& q1, communality<FOD, T> const& q2) const
    {
        communality<FOD, T> q12;
        for (std::size_t i = 0; i < FOD::powerset_size; ++i) {
            q12[i] = q1[i] * q2[i];
        }
        return q12;
    }

    template <class FOD, typename T>
    mass<FOD, T> operator()(mass<FOD, T> const& m1, mass<FOD, T> const& m2) const
    {
        communality<FOD, T> q1 = to_communality(m1);
        communality<FOD, T> q2 = to_communality(m2);
        communality<FOD, T> q12 = operator()(q1, q2);
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

} // namespace beliefs

} // namespace boost

#endif // BOOST_BELIEFS_RULE_CONJUNCTIVE_HPP
