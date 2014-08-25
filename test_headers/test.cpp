// Boost.BFT - A C++ library for uncertain information fusion using the
// theory of belief functions (Dempster-Shafer theory)
//
// Copyright (C) 2011-2014 Marek Kurdej
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_BFT_STRINGIZE_IMPL(x) #x
#define BOOST_BFT_STRINGIZE(x) BOOST_BFT_STRINGIZE_IMPL(x)

#define BOOST_BFT_HEADER BOOST_BFT_STRINGIZE(BOOST_BFT_HEADER_NAME)

#include BOOST_BFT_HEADER
#include BOOST_BFT_HEADER

int main() {}
