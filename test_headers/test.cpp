// Boost.Beliefs - A C++ library for uncertain information fusion using the
// theory of belief functions (Dempster-Shafer theory)
//
// Copyright (C) 2011-2014 Marek Kurdej
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_BELIEFS_STRINGIZE_IMPL(x) #x
#define BOOST_BELIEFS_STRINGIZE(x) BOOST_BELIEFS_STRINGIZE_IMPL(x)

#define BOOST_BELIEFS_HEADER BOOST_BELIEFS_STRINGIZE(BOOST_BELIEFS_HEADER_NAME)

#include BOOST_BELIEFS_HEADER
#include BOOST_BELIEFS_HEADER

int main() {}
