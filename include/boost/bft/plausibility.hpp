// Copyright (c) 2011-2014
// Marek Kurdej
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_BFT_PLAUSIBILITY_HPP
#define BOOST_BFT_PLAUSIBILITY_HPP

#include <boost/bft/bft_function.hpp>

namespace boost
{
namespace bft
{

template <class FOD, typename T = double>
class plausibility : public bft_function<FOD, T>
{
public:
    typedef plausibility<FOD, T> this_type;
    typedef typename bft_function<FOD, T>::container_type container_type;

    /// Default constructor.
    plausibility()
    {
    }

    /// It creates a plausibility function equivalent to a mass function where
    /// all mass is attributed to the Conflict set (Emptyset).
    /// I.e. all values equal 0.
    plausibility(degenerate_t)
    {
    }

    /// It creates a plausibility function equivalent to a mass function where
    /// all mass is attributed to the Unknown set (Omega).
    /// I.e. value for Conflict (Emptyset) equals 1 and for other sets equals 0.
    plausibility(vacuous_t)
    {
        this->m_values.assign(1);
        this->m_values.front() = 0;
    }

    explicit plausibility(const bft_function<FOD, T>& f)
        : bft_function<FOD, T>(f)
    {
    }

    plausibility(const container_type& init_values)
        : bft_function<FOD, T>(init_values)
    {
    }

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    plausibility(const std::initializer_list<T>& init_values)
        : bft_function<FOD, T>(init_values)
    {
    }
#endif

    ~plausibility()
    {
    }
};

} // namespace bft

} // namespace boost

#endif // BOOST_BFT_PLAUSIBILITY_HPP
