#ifndef H_MATRIX_H
#define H_MATRIX_H

#include <vector>
#include <iostream>
#include <algorithm>

class matrix{
	unsigned int nrows;
	unsigned int ncols;
	
	std::vector<double> mat;
	
	public:
	//default constructor
	matrix(const unsigned int nrows_=1, const unsigned int ncols_=1, const double init_val=0);
	
	//copy constructor
	matrix(matrix const &)=default;
	
	//default destructor
	~matrix();
	
	//overloading of () : 2 indices
	double& operator() (const unsigned int i, const unsigned int j){return mat[j*nrows+i];};
	
	//overloading of [] : 1 index
	double& operator[] (const unsigned int i){return mat[i];};
	
	//get_nrows
	unsigned int get_nrows(){return nrows;};
	
	//get_ncols
	unsigned int get_ncols(){return ncols;};
	
	//get_vect
	std::vector<double> get_vect(){return mat;};
	
	
	//matrix transpose
	matrix matrix_transpose(matrix &A);
	
	//matrix product
	
	//matrix sum
	
	//gauss-seidel to solve a linear system
};
#endif
