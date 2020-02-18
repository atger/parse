#include <iostream>
#include "seqio.hpp"

using namespace std;

int main(int argc, char ** argv)
{
	auto records = parse_seq_file<Fasta>(argv[1],"fasta");
	for(auto record : records)
		std::cout << record.seq() << std::endl;
}
