#include <iostream>
#include <string>
#include "matrix.hpp"

using namespace std;
class Record 
{ 
	std::string value;
	public:
	Record(std::string str) {value = str; }
	~Record() {}
	friend ostream& operator <<(ostream& os,const Record& r);
};

ostream& operator <<(ostream& os, const Record & r)
{
	os << r.value ;
	return os;
}

int main(int argc, char** argv)
{
	Record m1("valuesant");
	Matrix<Record> m(4,4,m1);
	m.display();
}
