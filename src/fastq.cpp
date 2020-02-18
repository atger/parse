#include "fastq.hpp"


Fastq::Fastq(std::string h ,std::string s, std::string o, std::string q)
{
	header = h;
	sequence = s;
	optional = o;
	quality = q;
}

std::string Fastq::id()
{
	return header;
}

std::string Fastq::seq()
{
	return sequence;
}

std::string Fastq::qual()
{
	return quality;
}

std::string Fastq::to_string()
{
	return header+"\n"+sequence+"\n"+optional+"\n"+quality;
}
