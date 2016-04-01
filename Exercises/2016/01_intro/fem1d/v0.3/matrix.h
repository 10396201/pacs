#ifndef H_MATRIX_H
#define H_MATRIX_H

#include <vector>

class matrix{
	unsigned int nrows;
	unsigned int ncols;
	
	std::vector<double> mat;
	
	//default constructor
	matrix(const unsigned int nrows_=1, const unsigned int ncols_=1);
	
	//default destructor
	~matrix();
	
	//index. controlla: accedi per colonna, è più veloce
	inline unsigned int index(const unsigned int i, const unsigned int j){return i*ncols+j;}
	
	//overloading of []
	
	
	public:
	//get_nrows
	inline unsigned int get_nrows(){return nrows;}
	
	//get_ncols
	inline unsigned int get_ncols(){return ncols;}
	
	
	//matrix transpose
	matrix matrix_transpose(matrix A);
	
	//matrix product
	
	//matrix sum
	
	//gauss-seidel to solve a linear system
	

}
