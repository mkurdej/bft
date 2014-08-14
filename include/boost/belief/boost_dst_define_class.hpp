//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DST_DEFINE_CLASS_HPP
#define BOOST_DST_DEFINE_CLASS_HPP

#ifdef _MSC_VER
#   pragma warning(push)	// disable for this header only
#   pragma warning(disable:4820)
#   pragma warning(disable:4986)
#endif // _MSC_VER

#include <string>

#ifdef _MSC_VER
#   pragma warning(pop)  	// restore original warning level
#endif // _MSC_VER

//[ aux_dst_base_class
namespace boost { namespace dst { namespace aux {

struct dst_base_class
{
};

} // namespace aux

} // namespace dst

} // namespace boost
//]

//[ boost_dst_define_class
#define BOOST_DST_DEFINE_CLASS(C) \
    struct C \
        : public ::boost::dst::aux::dst_base_class \
    { \
        static const std::string name; \
    }; \
    \
    const std::string C::name = #C // Note: no semicolon at the end, you have to write it after macro invocation
//]

#endif // BOOST_DST_DEFINE_CLASS_HPP
