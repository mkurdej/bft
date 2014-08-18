//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BELIEFS_IMPLICABILITY_HPP
#define BOOST_BELIEFS_IMPLICABILITY_HPP

#include <boost/beliefs/dst_function.hpp>
#include <boost/beliefs/fod.hpp>
#include <boost/test/floating_point_comparison.hpp>

namespace boost { namespace beliefs {

template <class FOD, typename T = double>
class implicability : public dst_function<FOD, T>
{
public:
    typedef implicability<FOD, T> this_type;
    typedef typename dst_function<FOD, T>::container_type container_type;

    /// Default constructor.
    implicability()
    {
    }

    /// It creates an implicability function equivalent to a mass function where all mass is attributed to the Conflict set (Emptyset).
    /// I.e. all values equal 1.
    implicability(degenerate_t)
    {
        this->m_values.assign(1);
    }

    /// It creates an implicability function equivalent to a mass function where all mass is attributed to the Unknown set (Omega).
    /// I.e. value for Unknown equals 1 and for other sets equals 0.
    implicability(vacuous_t)
    {
        this->m_values.back() = 1;
    }

    explicit implicability(const dst_function<FOD, T> & f)
        : dst_function<FOD, T>(f)
    {
    }

    implicability(const container_type & init_values)
        : dst_function<FOD, T>(init_values)
    {
    }

    ~implicability()
    {
    }

    /// Subnormal mass function has some mass at Emptyset.
    bool is_subnormal() const
    {
        return ! boost::math::fpc::is_small(this->m_values.front(), aux::tolerance);
    }
};

} // namespace beliefs

} // namespace boost

#endif // BOOST_BELIEFS_IMPLICABILITY_HPP
