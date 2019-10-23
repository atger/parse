#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include "parse_csv.hpp"

using namespace std;
enum class Index { Single, Dual };

using Matrix = std::vector<std::vector<int>>;
using Indices = std::vector<std::pair<int,int>>;

std::pair< std::vector<std::string>,csv> get_barcodes(Index index_type, std::string sample_sheet);
int mismatch_count(std::string barcode1, std::string barcode2);
std::vector<std::vector<int>> build_score_matrix(std::vector<std::string> barcodes);
bool is_matrix_symmetric( std::vector<std::vector<int>> mat);
std::vector<std::pair<int,int>> get_clashed_positions(Matrix mat);
std::vector<std::string> get_clashed_barcodes(csv data,Indices positions,Index index_type);

int main(int argc, char** argv)
{
	if(argc < 2) cout << "Usage : " << argv[0] << " <sample sheet> " << endl;
	else
	{
		auto [b1,data] = get_barcodes(Index::Single,string(argv[1]));
		cout << mismatch_count(b1[0],b1[2]) << endl;
		auto scores = build_score_matrix(b1);
		auto positions = get_clashed_positions(scores);
		auto clashed_barcodes = get_clashed_barcodes(data,positions,Index::Single);
		for (auto clashes :  clashed_barcodes) cout << clashes << endl;
	}
}

std::pair< std::vector<std::string>, csv >
get_barcodes(Index index_type, std::string sample_sheet)
{
	auto data = csv(sample_sheet, 5);
	std::vector<std::string> index1, index2, barcodes;
	index1 = data[2];
	index2 = data[1];
	if (index_type == Index::Single)
		for ( auto val : index1) barcodes.push_back(val);
	else if (index_type == Index::Dual)
		for (int i = 0; i != index1.size(); ++i) barcodes.push_back(index1[i]+index2[i]);
	return std::make_pair(barcodes,data);
}

int mismatch_count(std::string barcode1, std::string barcode2)
{
	int count = 0;
	for(int i = 0; i!= barcode1.length();++i)
		if (barcode1[i] != barcode2[i])
			count += 1;
	return count;
}

std::vector<std::vector<int>> build_score_matrix(std::vector<std::string> barcodes)
{
	int dim = barcodes.size();
	std::vector<std::vector<int>> mat(dim,std::vector<int>(dim));
	for(int i = 0; i != dim; ++i)
		for(int j = 0; j != dim; ++j)
			mat[i][j] = mismatch_count(barcodes[i],barcodes[j]);
	return mat;
}

bool is_matrix_symmetric( std::vector<std::vector<int>> mat)
{
	int x = 0;
	int dim = mat.size();
	for(int i=0; i!= dim; ++i)
		for(int j=0; j != dim; ++j)
			if (mat[i][j] != mat[j][i])
				x = 1;
	return x==0 ? true:false;
}

std::vector<std::pair<int,int>> get_clashed_positions(Matrix mat)
{
	std::vector<std::pair<int,int>> clash_positions;
	int dim = mat.size();
	for(int i=0; i!=dim; ++i)
		for(int j=0; j!=dim; ++j)
			if (i < j && mat[i][j] <= 2)
				clash_positions.push_back(make_pair(i,j));
	return clash_positions;
}

std::vector<std::string> get_clashed_barcodes(csv data,Indices positions,Index index_type)
{
	std::vector<std::string> messages {};
	for(auto pos : positions)
	{
		if (index_type == Index::Single)
		{
			std::string first = data[2][pos.first];
			std::string second = data[2][pos.second];
			std::string msg = "Barcode "+to_string(pos.first)+": "+first+" and Barcode "+to_string(pos.second)+": "+second;
			messages.push_back(msg);
		} else if (index_type == Index::Single)
		{
			std::string first = data[2][pos.first]+"+"+data[3][pos.first];
			std::string second = data[2][pos.second]+"+"+data[3][pos.second];
			std::string msg = "Barcode "+to_string(pos.first)+": "+first+" and Barcode "+to_string(pos.second)+": "+second;
			messages.push_back(msg);
		}

	}
	return messages;
}
