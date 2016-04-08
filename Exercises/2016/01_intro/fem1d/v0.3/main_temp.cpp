#include <vector>
#include <iostream>

#include "matrix.h"

using Uint=unsigned int;

int main(){
matrix M(3,2,5.6);
matrix MM(M);
for(auto i=0; i<M.get_nrows();++i){
	for(auto j=0; j<M.get_ncols();++j)
		std::cout<<M(i,j)<<" ";
	std::cout<<std::endl;
}

for(int i=0; i<MM.get_nrows();++i){
	for(int j=0; j<MM.get_ncols();++j)
		std::cout<<MM(i,j)<<" ";
	std::cout<<std::endl;
}

return 0;
}
