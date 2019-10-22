#include <fstream>
#include "common.hpp"
#include "parse_csv.hpp"



csv::csv(std::string filename)
{
        std::ifstream file(filename);
        std::string line;
        while(getline(file,line)){
                if (!line.empty())
                {
                        std::vector<std::string> columns = split(line,',');
                        data.push_back(columns);
                }
        }
}


csv::~csv()
{
}

std::vector<std::string> csv::operator[](int i)
{
	std::vector<std::string> column_data;
	for (auto row : data)
		column_data.push_back(row[i]);
	return column_data;
}
