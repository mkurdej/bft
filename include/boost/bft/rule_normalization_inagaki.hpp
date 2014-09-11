// Copyright (c) 2011-2014
// Marek Kurdej
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_BFT_RULE_NORMALIZATION_INAGAKI_HPP
#define BOOST_BFT_RULE_NORMALIZATION_INAGAKI_HPP

#include <boost/bft/mass.hpp>
#include <boost/bft/rule_base.hpp>
#include <boost/foreach.hpp>

namespace boost
{
namespace bft
{

struct rule_normalization_inagaki : public rule_base
{
    std::string to_string() const
    {
        return "Inagaki normalization rule";
    }

    typedef double value_type;

    rule_normalization_inagaki(value_type k)
        : m_k(k)
    {
        BOOST_ASSERT(this->m_k >= 0);
    }

    template <class FOD, typename T>
    void operator()(mass<FOD, T>& m) const
    {
        T conflict_mass = m.values().front();
        T unknown_mass = m.values().back();
        BOOST_VERIFY(this->m_k <= 1 / (1 - conflict_mass - unknown_mass -
                                       detail::tolerance));
        BOOST_FOREACH (T& v, m.values()) {
            v *= 1 + this->m_k * conflict_mass;
        }
        m.values().front() = 0;
        m.values().back() +=
            (1 + this->m_k * conflict_mass - this->m_k) * conflict_mass;
    }

    template <class FOD, typename T>
    mass<FOD, T> operator()(const mass<FOD, T>& m) const
    {
        mass<FOD, T> m_out(m);
        operator()(m_out);
        return m_out;
    }

private:
    value_type m_k;
};

} // namespace bft

} // namespace boost

#endif // BOOST_BFT_RULE_NORMALIZATION_INAGAKI_HPP
