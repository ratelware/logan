#include <boost/test/auto_unit_test.hpp>

BOOST_AUTO_TEST_SUITE(adding_is_fun)
BOOST_AUTO_TEST_CASE(simple_integer_values)
{
    BOOST_CHECK_EQUAL(4, 2+2); // this is the "usual" assert
    BOOST_REQUIRE_EQUAL(6, 4+2); // this one throws if is unhappy
    BOOST_WARN_EQUAL(8, 4+4); // this one only prints, so nobody cares
}

BOOST_AUTO_TEST_CASE(doubles_are_more_fun)
{
    BOOST_CHECK_LT(3.99999, 2.0*2.0); // this one is obscure
    BOOST_CHECK_GT(4.00001, 2.0*2.0); // this one also is obscure
    BOOST_CHECK_CLOSE(4.0, 2.0*2.0, 0.001); // this is better - takes percentage
    BOOST_CHECK_CLOSE_FRACTION(4.0, 2.0*2.0, 0.001); // this is also good - accepts 100x more than previous with same args, as it's fraction not value
    // by the way - it won't compile if you pass an integral constant to CLOSE or CLOSE_FRACTION
}

BOOST_AUTO_TEST_SUITE_END()
