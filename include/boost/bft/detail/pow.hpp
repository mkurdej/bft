//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BFT_DETAIL_POW_HPP
#define BOOST_BFT_DETAIL_POW_HPP

#pragma warning(push) // disable for this header only
#pragma warning(disable : 4668)
#include <boost/static_assert.hpp>
#pragma warning(pop)

namespace boost
{
namespace bft
{
namespace detail
{

/**
Power of 2 class template
Result is in the <b>value</b> <tt>static const</tt> variable, equal to
2^EXPONENT
Only positive integers can be used.
*/
template <long BASE, long EXPONENT>
class pow
{
    typedef pow<BASE, EXPONENT - 1> pow_minus_one;

public:
    BOOST_STATIC_CONSTANT(int, value = BASE * pow_minus_one::value);

    BOOST_STATIC_ASSERT_MSG((EXPONENT > 0),
                            "Exponent must be a positive integer");
};

template <long BASE>
struct pow<BASE, 0>
{
    BOOST_STATIC_CONSTANT(int, value = 1);
};

} // namespace detail

} // namespace bft

} // namespace boost

#endif // BOOST_BFT_DETAIL_POW_HPP
