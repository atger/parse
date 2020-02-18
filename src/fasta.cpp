#include "fasta.hpp"


Fasta::Fasta(std::string h ,std::string s)
{
	header = h;
	sequence = s;
}

std::string Fasta::id()
{
	return header;
}

std::string Fasta::seq()
{
	return sequence;
}

std::string Fasta::to_string()
{
	return header+"\n"+sequence;
}
