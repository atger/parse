#include <string>

class Fastq
{
	std::string header;
	std::string sequence;
	std::string optional;
	std::string quality;
	public:
	Fastq(std::string h, std::string s, std::string o, std::string q);
	std::string id();
	std::string seq();
	std::string qual();
	std::string to_string();
};
