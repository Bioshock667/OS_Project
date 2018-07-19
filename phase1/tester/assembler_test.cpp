#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include "Assembler.h"
#include <fstream>
#define BOOST_TEST_MODULE AssemblerTest
#include <boost/test/included/unit_test.hpp>
#include <string>

BOOST_AUTO_TEST_CASE(MyTestCase)
{
	Assembler as;
	as.compile("allins.s");
	ifstream comp, exp;
	string c, e;
	comp.open("allins.o");
	exp.open("expected.o");
	while(exp >> e)
	{
		BOOST_CHECK(comp >> c);
		BOOST_CHECK_EQUAL(e, c);
	}
	BOOST_TEST_MESSAGE("Test complete");	
}
