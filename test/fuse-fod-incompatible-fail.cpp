#include <boost/dst/fod.hpp>
#include <boost/dst/rule_conjunctive.hpp>
#include <vector>

BOOST_DST_DEFINE_CLASS(C1);
BOOST_DST_DEFINE_CLASS(C2);
BOOST_DST_DEFINE_CLASS(C3);
BOOST_DST_DEFINE_CLASS(C4);

namespace dst = boost::dst;

typedef dst::fod<C1, C2> fodAB;
typedef dst::fod<C1, C2, C3, C4> fodABCD;

int main( int , char* [] )
{
    dst::rule_conjunctive rule;

    const mass<fodAB> m1;
    const mass<fodABCD> m2;

    //  Should fail to compile because the underlying FODs are different.
    //  They are the different size.
    m1.apply(rule, m2);
    return 0;
}
