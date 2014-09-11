//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/bft/mass.hpp>
#include <boost/bft/rule_conjunctive.hpp>

BOOST_BFT_DEFINE_CLASS(C1);
BOOST_BFT_DEFINE_CLASS(C2);
BOOST_BFT_DEFINE_CLASS(C3);
BOOST_BFT_DEFINE_CLASS(C4);
BOOST_BFT_DEFINE_CLASS(C5);
BOOST_BFT_DEFINE_CLASS(C6);
BOOST_BFT_DEFINE_CLASS(C7);
BOOST_BFT_DEFINE_CLASS(C8);

typedef boost::bft::fod<C1, C2> fod2;
typedef boost::bft::fod<C1, C2, C3> fod3;

int main()
{
    using namespace boost::bft;

    rule_conjunctive rule;

    typedef fod2 fod_t;

    const mass<fod_t>::container_type ma1 = {0, 0.3, 0, 0.7};
    const mass<fod_t> m1(ma1);
    const mass<fod_t>::container_type ma2 = {0, 0.3, 0, 0.7};
    const mass<fod_t> m2(ma2);

    mass<fod_t> m12 = m1.apply(rule, m2);

    for (std::size_t i = 0; i < fod_t::powerset_size; ++i) {
    }
}
