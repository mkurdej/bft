#include <boost/belief/fod.hpp>
#include <boost/belief/rule_conjunctive.hpp>
#include <vector>

BOOST_BELIEF_DEFINE_CLASS(C1);
BOOST_BELIEF_DEFINE_CLASS(C2);
BOOST_BELIEF_DEFINE_CLASS(C3);
BOOST_BELIEF_DEFINE_CLASS(C4);

namespace belief = boost::belief;

typedef belief::fod<C1, C2> fodAB;
typedef belief::fod<C1, C2, C3, C4> fodABCD;

int main( int , char* [] )
{
    belief::rule_conjunctive rule;

    const mass<fodAB> m1;
    const mass<fodABCD> m2;

    //  Should fail to compile because the underlying FODs are different.
    //  They are the different size.
    m1.apply(rule, m2);
    return 0;
}
