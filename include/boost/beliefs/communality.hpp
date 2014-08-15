//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BELIEFS_COMMUNALITY_HPP
#define BOOST_BELIEFS_COMMUNALITY_HPP

#include <boost/beliefs/dst_function.hpp>
#include <boost/beliefs/fod.hpp>
#include <boost/test/floating_point_comparison.hpp>

namespace boost { namespace beliefs {

template <class FOD, typename T = double>
class communality : public dst_function<FOD, T>
{
public:
    typedef communality<FOD, T> this_type;
    typedef typename dst_function<FOD, T>::container_type container_type;

    /// Default constructor.
    communality()
    {
    }

    /// It creates a communality function equivalent to a mass function where all mass is attributed to the Conflict set (Emptyset).
    /// I.e. value for Conflict (Emptyset) equals 1 and for other sets equals 0.
    communality(degenerate_t)
    {
        this->m_values.front() = 1;
    }

    /// It creates a communality function equivalent to a mass function where all mass is attributed to the Unknown set (Omega).
    /// I.e. all values equal 1.
    communality(vacuous_t)
    {
        this->m_values.assign(1);
    }

    explicit communality(const dst_function<FOD, T> & f)
        : dst_function<FOD, T>(f)
    {
    }

    communality(const container_type & init_values)
        : dst_function<FOD, T>(init_values)
    {
    }

    ~communality()
    {
    }

    /// Non-dogmatic mass function has some mass at Unknown.
    bool is_nondogmatic() const
    {
        return ! test_tools::check_is_small(this->m_values.back(), aux::tolerance);
    }
};

} // namespace beliefs

} // namespace boost

#endif // BOOST_BELIEFS_COMMUNALITY_HPP
