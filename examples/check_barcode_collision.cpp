#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include "parse_csv.hpp"

using namespace std;
enum class Index { Single, Dual };

//auto get_barcodes(Index index_type, std::string sample_sheet);
int main(int argc, char** argv)
{
	if(argc < 2) cout << "Usage : " << argv[0] << " <sample sheet> " << endl;
	else
	{
		//auto data = csv(argv[1]);
		//vector<string> b1 = data[1];
		//auto [b1,data] = get_barcodes(Index::Single,string(argv[1]));
		//for (auto code : b1) cout << code << endl;
	}
}

std::pair< std::vector<std::string>, std::vector<std::vector<std::string>> >
get_barcodes(Index index_type, std::string sample_sheet)
{
	auto data = csv(sample_sheet);
	std::vector<std::string> index1, index2, barcodes;
	index1 = data[2];
	index2 = data[1];
	if (index_type == Index::Single)
		for ( auto val : index1) barcodes.push_back(val);
	else if (index_type == Index::Dual)
		for (int i = 0; i != index1.size(); ++i) barcodes.push_back(index1[i]+index2[i]);
	return std::make_pair(barcodes,data);
}
