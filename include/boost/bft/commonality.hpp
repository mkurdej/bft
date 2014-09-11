// Copyright (c) 2011-2014
// Marek Kurdej
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_BFT_COMMONALITY_HPP
#define BOOST_BFT_COMMONALITY_HPP

#include <boost/bft/bft_function.hpp>
#include <boost/bft/fod.hpp>
#include <boost/bft/detail/is_small.hpp>

namespace boost
{
namespace bft
{

template <class FOD, typename T = double>
class commonality : public bft_function<FOD, T>
{
public:
    typedef commonality<FOD, T> this_type;
    typedef typename bft_function<FOD, T>::container_type container_type;

    /// Default constructor.
    commonality()
    {
    }

    /// It creates a commonality function equivalent to a mass function where
    /// all mass is attributed to the Conflict set (Emptyset).
    /// I.e. value for Conflict (Emptyset) equals 1 and for other sets equals 0.
    commonality(degenerate_t)
    {
        this->m_values.front() = 1;
    }

    /// It creates a commonality function equivalent to a mass function where
    /// all mass is attributed to the Unknown set (Omega).
    /// I.e. all values equal 1.
    commonality(vacuous_t)
    {
        this->m_values.assign(1);
    }

    explicit commonality(const bft_function<FOD, T>& f)
        : bft_function<FOD, T>(f)
    {
    }

    commonality(const container_type& init_values)
        : bft_function<FOD, T>(init_values)
    {
    }

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    commonality(const std::initializer_list<T>& init_values)
        : bft_function<FOD, T>(init_values)
    {
    }
#endif

    ~commonality()
    {
    }

    /// Non-dogmatic mass function has some mass at Unknown.
    bool is_nondogmatic() const
    {
        return !detail::is_small(this->m_values.back(), detail::tolerance);
    }
};

} // namespace bft

} // namespace boost

#endif // BOOST_BFT_COMMONALITY_HPP
