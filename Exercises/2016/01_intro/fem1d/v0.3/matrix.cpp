#include "matrix.hpp"

matrix::matrix(unsigned int nrows_=1, unsigned int ncols_=1):nrows(nrows_),ncols(ncols_){
	mat.reserve(nrows*ncols);
};

matrix::~matrix(){
		std::cout<<"destroying object of class matrix"<<std::endl;
	}
	
matrix::matrix matrix_transpose(matrix A){
	
}
