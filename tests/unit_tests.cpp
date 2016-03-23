#include "../src/cgpp"
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE ObjectTest
//#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(object_test)

// token tests
BOOST_AUTO_TEST_CASE(token_test)
{
	BOOST_TEST_MESSAGE("token test");

	// empty ctor
	cgpp::Token t_empty = cgpp::Token();

	// ctor with string and postag
	cgpp::Token t_a1 = cgpp::Token("string", "tag");
	// TODO : strcmp(Fdim.name(), "F Diminished") == 0 
	// @BUG below comparison throws error
	BOOST_CHECK(t_a1.value() == "string");
	BOOST_CHECK(t_a1.tag() == "tag");

	// copy ctor
	cgpp::Token t_a2 = cgpp::Token(t_a1);
	BOOST_CHECK(t_a1 == t_a2);
	BOOST_CHECK(t_a2.value() == "string");
	BOOST_CHECK(t_a2.tag() == "tag");

	// asignment ctor
	cgpp::Token t_a3 = t_a2;
	BOOST_CHECK(t_a2 == t_a3);
	BOOST_CHECK(t_a3.value() == "string");
	BOOST_CHECK(t_a3.tag() == "tag");

	cgpp::Token t_b1 = cgpp::Token("blah", "none");
	BOOST_CHECK(t_b1.value() == "blah");
	BOOST_CHECK(t_b1.tag() == "none");

	// check difference
	BOOST_CHECK(t_a1 != t_empty);
	BOOST_CHECK(t_a1 != t_b1);
	BOOST_CHECK(t_a2 != t_b1);
	BOOST_CHECK(t_a3 != t_b1);
}

// Construct a Concept
/*
BOOST_AUTO_TEST_CASE(concept_test)
{
	// empty Ctor
	Concept c_a0 = Concept();
	
	// ctor with Token
	Token t_a1 = Token("string", "tag");
	Concept c_a1 = 
}
*/

// Construct a Relation

// Construct an Edge

// Construct a ConceptualGraph

BOOST_AUTO_TEST_SUITE_END( )

