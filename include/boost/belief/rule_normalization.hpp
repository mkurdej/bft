//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DST_RULE_NORMALIZATION_HPP
#define BOOST_DST_RULE_NORMALIZATION_HPP

#include <boost/dst/mass.hpp>
#include <boost/dst/rule_base.hpp>
#include <boost/dst/total_conflict_exception.hpp>
#include <boost/throw_exception.hpp>
#include <boost/foreach.hpp>

namespace boost { namespace dst {

// what behaviour should have rule_normalization when mass<EmptySet>() == 1.0 (total conflict)?
// throw an exception boost::dst::total_conflict_exception

struct rule_normalization
        : public rule_base
{
    std::string to_string() const
    {
        return "normalization rule";
    }

    template <class FOD, typename T>
    void operator()(mass<FOD, T> & m) const
    {
        if (m.is_degenerate()) {
            BOOST_THROW_EXCEPTION(boost::dst::total_conflict_exception());
            // TODO: append mass function information to the exception?
        }

        T conflict_mass = m[0];
        BOOST_FOREACH(T & v, m.values()) {
            v = v / (1-conflict_mass);
        }
        m.values().front() = 0;
    }

    template <class FOD, typename T>
    mass<FOD, T> operator()(const mass<FOD, T> & m) const
    {
        mass<FOD, T> m_out(m);
        operator()(m_out);
        return m_out;
    }
};

} // namespace dst

} // namespace boost

#endif // BOOST_DST_RULE_NORMALIZATION_HPP
