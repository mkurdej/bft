#include <boost/bft/fod.hpp>
#include <boost/bft/rule_conjunctive.hpp>
#include <vector>

BOOST_BFT_DEFINE_CLASS(C1);
BOOST_BFT_DEFINE_CLASS(C2);
BOOST_BFT_DEFINE_CLASS(C3);
BOOST_BFT_DEFINE_CLASS(C4);

namespace bb = boost::bft;

typedef bb::fod<C1, C2> fodAB;
typedef bb::fod<C1, C2, C3, C4> fodABCD;

int main(int, char* [])
{
    bb::rule_conjunctive rule;

    const bb::mass<fodAB> m1;
    const bb::mass<fodABCD> m2;

    //  Should fail to compile because the underlying FODs are different.
    //  They are of different size.
    m1.apply(rule, m2);
    return 0;
}
