// Copyright (c) 2011-2014
// Marek Kurdej
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_BFT_RULE_BASE_HPP
#define BOOST_BFT_RULE_BASE_HPP

#include <string>

namespace boost
{
namespace bft
{

struct rule_base
{
    virtual std::string to_string() const = 0;
};

} // namespace bft

} // namespace boost

#endif // BOOST_BFT_RULE_BASE_HPP
