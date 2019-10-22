#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "parse_csv.hpp"


using namespace std;


int main(int argc, char** argv)
{
	if (argc < 2) cout << "Usage : " << argv[0] << " <csv file> " << endl;
	else
	{
		auto data = csv(string(argv[1]));
		vector<string> b1 = data[1];
		vector<string> b2 = data[2];
		for(int i = 0; i!= b1.size(); ++i) cout << b1[i]+b2[i] << endl;
		//for (auto code : b1) cout << code << endl;
	}
}
