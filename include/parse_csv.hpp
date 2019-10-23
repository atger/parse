#include <vector>
#include <string>


class csv
{
	std::vector<std::vector<std::string>> data;
	public:
	csv(std::string filename, int skip_rows = 0);
	std::vector<std::string> operator[](int i);
	~csv();
};


