//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BFT_BELIEF_HPP
#define BOOST_BFT_BELIEF_HPP

#include <boost/bft/bft_function.hpp>

namespace boost { namespace bft {

template <class FOD, typename T = double>
class belief
        : public bft_function<FOD, T>
{
public:
    typedef belief<FOD, T> this_type;
    typedef typename bft_function<FOD, T>::container_type container_type;

    /// Default constructor.
    belief()
    {
    }

    /// It creates a belief function equivalent to a mass function where all mass is attributed to the Conflict set (Emptyset).
    /// I.e. all values equal 0.
    belief(degenerate_t)
    {
    }

    /// It creates a belief function equivalent to a mass function where all mass is attributed to the Unknown set (Omega).
    /// I.e. value for Unknown equals 1 and for other sets equals 0.
    belief(vacuous_t)
    {
        this->m_values.back() = 1;
    }

    explicit belief(const bft_function<FOD, T> & f)
        : bft_function<FOD, T>(f)
    {
    }

    belief(const container_type & init_values)
        : bft_function<FOD, T>(init_values)
    {
    }

    ~belief()
    {
    }
};

} // namespace bft

} // namespace boost

#endif // BOOST_BFT_BELIEF_HPP
