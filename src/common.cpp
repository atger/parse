#include <map>
#include <algorithm>
#include "common.hpp"


std::vector<std::string> split(std::string line,char delim)
{
	std::vector<std::string> words;
	std::istringstream line_stream(line);
	while(line_stream)
	{
		std::string word;
		getline(line_stream,word,delim);
		words.push_back(word);
	}
	return words;

}


std::string reverse_complement(std::string dna_string)
{
        std::reverse(dna_string.begin(),dna_string.end());
        std::map<char,char> comp = {{'A','T'},{'T','A'},{'C','G'},{'G','C'}};
        std::string rc = "";
        for(auto c : dna_string)
            rc += comp[c];
        return rc;
}

