//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BFT_BFT_FUNCTION_HPP
#define BOOST_BFT_BFT_FUNCTION_HPP

#include <boost/array.hpp>
#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/bft/detail/emptytype.hpp>
#include <boost/type_traits/is_same.hpp>
#include <iterator>

namespace boost { namespace bft {

namespace /* anonymous */ {
struct degenerate_t {}; // all mass on Emptyset
struct vacuous_t {}; // all mass on Unknown
} // namespace

// TODO: silence warnings about unused variable
// GCC: [-Wunused-variable]
// MSVC: /W?
/*static*/ degenerate_t degenerate;
/*static*/ vacuous_t vacuous;

template <class FOD, typename T = double>
class bft_function
{
public:
    typedef bft_function<FOD, T> this_type;
    typedef FOD fod_type;
    typedef T value_type;
    typedef T container_type[FOD::powerset_size];

    /// Default constructor.
    ///
    /// Default constructor creates a zero-initialized (Dempster-Shafer theory) function.
    bft_function()
    {
        this->m_values.assign(0);
    }

    bft_function(const bft_function & f)
        : m_values(f.m_values)
    {
    }

    template <typename Iterator>
    bft_function(Iterator first, Iterator last)
    {
        BOOST_STATIC_ASSERT(( is_same<T, typename std::iterator_traits<Iterator>::value_type >::value ));
        BOOST_ASSERT(( std::distance(first, last) == FOD::powerset_size ));
        BOOST_ASSERT(( std::distance(first, last) == m_values.size() ));
        // TODO: throw
        std::copy(first, last, this->m_values.begin());
    }

    bft_function(const container_type & init_values)
    {
        BOOST_ASSERT(( FOD::powerset_size == m_values.size() ));
        std::copy(init_values, init_values + FOD::powerset_size, this->m_values.begin());
    }

    // =============================================================================
    virtual ~bft_function()
    {
    }

    // =============================================================================
    std::size_t size() const
    {
        return FOD::powerset_size;
    }

    // =============================================================================
    T& operator[](std::size_t i)
    {
        BOOST_ASSERT_MSG(i < FOD::powerset_size, "Index must be an integer in [0; FOD::powerset_size[");
        return this->m_values[i];
    }

    const T& operator[](std::size_t i) const
    {
        BOOST_ASSERT_MSG(i < FOD::powerset_size, "Index must be an integer in [0; FOD::powerset_size[");
        return this->m_values[i];
    }

    // =============================================================================
    array<T, FOD::powerset_size> & values()
    {
        return this->m_values;
    }

    const array<T, FOD::powerset_size> & values() const
    {
        return this->m_values;
    }

    // =============================================================================
    // =============================================================================
    template <typename S0 = detail::EmptyType, typename S1 = detail::EmptyType, typename S2 = detail::EmptyType, typename S3 = detail::EmptyType, typename S4 = detail::EmptyType, typename S5 = detail::EmptyType, typename S6 = detail::EmptyType, typename S7 = detail::EmptyType, typename S8 = detail::EmptyType, typename S9 = detail::EmptyType>
    struct Idx
    {
        enum
        {
            value
            = ((is_same<detail::EmptyType, S0>::value) ? 0 : (1 << FOD::template Idx<S0>::value))
            + ((is_same<detail::EmptyType, S1>::value) ? 0 : (1 << FOD::template Idx<S1>::value))
            + ((is_same<detail::EmptyType, S2>::value) ? 0 : (1 << FOD::template Idx<S2>::value))
            + ((is_same<detail::EmptyType, S3>::value) ? 0 : (1 << FOD::template Idx<S3>::value))
            + ((is_same<detail::EmptyType, S4>::value) ? 0 : (1 << FOD::template Idx<S4>::value))
            + ((is_same<detail::EmptyType, S5>::value) ? 0 : (1 << FOD::template Idx<S5>::value))
            + ((is_same<detail::EmptyType, S6>::value) ? 0 : (1 << FOD::template Idx<S6>::value))
            + ((is_same<detail::EmptyType, S7>::value) ? 0 : (1 << FOD::template Idx<S7>::value))
            + ((is_same<detail::EmptyType, S8>::value) ? 0 : (1 << FOD::template Idx<S8>::value))
            + ((is_same<detail::EmptyType, S9>::value) ? 0 : (1 << FOD::template Idx<S9>::value))
        };
    };

    // =============================================================================
    // =============================================================================
    static int idx()
    {
        return Idx<>::value;
    }

    template <typename S0>
    static int idx()
    {
        return Idx<S0>::value;
    }

    template <typename S0, typename S1>
    static int idx()
    {
        return Idx<S0,S1>::value;
    }

    template <typename S0, typename S1, typename S2>
    static int idx()
    {
        return Idx<S0,S1,S2>::value;
    }

    template <typename S0, typename S1, typename S2, typename S3>
    static int idx()
    {
        return Idx<S0,S1,S2,S3>::value;
    }

    template <typename S0, typename S1, typename S2, typename S3, typename S4>
    static int idx()
    {
        return Idx<S0,S1,S2,S3,S4>::value;
    }

    template <typename S0, typename S1, typename S2, typename S3, typename S4, typename S5>
    static int idx()
    {
        return Idx<S0,S1,S2,S3,S4,S5>::value;
    }

    template <typename S0, typename S1, typename S2, typename S3, typename S4, typename S5, typename S6>
    static int idx()
    {
        return Idx<S0,S1,S2,S3,S4,S5,S6>::value;
    }

    template <typename S0, typename S1, typename S2, typename S3, typename S4, typename S5, typename S6, typename S7>
    static int idx()
    {
        return Idx<S0,S1,S2,S3,S4,S5,S6,S7>::value;
    }

    template <typename S0, typename S1, typename S2, typename S3, typename S4, typename S5, typename S6, typename S7, typename S8>
    static int idx()
    {
        return Idx<S0,S1,S2,S3,S4,S5,S6,S7,S8>::value;
    }

    template <typename S0, typename S1, typename S2, typename S3, typename S4, typename S5, typename S6, typename S7, typename S8, typename S9>
    static int idx()
    {
        return Idx<S0,S1,S2,S3,S4,S5,S6,S7,S8,S9>::value;
    }

    // =============================================================================
    // =============================================================================
    T & at()
    {
        return this->m_values[Idx<>::value];
    }

    template <typename S0>
    T & at()
    {
        return this->m_values[Idx<S0>::value];
    }

    template <typename S0, typename S1>
    T & at()
    {
        return this->m_values[Idx<S0,S1>::value];
    }

    template <typename S0, typename S1, typename S2>
    T & at()
    {
        return this->m_values[Idx<S0,S1,S2>::value];
    }

    template <typename S0, typename S1, typename S2, typename S3>
    T & at()
    {
        return this->m_values[Idx<S0,S1,S2,S3>::value];
    }

    template <typename S0, typename S1, typename S2, typename S3, typename S4>
    T & at()
    {
        return this->m_values[Idx<S0,S1,S2,S3,S4>::value];
    }

    template <typename S0, typename S1, typename S2, typename S3, typename S4, typename S5>
    T & at()
    {
        return this->m_values[Idx<S0,S1,S2,S3,S4,S5>::value];
    }

    template <typename S0, typename S1, typename S2, typename S3, typename S4, typename S5, typename S6>
    T & at()
    {
        return this->m_values[Idx<S0,S1,S2,S3,S4,S5,S6>::value];
    }

    template <typename S0, typename S1, typename S2, typename S3, typename S4, typename S5, typename S6, typename S7>
    T & at()
    {
        return this->m_values[Idx<S0,S1,S2,S3,S4,S5,S6,S7>::value];
    }

    template <typename S0, typename S1, typename S2, typename S3, typename S4, typename S5, typename S6, typename S7, typename S8>
    T & at()
    {
        return this->m_values[Idx<S0,S1,S2,S3,S4,S5,S6,S7,S8>::value];
    }

    template <typename S0, typename S1, typename S2, typename S3, typename S4, typename S5, typename S6, typename S7, typename S8, typename S9>
    T & at()
    {
        return this->m_values[Idx<S0,S1,S2,S3,S4,S5,S6,S7,S8,S9>::value];
    }

    // =============================================================================
    // =============================================================================
    const T & at() const
    {
        return this->m_values[Idx<>::value];
    }

    template <typename S0>
    const T & at() const
    {
        return this->m_values[Idx<S0>::value];
    }

    template <typename S0, typename S1>
    const T & at() const
    {
        return this->m_values[Idx<S0,S1>::value];
    }

    template <typename S0, typename S1, typename S2>
    const T & at() const
    {
        return this->m_values[Idx<S0,S1,S2>::value];
    }

    template <typename S0, typename S1, typename S2, typename S3>
    const T & at() const
    {
        return this->m_values[Idx<S0,S1,S2,S3>::value];
    }

    template <typename S0, typename S1, typename S2, typename S3, typename S4>
    const T & at() const
    {
        return this->m_values[Idx<S0,S1,S2,S3,S4>::value];
    }

    template <typename S0, typename S1, typename S2, typename S3, typename S4, typename S5>
    const T & at() const
    {
        return this->m_values[Idx<S0,S1,S2,S3,S4,S5>::value];
    }

    template <typename S0, typename S1, typename S2, typename S3, typename S4, typename S5, typename S6>
    const T & at() const
    {
        return this->m_values[Idx<S0,S1,S2,S3,S4,S5,S6>::value];
    }

    template <typename S0, typename S1, typename S2, typename S3, typename S4, typename S5, typename S6, typename S7>
    const T & at() const
    {
        return this->m_values[Idx<S0,S1,S2,S3,S4,S5,S6,S7>::value];
    }

    template <typename S0, typename S1, typename S2, typename S3, typename S4, typename S5, typename S6, typename S7, typename S8>
    const T & at() const
    {
        return this->m_values[Idx<S0,S1,S2,S3,S4,S5,S6,S7,S8>::value];
    }

    template <typename S0, typename S1, typename S2, typename S3, typename S4, typename S5, typename S6, typename S7, typename S8, typename S9>
    const T & at() const
    {
        return this->m_values[Idx<S0,S1,S2,S3,S4,S5,S6,S7,S8,S9>::value];
    }

    // =============================================================================
    // =============================================================================

protected:
    array<T, FOD::powerset_size> m_values;
};

// =============================================================================
// =============================================================================

static std::size_t set_intersection(std::size_t set1, std::size_t set2)
{
    return set1 & set2;
}

static std::size_t set_union(std::size_t set1, std::size_t set2)
{
    return set1 | set2;
}

static std::size_t set_minus(std::size_t set1, std::size_t set2)
{
    return set1 & (set1 ^ set2);
}

static std::size_t set_xor(std::size_t set1, std::size_t set2)
{
    return set1 ^ set2;
}

/*static long set_negate(long set1, long max_set_mask)
    {
        return set_minus(max_set_mask, set1);
    }*/

static bool is_emptyset(std::size_t set1)
{
    return 0 == set1;
}

static bool is_subset_of(std::size_t set1, std::size_t set2)
{
    return set_intersection(set1, set2) == set1;
}

static bool is_superset_of(std::size_t set1, std::size_t set2)
{
    return is_subset_of(set2, set1);
}

static std::size_t count_bits(std::size_t n)
{
    std::size_t c; // c accumulates the total bits set in n
    for (c = 0; n; ++c) {
        n &= n - 1; // clear the least significant bit set
    }
    return c;
}

static std::size_t count_elements(std::size_t set)
{
    return count_bits(set);
}

namespace detail {

template <typename T> void quiet_warning()
{
    (void) degenerate;
    (void) vacuous;
}

} // namespace detail

} // namespace bft

} // namespace boost

#endif // BOOST_BFT_BFT_FUNCTION_HPP
