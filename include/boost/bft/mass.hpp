//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BFT_MASS_HPP
#define BOOST_BFT_MASS_HPP

#include <boost/bft/bft_function.hpp>
#include <boost/bft/fod.hpp>
#include <boost/test/floating_point_comparison.hpp>

namespace boost { namespace bft {

template <class FOD, typename T = double>
class mass
    : public bft_function<FOD, T>
{
public:
    typedef mass<FOD, T> this_type;
    typedef typename bft_function<FOD, T>::container_type container_type;

    /// Default constructor.
    mass()
    {
    }

    /// It creates a mass function will all mass attributed to the Conflict set (Emptyset).
    explicit mass(degenerate_t)
    {
        at_emptyset() = 1;
    }

    /// It creates a mass function will all mass attributed to the Unknown set (Omega).
    explicit mass(vacuous_t)
    {
        at_omega() = 1;
    }

    explicit mass(const bft_function<FOD, T> & f)
        : bft_function<FOD, T>(f)
    {
    }

    template <typename Iterator>
    mass(Iterator first, Iterator last)
        : bft_function<FOD, T>(first, last)
    {
    }

    mass(const container_type & init_values)
        : bft_function<FOD, T>(init_values)
    {
    }

    // =============================================================================
    static mass<FOD, T> create_mass_from_conjunctive_weight(std::size_t set, T w)
    {
        mass<FOD, T> m;
        m.at_omega() = w;
        m[set] = 1 - w;
        return m;
    }

    static mass<FOD, T> create_mass_from_disjunctive_weight(std::size_t set, T v)
    {
        mass<FOD, T> m;
        m.at_emptyset() = v;
        m[set] = 1 - v;
        return m;
    }

    /// Destructor
    ~mass()
    {
    }

    T& at_emptyset()
    {
        return this->values().front();
    }

    T const& at_emptyset() const
    {
        return this->values().front();
    }

    T& at_omega()
    {
        return this->values().back();
    }

    T const& at_omega() const
    {
        return this->values().back();
    }

    //        template <class RuleFunctor>
    //        void apply(RuleFunctor functor)
    //        {
    //            const mass<FOD, T> & m1 = *this;
    //            m1 = functor(m1);
    //        }

    // TODO: separate "in-place" and "return_" algorithms
    // TODO: remove apply, use free functions for algorithms (fusion rules)
    // bft::fuse(rule_conjunctive(), mf1, mf2); // mf1 <- mf1 \opconj mf2
    // mf12 = bft::return_fuse(rule_conjunctive(), mf1, mf2); // const // mf12 <- mf1 \opconj mf2

    template <class RuleFunctor>
    mass<FOD, T> apply(RuleFunctor functor) const
    {
        const mass<FOD, T> & m1 = *this;
        return functor(m1);
    }

    //        template <class RuleFunctor>
    //        void apply(RuleFunctor functor, const mass<FOD, T> & m2)
    //        {
    //            const mass<FOD, T> & m1 = *this;
    //            m1 = functor(m1, m2);
    //        }

    template <class RuleFunctor>
    mass<FOD, T> apply(RuleFunctor functor, const mass<FOD, T> & m2) const
    {
        const mass<FOD, T> & m1 = *this;
        return functor(m1, m2);
    }

    bool is_singleton(std::size_t i) const
    {
        BOOST_ASSERT(i < FOD::powerset_size);
        return is_power_of_two(i);
    }

    // TODO: is_singleton<S0,...,S9>()
    //        bool is_singleton()
    //        {
    //            return is_singleton(Idx<S0,...,S9>::value);
    //        }

    //! http://en.wikipedia.org/wiki/Power_of_two#Fast_algorithm_to_check_if_a_positive_number_is_a_power_of_two
    static bool is_power_of_two(std::size_t n)
    {
        // wanted behavior: gives @true when n==0
        return 0 == (n & (n-1));
    }

    /// A focal set has a non-zero mass attributed.
    ///
    /// @param i set index, i \in [0, powerset_size[
    bool is_focal(std::size_t i) const
    {
        BOOST_ASSERT(i < FOD::powerset_size);
        return ! boost::math::fpc::is_small(this->values()[i], detail::tolerance);
    }

    // emptyset
    bool is_focal() const
    {
        return is_focal(bft_function<FOD, T>::template Idx<>::value);
    }

    template <typename S0>
    bool is_focal() const
    {
        return is_focal(bft_function<FOD, T>::template Idx<S0>::value);
    }

    template <typename S0, typename S1>
    bool is_focal() const
    {
        return is_focal(bft_function<FOD, T>::template Idx<S0,S1>::value);
    }

    template <typename S0, typename S1, typename S2>
    bool is_focal() const
    {
        return is_focal(bft_function<FOD, T>::template Idx<S0,S1,S2>::value);
    }

    template <typename S0, typename S1, typename S2, typename S3>
    bool is_focal() const
    {
        return is_focal(bft_function<FOD, T>::template Idx<S0,S1,S2,S3>::value);
    }

    template <typename S0, typename S1, typename S2, typename S3, typename S4>
    bool is_focal() const
    {
        return is_focal(bft_function<FOD, T>::template Idx<S0,S1,S2,S3,S4>::value);
    }

    template <typename S0, typename S1, typename S2, typename S3, typename S4, typename S5>
    bool is_focal() const
    {
        return is_focal(bft_function<FOD, T>::template Idx<S0,S1,S2,S3,S4,S5>::value);
    }

    template <typename S0, typename S1, typename S2, typename S3, typename S4, typename S5, typename S6>
    bool is_focal() const
    {
        return is_focal(bft_function<FOD, T>::template Idx<S0,S1,S2,S3,S4,S5,S6>::value);
    }

    template <typename S0, typename S1, typename S2, typename S3, typename S4, typename S5, typename S6, typename S7>
    bool is_focal() const
    {
        return is_focal(bft_function<FOD, T>::template Idx<S0,S1,S2,S3,S4,S5,S6,S7>::value);
    }

    template <typename S0, typename S1, typename S2, typename S3, typename S4, typename S5, typename S6, typename S7, typename S8>
    bool is_focal() const
    {
        return is_focal(bft_function<FOD, T>::template Idx<S0,S1,S2,S3,S4,S5,S6,S7,S8>::value);
    }

    template <typename S0, typename S1, typename S2, typename S3, typename S4, typename S5, typename S6, typename S7, typename S8, typename S9>
    bool is_focal() const
    {
        return is_focal(bft_function<FOD, T>::template Idx<S0,S1,S2,S3,S4,S5,S6,S7,S8,S9>::value);
    }

    /// Normal mass function has no mass at Emptyset (Conflict).
    bool is_normal() const
    {
        return ! is_focal();
    }

    /// Regular mass function has no mass at Emptyset (Conflict).
    bool is_regular() const
    {
        return is_normal();
    }

    /// Subnormal mass function has some mass at Emptyset (Conflict).
    bool is_subnormal() const
    {
        return ! is_normal();
    }

    // =============================================================================
    /// Dogmatic mass function has no mass at Unknown.
    bool is_dogmatic() const
    {
        return boost::math::fpc::is_small(at_omega(), detail::tolerance);
    }

    /// Non-dogmatic mass function has some mass at Unknown.
    bool is_nondogmatic() const
    {
        return ! boost::math::fpc::is_small(at_omega(), detail::tolerance);
    }

    /// Vacuous mass function has all mass at Unknown.
    bool is_vacuous() const
    {
        return boost::math::fpc::is_small(1 - at_omega(), detail::tolerance);
    }

    /// Degenerate mass function has all mass at Emptyset (Conflict).
    bool is_degenerate() const
    {
        return boost::math::fpc::is_small(1 - at_emptyset(), detail::tolerance);
    }

    /// Categorical mass function has only one focal set.
    bool is_categorical() const
    {
        std::size_t focal_set_count = 0;
        for(std::size_t A = 0; A < FOD::powerset_size; ++A) {
            if(is_focal(A)) {
                ++focal_set_count;
                if(focal_set_count > 1) {
                    return false;
                }
            }
        }
        return true;
    }

    /// Simple mass function has at most two focal sets, and if it has two, Omega is one of them.
    bool is_simple() const
    {
        std::size_t focal_set_count = 0;
        for(std::size_t A = 0; A < FOD::powerset_size; ++A) {
            if(is_focal(A)) {
                ++focal_set_count;
                if(focal_set_count > 2) {
                    return false;
                }
            }
        }

        bool has_one_focal_set = (1 == focal_set_count);
        bool has_two_focal_sets = (2 == focal_set_count); // unnecessary with the inner if-clause
        bool is_omega_a_focal_set = is_focal(FOD::powerset_size-1);
        return has_one_focal_set || (has_two_focal_sets && is_omega_a_focal_set);
    }

    /// In bayesian mass function, all focal sets are singletons.
    bool is_bayesian() const
    {
        for(std::size_t A = 0; A < FOD::powerset_size; ++A) {
            if(is_focal(A)) {
                if(!is_singleton(A)) {
                    return false;
                }
            }
        }
        return true;
    }

    /// Mass function is consonant when all focal sets are nested.
    ///
    /// Consonant evidence can be represented as a nested structure of subsets where the
    /// elements of the smallest set are included in the next larger set, all of whose elements are
    /// included in the next larger set and so on.
    ///
    /// Equivalent to pl(A union B) == max(pl(A), pl(B))
    /// Equivalent to bel(A intersection B) == min(bel(A), bel(B))
    bool is_consonant() const
    {
        std::size_t A;
        for(A = 0; A < FOD::powerset_size; ++A) { // for all subsets in powerset 2^FOD
            if(is_focal(A)) {
                // found first smallest focal element
                break;
            }
        }
        for(std::size_t B = A + 1; B < FOD::powerset_size; ++B) {
            if(is_focal(B)) {
                if(! is_subset_of(A, B)) {
                    return false;
                }
                A = B;
            }
        }
        return true;
    }

    /// Mass function is consistent when there is at least one set that is common to all
    /// focal sets.
    ///
    /// Consistent evidence means that there is at least one set that is common to all
    /// focal sets.
    bool is_consistent() const
    {
        std::size_t A;
        for(A = 0; A < FOD::powerset_size; ++A) { // for all subsets in powerset 2^FOD
            if(is_focal(A)) {
                // found first smallest focal element
                break;
            }
        }
        for(std::size_t B = A + 1; B < FOD::powerset_size; ++B) {
            if(is_focal(B)) {
                if(! is_subset_of(A, B)) {
                    return false;
                }
            }
        }
        return true;
    }

    /// Arbitrary evidence corresponds to the situation where there is no element common to
    /// all subsets, though some subsets may have elements in common.
    bool is_arbitrary() const
    {
        BOOST_ASSERT_MSG(false, "unimplemented");
        return false;
    }

    /// Disjoint evidence implies that any two subsets have no elements in common with any
    /// other subset.
    bool is_disjoint() const
    {
        BOOST_ASSERT_MSG(false, "unimplemented");
        return false;
    }

    /// Focal sets of a partitioned mass function do not intersect and their union is equal to the frame of discernment \f$ \Omega \f$.
    bool is_partitioned() const
    {
        std::size_t focals_union = 0, focals_intersections_union = 0;
        for(std::size_t A = 0; A < FOD::powerset_size; ++A) { // for all subsets in powerset 2^FOD
            if(is_focal(A)) {
                // found first smallest focal element
                focals_union = A;
                break;
            }
        }
        for(std::size_t A = focals_union + 1; A < FOD::powerset_size; ++A) {
            if(is_focal(A)) {
                //focals_intersection = set_intersection(A, focals_intersection);
                //focals_intersections_union = set_union(focals_intersection, focals_intersections_union);
                //focals_union = set_union(A, focals_union);
                //focals_intersection = A;

                if (0 != set_intersection(A, focals_union)) {
                    return false;
                }
                focals_union = set_union(A, focals_union);
            }
        }
        std::size_t omega = FOD::powerset_size - 1;
        return (0 == focals_intersections_union) && (omega == focals_union);
    }

    /// Mass function without internal conflict is a one where all pairs of focal elements have a non-empty intersection.
    /// \f[
    /// \forall A, B \subseteq \Omega, m(A) > 0, m(B) > 0 : A \cap B \neq \emptyset
    /// \f]
    bool has_internal_conflict() const
    {
        std::size_t focals_intersection = 0;
        for(std::size_t A = 0; A < FOD::powerset_size; ++A) { // for all subsets in powerset 2^FOD
            if(is_focal(A)) {
                // found first smallest focal element
                focals_intersection = A;
                break;
            }
        }
        for(std::size_t A = focals_intersection + 1; A < FOD::powerset_size; ++A) {
            if(is_focal(A)) {
                focals_intersection = set_intersection(A, focals_intersection);
            }
        }
        // has internal conflict if intersection of all focal elements is an emptyset
        return 0 == focals_intersection;
    }
};

} // namespace bft

} // namespace boost

#endif // BOOST_BFT_MASS_HPP
