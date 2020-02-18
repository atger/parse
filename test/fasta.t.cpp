#define BOOST_TEST_MODULE Fasta
#include <boost/test/included/unit_test.hpp>
#include "fasta.hpp"


BOOST_AUTO_TEST_CASE(test1)
{
	Fasta record = Fasta(">header","ATATAT");
	BOOST_TEST(record.to_string() == ">header\nATATAT");
	BOOST_TEST(record.id() == ">header");
	BOOST_TEST(record.seq() == "ATATAT");
}
