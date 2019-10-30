#include <iostream>
#include <string>
#include "matrix.hpp"

using namespace std;
int main(int argc, char** argv)
{
	Matrix<string> m(4,4,string("as"));
	m.display();
}
