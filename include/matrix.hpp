#include <iostream>
#include <vector>

//===--------------matrix.h---Matrix class definition-----------===//
//
// Part of parse library to compute matrix operations.
//
//===----------------------------------------------------------===//

template <typename T>
class Matrix
{
	std::vector<std::vector<T>> Mat;
	public:
	Matrix(int x,int y, T val);
	~Matrix();
	void display();
};

template<typename T>
Matrix<T>::Matrix(int x, int y, T val)
{
	std::vector<T> temp(x,val);
	for(int i = 0; i != y; ++i)
		Mat.push_back(temp);
}

template<typename T>
Matrix<T>::~Matrix()
{
}

template<typename T>
void Matrix<T>::display()
{
	for(auto vec : Mat)
	{
		for(auto x: vec)
			std::cout << x << " ";
		std::cout << std::endl;
	}
}
