//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BELIEFS_COMMONALITY_HPP
#define BOOST_BELIEFS_COMMONALITY_HPP

#include <boost/beliefs/dst_function.hpp>
#include <boost/beliefs/fod.hpp>
#include <boost/test/floating_point_comparison.hpp>

namespace boost { namespace beliefs {

template <class FOD, typename T = double>
class commonality : public dst_function<FOD, T>
{
public:
    typedef commonality<FOD, T> this_type;
    typedef typename dst_function<FOD, T>::container_type container_type;

    /// Default constructor.
    commonality()
    {
    }

    /// It creates a commonality function equivalent to a mass function where all mass is attributed to the Conflict set (Emptyset).
    /// I.e. value for Conflict (Emptyset) equals 1 and for other sets equals 0.
    commonality(degenerate_t)
    {
        this->m_values.front() = 1;
    }

    /// It creates a commonality function equivalent to a mass function where all mass is attributed to the Unknown set (Omega).
    /// I.e. all values equal 1.
    commonality(vacuous_t)
    {
        this->m_values.assign(1);
    }

    explicit commonality(const dst_function<FOD, T> & f)
        : dst_function<FOD, T>(f)
    {
    }

    commonality(const container_type & init_values)
        : dst_function<FOD, T>(init_values)
    {
    }

    ~commonality()
    {
    }

    /// Non-dogmatic mass function has some mass at Unknown.
    bool is_nondogmatic() const
    {
        return ! boost::math::fpc::is_small(this->m_values.back(), aux::tolerance);
    }
};

} // namespace beliefs

} // namespace boost

#endif // BOOST_BELIEFS_COMMONALITY_HPP
