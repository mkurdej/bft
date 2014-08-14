//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DST_RULE_BASE_HPP
#define BOOST_DST_RULE_BASE_HPP

#include <string>

namespace boost { namespace dst {

struct rule_base
{
    virtual std::string to_string() const = 0;
};

} // namespace dst

} // namespace boost

#endif // BOOST_DST_RULE_BASE_HPP
