#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include "VirtualMachine.h"
#include <fstream>
#define BOOST_TEST_MODULE AssemblerTest
#include <boost/test/included/unit_test.hpp>
#include <string>

BOOST_AUTO_TEST_CASE(MyTestCase)
{
	VitualMachine vm;
	ifstream results;
	ofstream progIn;
	results.open("flag_checker.out");
	int l,e,g;
	results >> g >> e >> l;

	BOOST_TEST_MESSAGE("Test complete");	
}
