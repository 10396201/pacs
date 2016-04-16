#include <iostream> // input output
#include <cmath> // (for sqrt)
#include <vector>
#include <tuple>
#include<string>

#include "readParameters.hpp"
#include "GetPot.hpp"
#include "gnuplot-iostream.hpp"// interface with gnuplot
/*!
  @file main.cpp
  @brief Temperature distribution in a 1D bar.

  @detail
    We solve  \f$ -T^{\prime\prime}(x)+act*(T(x)-T_e)=0, 0<x<L \f$ with 
    boundary conditions \f$ T(0)=To; T^\prime(L)=0\f$
    
    **************************************************
    Linear finite elements
    Iterative resolution by Gauss Seidel.
    **************************************************
    
    Example adapted by Luca Formaggia from  a code found in 
    "Simulation numerique an C++" di I. Danaila, F. Hecht e
    O. Pironneau.
*/
//! helper function
void printHelp()
{
  std::cout<<"USAGE: main [-h] [-v] -p parameterFile (default: parameters.pot)"<<std::endl;
  std::cout<<"-h this help"<<std::endl;
  std::cout<<"-v verbose output"<<std::endl;
}

//! main program
int main(int argc, char** argv)
{
  using namespace std; // avoid std::
  int status(0); // final program status
  GetPot   cl(argc, argv);
  if( cl.search(2, "-h", "--help") )
    {
      printHelp();
      return 0;
    }
  // check if we want verbosity
  bool verbose=cl.search(1,"-v");
  // Get file with parameter values
  string filename = cl.follow("parameters.pot","-p");
  cout<<"Reading parameters from "<<filename<<std::endl;
  // read parameters
  const parameters param=readParameters(filename,verbose);
  // Transfer parameters to local variables
  // I use references to save memory (not really an issue here, it is just
  // to show a possible  use of references)
  const int&    itermax= param.itermax;   //max number of iteration for Gauss-Siedel
  const double& toler=param.toler;   // Tolerance for stopping criterion
  // Here I use auto (remember that you need const and & if you want constant references)
  const auto& L= param.L;  // Bar length
  const auto& a1=param.a1; // First longitudinal dimension
  const auto& a2=param.a2; //  Second longitudinal dimension
  const auto& To=param.To; // Dirichlet condition
  const auto& Te=param.Te; // External temperature (Centigrades)
  const auto& k=param.k;  // Thermal conductivity
  const auto& hc=param.hc; // Convection coefficient
  const auto& M=param.M; // Number of grid elements
  
  const string output_filename = param.output_filename;
  const auto& whatout=param.whatout;
  const auto& stop_crit=param.stop_crit;
  
  //! Precomputed coefficient for adimensional form of equation
  const auto act=2.*(a1+a2)*hc*L*L/(k*a1*a2);

  // mesh size
  const auto h=1./M;
  
  // Solution vector
  std::vector<double> theta(M+1);
  
  // Gauss Siedel is initialised with a linear variation
  // of T
  
  for(auto m=0;m <= M;++m)
     theta[m]=(1.-m*h)*(To-Te)/Te;
  
  // Gauss-Seidel
  // epsilon= x^{k+1}-x^{k}
  // Stopping criteria err <=toler 
  // err is computed through R^n norm or L^2 norm or H^1 norm (set this in parameters.pot) 
  //R^n: err=sqrt(sum(epsilon*epsilon))
  //L^2: err=sqrt(h*err_Rn)
  //H^1: err=err_L2+sqrt(h*sum((epsilon(k)-epsilon(k-1))/h*(epsilon(k)-epsilon(k-1))/h))=err_L2+sqrt(1/h*sum((epsilon(k)-epsilon(k-1))*(epsilon(k)-epsilon(k-1)))
  
  int iter=0;
  double xnew, epsilon, prev_epsilon, grad_epsilon, err=0., err_Rn=0., err_L2=0., err_H1=0.;
     do
       { err_Rn=0.;
       	 prev_epsilon=0.; //in the first node the solution is exact
       	 grad_epsilon=0.;

	 // first M-1 row of linear system
         for(int m=1;m < M;m++)
         {   
	   xnew  = (theta[m-1]+theta[m+1])/(2.+h*h*act);
	   epsilon=xnew-theta[m];
	   grad_epsilon+=(epsilon-prev_epsilon)*(epsilon-prev_epsilon);
	   err_Rn += epsilon*epsilon;
	   prev_epsilon=epsilon;
	   theta[m] = xnew;
         }

	 //Last row
	 xnew = theta[M-1]; 
	 epsilon=xnew-theta[M];
	 grad_epsilon+=(epsilon-prev_epsilon)*(epsilon-prev_epsilon);
	 err_Rn += epsilon*epsilon;
	 theta[M]=  xnew; 

	 iter=iter+1;   
	 
	 err_L2=sqrt(err_Rn*h);  
	 err_H1=err_L2+sqrt(1./h*grad_epsilon);
	 err_Rn=sqrt(err_Rn);
	 
	 switch(stop_crit){
	 	case 1: {err=err_H1;}
	 	case 2: {err=err_L2;}
	 	case 3: {err=err_Rn;}
	 }   
       }while((err > toler) && (iter < itermax) );

    if(iter<itermax)
      cout << "M="<<M<<"  Convergence in "<<iter<<" iterations"<<endl;
    else
      {
	cerr << "NOT CONVERGING in "<<itermax<<" iterations "<<
	  "||dx||="<<err<<endl;
	status=1;
      }

 // Analitic solution

    vector<double> thetaa(M+1);
     for(int m=0;m <= M;m++)
       thetaa[m]=Te+(To-Te)*cosh(sqrt(act)*(1-m*h))/cosh(sqrt(act));

    
    switch(whatout){
    	case 1:      {//only graphic
    		     // writing results with format
     		     // x_i u_h(x_i) u(x_i) and lauch gnuplot 

     		     Gnuplot gp;
     		     std::vector<double> coor(M+1);
     		     std::vector<double> sol(M+1);
     		     std::vector<double> exact(M+1);
     		     //fill the vectors
     		     for(int m = 0; m<= M; m++)
       			{ 
	 			std::tie(coor[m],sol[m],exact[m])=std::make_tuple(m*h*L,Te*(1.+theta[m]),thetaa[m]);
       			}
    		     // Using temporary files (another nice use of tie)
     		     gp<<"plot"<<gp.file1d(std::tie(coor,sol))<<"w lp title 'uh',"<< gp.file1d(std::tie(coor,exact))<<"w l title 'uex'"<<std::endl;
       		     break;}
       	case 2:      {//only data file
       		     cout<<"Result file: "<<output_filename<<endl;
    		     ofstream f(output_filename);
    		     std::vector<double> coor(M+1);
     		     std::vector<double> sol(M+1);
     		     std::vector<double> exact(M+1);
     		     for(int m = 0; m<= M; m++)
       			{
	 			// \t writes a tab 
         			f<<m*h*L<<"\t"<<Te*(1.+theta[m])<<"\t"<<thetaa[m]<<endl;
	 			// An example of use of tie and tuples!
         
	 			std::tie(coor[m],sol[m],exact[m])=std::make_tuple(m*h*L,Te*(1.+theta[m]),thetaa[m]);
       			}
     		     f.close();
     		     break;}
    	case 3:      {// Graphic + data file
     		     Gnuplot gp;
     		     std::vector<double> coor(M+1);
     		     std::vector<double> sol(M+1);
     		     std::vector<double> exact(M+1);
     		     
     		     cout<<"Result file: "<<output_filename<<endl;
    		     ofstream f(output_filename);
     		     for(int m = 0; m<= M; m++)
       			{
	 			// \t writes a tab 
         			f<<m*h*L<<"\t"<<Te*(1.+theta[m])<<"\t"<<thetaa[m]<<endl;
	 			// An example of use of tie and tuples!
	 			std::tie(coor[m],sol[m],exact[m])=std::make_tuple(m*h*L,Te*(1.+theta[m]),thetaa[m]);
       			}
     		     f.close();
    		     // Using temporary files (another nice use of tie)
     		     gp<<"plot"<<gp.file1d(std::tie(coor,sol))<<"w lp title 'uh',"<< gp.file1d(std::tie(coor,exact))<<"w l title 'uex'"<<std::endl;
     		     break;}
    }     


     return status;
}
