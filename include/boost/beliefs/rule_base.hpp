//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BELIEFS_RULE_BASE_HPP
#define BOOST_BELIEFS_RULE_BASE_HPP

#include <string>

namespace boost { namespace beliefs {

struct rule_base
{
    virtual std::string to_string() const = 0;
};

} // namespace beliefs

} // namespace boost

#endif // BOOST_BELIEFS_RULE_BASE_HPP
