//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BFT_IO_HPP
#define BOOST_BFT_IO_HPP

#include <boost/bft/bft_function.hpp>
#include <boost/bft/mass.hpp>
#include <ostream>

namespace boost
{
namespace bft
{

namespace detail
{
template <typename CharT>
struct bft_io_traits;

#define BOOST_BFT_DEFINE_TRAITS_MEMBER(CharT, string_prefix, key, value)       \
    static std::basic_string<CharT> key()                                      \
    {                                                                          \
        return BOOST_PP_CAT(string_prefix, value);                             \
    } \                                                                       \
/**/

#define BOOST_BFT_SPECIALIZE_TRAITS(CharT, string_prefix, prefix_, infix_,     \
                                    suffix_)                                   \
    template <>                                                                \
    struct bft_io_traits<CharT>                                                \
    {                                                                          \
        BOOST_BFT_DEFINE_TRAITS_MEMBER(CharT, string_prefix, prefix, prefix_)  \
        BOOST_BFT_DEFINE_TRAITS_MEMBER(CharT, string_prefix, infix, infix_)    \
        BOOST_BFT_DEFINE_TRAITS_MEMBER(CharT, string_prefix, suffix, suffix_)  \
    }; \                                                                      \
/**/

BOOST_BFT_SPECIALIZE_TRAITS(char, , "[", ", ", "]")
#ifndef BOOST_NO_CWCHAR
BOOST_BFT_SPECIALIZE_TRAITS(wchar_t, L, "[", ", ", "]")
#endif // BOOST_NO_CWCHAR
#ifndef BOOST_NO_CXX11_UNICODE_LITERALS
BOOST_BFT_SPECIALIZE_TRAITS(char16_t, u, "[", ", ", "]")
BOOST_BFT_SPECIALIZE_TRAITS(char32_t, U, "[", ", ", "]")
#endif // BOOST_NO_CXX11_UNICODE_LITERALS

#undef BOOST_BFT_SPECIALIZE_TRAITS
#undef BOOST_BFT_DEFINE_TRAITS_MEMBER

} // namespace detail

template <typename CharT, typename CharTraits, class FOD,
          typename T> //, typename IoTraits = detail::bft_io_traits<CharT> >
std::basic_ostream<CharT, CharTraits>&
operator<<(std::basic_ostream<CharT, CharTraits>& os,
           boost::bft::bft_function<FOD, T> const& bft)
{
    typedef detail::bft_io_traits<CharT> IoTraits;
    os << IoTraits::prefix();
    for (std::size_t i = 0; i < FOD::powerset_size - 1; ++i) {
        os << bft[i] << IoTraits::infix();
    }
    os << bft[FOD::powerset_size - 1];
    os << IoTraits::suffix();

    return os;
}

} // namespace bft

} // namespace boost

#endif // BOOST_BFT_IO_HPP
