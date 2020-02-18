#include <string>

class Fasta
{
	std::string header;
	std::string sequence;
	public:
	Fasta(std::string h, std::string s);
	std::string id();
	std::string seq();
	std::string to_string();
};
