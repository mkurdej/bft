//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BFT_RULE_YAGER_HPP
#define BOOST_BFT_RULE_YAGER_HPP

#include <boost/bft/mass.hpp>
#include <boost/bft/rule_base.hpp>
#include <boost/bft/rule_conjunctive.hpp>

namespace boost
{
namespace bft
{

struct rule_yager : public rule_base
{
    std::string to_string() const
    {
        return "Yager rule";
    }

    template <class FOD, typename T>
    mass<FOD, T>
    operator()(const mass<FOD, T>& m1, const mass<FOD, T>& m2) const
    {
        mass<FOD> m_result = m1.apply(rule_conjunctive(), m2);
        m_result.values().back() =
            m_result.values().back() + m_result.values().front(); // Unknown
        m_result.values().front() = 0;                            // Emptyset
        return m_result;
    }
};

} // namespace bft

} // namespace boost

#endif // BOOST_BFT_RULE_YAGER_HPP
