//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DST_PLAUSIBILITY_HPP
#define BOOST_DST_PLAUSIBILITY_HPP

#include <boost/dst/dst_function.hpp>

namespace boost { namespace dst {

template <class FOD, typename T = double>
class plausibility
        : public dst_function<FOD, T>
{
public:
    typedef plausibility<FOD, T> this_type;
    typedef typename dst_function<FOD, T>::container_type container_type;

    /// Default constructor.
    plausibility()
    {
    }

    /// It creates a plausibility function equivalent to a mass function where all mass is attributed to the Conflict set (Emptyset).
    /// I.e. all values equal 0.
    plausibility(degenerate_t)
    {
    }

    /// It creates a plausibility function equivalent to a mass function where all mass is attributed to the Unknown set (Omega).
    /// I.e. value for Conflict (Emptyset) equals 1 and for other sets equals 0.
    plausibility(vacuous_t)
    {
        this->m_values.assign(1);
        this->m_values.front() = 0;
    }

    explicit plausibility(const dst_function<FOD, T> & f)
        : dst_function<FOD, T>(f)
    {
    }

    plausibility(const container_type & init_values)
        : dst_function<FOD, T>(init_values)
    {
    }

    ~plausibility()
    {
    }

};

} // namespace dst

} // namespace boost

#endif // BOOST_DST_PLAUSIBILITY_HPP
