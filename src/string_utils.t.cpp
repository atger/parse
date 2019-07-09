#include <iostream>
#include "string_utils.hpp"
using namespace std;

int main()
{
	StringUtils su("ATTGAGCAGT");
	vector<string> vec = su.split_by(' ');
	cout << su.to_string() << endl;
        cout << su.reverse_complement() << endl;
}
