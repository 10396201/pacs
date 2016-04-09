#include "test_solve.h"
#include <iostream>

using namespace Eigen

int main ()
{
  
  matrix A (10);
  matrix rhs (10, 1);
  typedef Matrix<double, Dynamic, Dynamic> MatrixType;
  typedef Map<MatrixType> MapType;
  typedef Map<const MatrixType> MapTypeConst;
  
  for (unsigned int i = 0; i < 10; ++i)
    {
      rhs (i, 0) = 1.;
      for (unsigned int j = 0; j < 10; ++j)
        {
          if (j+1 == i)
            A(i, j) = -1.;
          else if (j == i+1)
            A(i, j) = -1.;
          else if (i == j)
            A(i, j) = 2.;
        }
    }
  
  MatrixType m1(A.get_rows(),A.get_cols());

  MapType m2map(A.get_data(),m1.size());
  MapTypeConst m2mapconst(A.get_data(), m1.size())
  
  matrix uh (rhs);
  
  MatrixType uh(uh.get_rows(), uh.get_cols());
  
  MapType uh2map(uh.get_data(), uh.size());
  MapTypeConst uh2mapconst(uh.get_data(), uh.size());
  
  
  
  matrix f = A * uh;
  
  for (unsigned int i = 0; i < 10; ++i)
    {
      std::cout << "x (" << i+1 << ") = " << uh(i, 0) << ";"        
                << "    y (" << i+1 << ") = " << f(i, 0) << ";"
                << "    b (" << i+1 << ") = " << rhs(i, 0) << ";"
                << std::endl;
    }
  return 0;
}

