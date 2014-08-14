//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BELIEF_RULE_BASE_HPP
#define BOOST_BELIEF_RULE_BASE_HPP

#include <string>

namespace boost { namespace belief {

struct rule_base
{
    virtual std::string to_string() const = 0;
};

} // namespace belief

} // namespace boost

#endif // BOOST_BELIEF_RULE_BASE_HPP
