#include <map>
#include <sstream>
#include <algorithm>
#include "string_utils.hpp"

std::vector<std::string> StringUtils::split_by(char delim)
{
	std::vector<std::string> words;
        std::istringstream str(text);
        while(str)
	{
		std::string word;
		std::getline(str,word,delim);
		words.push_back(word);
	}
	return words;
}

std::string StringUtils::reverse_complement()
{
	std::reverse(text.begin(),text.end());
        std::map<char,char> comp = {{'A','T'},{'T','A'},{'C','G'},{'G','C'}};
        std::string rc = "";
        for(auto c : text)
            rc += comp[c];
        return rc;
}

std::string StringUtils::to_string()
{
	return text;
}
