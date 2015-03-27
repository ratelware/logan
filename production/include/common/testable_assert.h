#ifndef TESTABLE_ASSERT_H_miocewm98fj34985j4ugnrfjdmcd903dk382jf4ufierjfdslkq90d823jfujrfvdmkldmc
#define TESTABLE_ASSERT_H_miocewm98fj34985j4ugnrfjdmcd903dk382jf4ufierjfdslkq90d823jfujrfvdmkldmc

#include <string>

struct assertion_failed
{
	assertion_failed(const std::string& msg) : what(msg)
	{}

	std::string what;
};

#define TESTABLE_ASSERT(x, msg) if(!(x)){throw assertion_failed(msg);}

#endif