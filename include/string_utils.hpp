#include <string>
#include <vector>

class StringUtils 
{
	std::string text;
	public:
        StringUtils(std::string& str) { text=str; }
	std::vector<std::string> split_by(char delim);
	std::string reverse_complement();
	std::string to_string();
};

