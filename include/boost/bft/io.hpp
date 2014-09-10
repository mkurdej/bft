//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BFT_IO_HPP
#define BOOST_BFT_IO_HPP

#include <boost/bft/bft_function.hpp>
#include <boost/bft/mass.hpp>
#include <boost/preprocessor/cat.hpp>
#include <ostream>

namespace boost
{
namespace bft
{

namespace detail
{
template <typename CharT>
struct bft_io_traits;

#define BOOST_BFT_DEFINE_TRAITS_MEMBER(CharT, key, value)   \
    static std::basic_string<CharT> key()                   \
    {                                                       \
        return value;                                       \
    }                                                       \
/**/

#define BOOST_BFT_SPECIALIZE_TRAITS(CharT, prefix_, infix_, suffix_)    \
    template <>                                                         \
    struct bft_io_traits<CharT>                                         \
    {                                                                   \
        BOOST_BFT_DEFINE_TRAITS_MEMBER(CharT, prefix, prefix_)          \
        BOOST_BFT_DEFINE_TRAITS_MEMBER(CharT, infix, infix_)            \
        BOOST_BFT_DEFINE_TRAITS_MEMBER(CharT, suffix, suffix_)          \
    };                                                                  \
/**/

#define BOOST_BFT_SPECIALIZE_TRAITS_WITH_PREFIX(CharT, string_prefix,       \
                                                prefix_, infix_, suffix_)   \
BOOST_BFT_SPECIALIZE_TRAITS(CharT,          \
    BOOST_PP_CAT(string_prefix, prefix_),   \
    BOOST_PP_CAT(string_prefix, infix_),    \
    BOOST_PP_CAT(string_prefix, suffix_))   \
/**/

BOOST_BFT_SPECIALIZE_TRAITS(char, "[", ", ", "]")
#ifndef BOOST_NO_CWCHAR
BOOST_BFT_SPECIALIZE_TRAITS_WITH_PREFIX(wchar_t, L, "[", ", ", "]")
#endif // BOOST_NO_CWCHAR
#if BOOST_VERSION >= 104700 && !(defined(BOOST_NO_CXX11_CHAR16_T) || defined(BOOST_NO_CXX11_CHAR32_T) || defined(BOOST_NO_CXX11_UNICODE_LITERALS))
//BOOST_BFT_SPECIALIZE_TRAITS_WITH_PREFIX(char16_t, u, "[", ", ", "]")
//BOOST_BFT_SPECIALIZE_TRAITS_WITH_PREFIX(char32_t, U, "[", ", ", "]")
#endif // BOOST_NO_CXX11_UNICODE_LITERALS

#undef BOOST_BFT_SPECIALIZE_TRAITS_WITH_PREFIX
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
