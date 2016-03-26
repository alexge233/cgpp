#define BOOST_TEST_MODULE ObjectTest
#include <boost/test/unit_test.hpp>
#include "../src/cgpp"

BOOST_AUTO_TEST_SUITE(object_test)

// token tests
BOOST_AUTO_TEST_CASE(token_test)
{
	BOOST_TEST_MESSAGE("token test");
	std::string value = "string";
	std::string tag = "tag;";

	// empty ctor
	cgpp::Token t_empty = cgpp::Token();

	// ctor with string and postag
	cgpp::Token t_a1 = cgpp::Token(value, tag);
	BOOST_CHECK(t_a1.value() == value);
	BOOST_CHECK(t_a1.tag() == tag);

	// copy ctor
	cgpp::Token t_a2 = cgpp::Token(t_a1);
	BOOST_CHECK(t_a1 == t_a2);
	BOOST_CHECK(t_a2.value() == value);
	BOOST_CHECK(t_a2.tag() == tag);

	// asignment ctor
	cgpp::Token t_a3 = t_a2;
	BOOST_CHECK(t_a2 == t_a3);
	BOOST_CHECK(t_a3.value() == value);
	BOOST_CHECK(t_a3.tag() == tag);

	value = "blah";
	tag = "none";	
	cgpp::Token t_b1 = cgpp::Token(value, tag);
	BOOST_CHECK(t_b1.value() == value);
	BOOST_CHECK(t_b1.tag() == tag);

	// check difference
	BOOST_CHECK(t_a1 != t_empty);
	BOOST_CHECK(t_a1 != t_b1);
	BOOST_CHECK(t_a2 != t_b1);
	BOOST_CHECK(t_a3 != t_b1);
}

// Construct a Concept
BOOST_AUTO_TEST_CASE(concept_test)
{
	BOOST_TEST_MESSAGE("Concept test");
	std::string value = "string";
	std::string tag = "tag;";

	cgpp::Token tok = cgpp::Token(value, tag);
	BOOST_CHECK(tok.value() == value);
	BOOST_CHECK(tok.tag() == tag);
	// empty Ctor
	cgpp::Concept c_empty = cgpp::Concept();
	// ctor with Token - but no index
	cgpp::Concept c_a1 = cgpp::Concept(tok);
	// ctor with Token and index
	cgpp::Concept c_a2 = cgpp::Concept(tok, 1);
	// copy ctor
	cgpp::Concept c_a3 = cgpp::Concept(c_a2);
	// assignment ctor
	cgpp::Concept c_a4 = c_a3;
	// different token index
	cgpp::Concept c_a5 = cgpp::Concept(tok, 2);

	BOOST_CHECK(c_empty != c_a1);
	BOOST_CHECK(c_a1 != c_a2);
	BOOST_CHECK(c_a2 == c_a2);
	BOOST_CHECK(c_a2 == c_a3);
	BOOST_CHECK(c_a3 == c_a4);
	BOOST_CHECK(c_a4 != c_a5);
	BOOST_CHECK(c_a1.label() == value);
	BOOST_CHECK(c_a1.as_token().tag() == tag);
	BOOST_CHECK(c_a2.label() == value);
	BOOST_CHECK(c_a2.as_token().tag() == tag);
	BOOST_CHECK(c_a2.token_index() == 1);
	BOOST_CHECK(c_a5.token_index() == 2);
	BOOST_CHECK(c_empty.token_index() == -1);

	value = "xyz";
	tag = "xyz";
	cgpp::Token tok2 = cgpp::Token(value, tag);
	cgpp::Concept c_b1 = cgpp::Concept(tok2);

	BOOST_CHECK(c_a1 != c_b1);
	BOOST_CHECK(c_b1 != c_empty);
	BOOST_CHECK(c_b1 == c_b1);
	BOOST_CHECK(c_empty < c_a2);
	BOOST_CHECK(c_a2 < c_b1);
}

// Construct a Relation
BOOST_AUTO_TEST_CASE(relation_test)
{
	BOOST_TEST_MESSAGE("Relation test");
	std::string value = "string";
	std::string tag = "tag;";

	cgpp::Token tok = cgpp::Token(value, tag);
	BOOST_CHECK(tok.value() == value);
	BOOST_CHECK(tok.tag() == tag);
	// empty Ctor
	cgpp::Relation r_empty = cgpp::Relation();
	// ctor with Token - but no index
	cgpp::Relation r_a1 = cgpp::Relation(tok);
	// ctor with Token and index
	cgpp::Relation r_a2 = cgpp::Relation(tok, 1);
	// copy ctor
	cgpp::Relation r_a3 = cgpp::Relation(r_a2);
	// assignment ctor
	cgpp::Relation r_a4 = r_a3;
	// different token index
	cgpp::Relation r_a5 = cgpp::Relation(tok, 2);

	BOOST_CHECK(r_empty != r_a1);
	BOOST_CHECK(r_a1 != r_a2);
	BOOST_CHECK(r_a2 == r_a2);
	BOOST_CHECK(r_a2 == r_a3);
	BOOST_CHECK(r_a3 == r_a4);
	BOOST_CHECK(r_a4 != r_a5);
	BOOST_CHECK(r_a1.label() == value);
	BOOST_CHECK(r_a1.as_token().tag() == tag);
	BOOST_CHECK(r_a2.label() == value);
	BOOST_CHECK(r_a2.as_token().tag() == tag);
	BOOST_CHECK(r_a2.token_index() == 1);
	BOOST_CHECK(r_a5.token_index() == 2);
	BOOST_CHECK(r_empty.token_index() == -1);

	value = "xyz";
	tag = "xyz";
	cgpp::Token tok2 = cgpp::Token(value, tag);
	cgpp::Relation r_b1 = cgpp::Relation(tok2);

	BOOST_CHECK(r_a1 != r_b1);
	BOOST_CHECK(r_b1 != r_empty);
	BOOST_CHECK(r_b1 == r_b1);
	BOOST_CHECK(r_empty < r_a2);
	BOOST_CHECK(r_a2 < r_b1);
}

//  Edge tests
BOOST_AUTO_TEST_CASE(edge_test)
{
	BOOST_TEST_MESSAGE("Edge test");

	std::string value1 = "concept";
	std::string tag1 = "tag1";
	std::string value2 = "relation";
	std::string tag2 = "tag2";

	auto tok1 = cgpp::Token(value1, tag1);
	cgpp::Concept c_a1 = cgpp::Concept(tok1);

	auto tok2 = cgpp::Token(value2, tag2);
	cgpp::Relation r_a1 = cgpp::Relation(tok2);

	auto ptr1 = std::make_shared<cgpp::Concept>(c_a1);
	auto ptr2 = std::make_shared<cgpp::Relation>(r_a1);

	cgpp::Edge e1{ptr1, ptr2};
	cgpp::Edge e2{ptr2, ptr1};

	BOOST_CHECK(e1 == e1);
    BOOST_CHECK(e2 == e2);
	BOOST_CHECK(e1 != e2);
    BOOST_CHECK(e2 != e1);

    cgpp::Edge e3 = e1;
    cgpp::Edge e4 = e2;
	BOOST_CHECK(e1 == e3);
    BOOST_CHECK(e2 == e4);
	BOOST_CHECK(e3 != e4);
}

// Construct a ConceptualGraph and use operators
BOOST_AUTO_TEST_CASE(graph_test)
{
    BOOST_TEST_MESSAGE("Conceptual Graph test");

	std::string value1 = "concept";
	std::string tag1 = "tag1";
	std::string value2 = "relation";
	std::string tag2 = "tag2";

	auto tok1 = cgpp::Token(value1, tag1);
	cgpp::Concept c_a1 = cgpp::Concept(tok1);
	auto tok2 = cgpp::Token(value2, tag2);
	cgpp::Relation r_a1 = cgpp::Relation(tok2);

	auto ptr1 = std::make_shared<cgpp::Concept>(c_a1);
	auto ptr2 = std::make_shared<cgpp::Relation>(r_a1);
	cgpp::Edge e1{ptr1, ptr2};
	cgpp::Edge e2{ptr2, ptr1};

    // TODO: construct a couple of graphs, add concepts, relations
    //       check them for equality, inequality, isomorphism
    // 
}

BOOST_AUTO_TEST_SUITE_END()
