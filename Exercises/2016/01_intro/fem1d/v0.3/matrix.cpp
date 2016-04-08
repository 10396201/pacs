#include "matrix.h"

matrix::matrix(const unsigned int nrows_, const unsigned int ncols_, const double init_val):nrows(nrows_), ncols(ncols_){
	mat.reserve(nrows*ncols);
	if(init_val)
		std::fill(mat.begin(), mat.begin()+nrows*ncols, init_val);
}

matrix::~matrix(){
	std::cout<<"Deleting an object of class matrix"<<std::endl;
}

matrix matrix::matrix_transpose(matrix &A){
	const unsigned int rows=get_ncols();
	const unsigned int cols=get_nrows();
	
	matrix B(rows,cols);
	
	for(unsigned int i=0; i<nrows; ++i)
		for(unsigned int j=0; j<ncols; ++j)
			B(j,i)=A(i,j);
	return B;
}


