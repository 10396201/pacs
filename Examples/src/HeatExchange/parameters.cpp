#include <iostream>
#include "parameters.hpp"
std::ostream & operator << (std::ostream & out,const parameters & p)
{
  out<<"PARAMETER VALUES:"<<"\n";
  out<<"itermax= "<<p.itermax<<"\n";
  out<<"toler= "<<p.toler<<"\n";
  out<<"L= "<<p.L<<"\n";
  out<<"a1= "<<p.a1<<"\n";
  out<<"a2= "<<p.a2<<"\n";
  out<<"To= "<<p.To<<"\n";
  out<<"Te= "<<p.Te<<"\n";
  out<<"k= "<<p.k<<"\n";
  out<<"hc= "<<p.hc<<"\n";
  out<<"M= "<<p.M<<"\n";
  out<<"output_filename= "<<p.output_filename<<"\n";
  
  switch(p.whatout){
	 	case 1: {out<<"Results in a graphic on the screen"<<"\n";}
	 	case 2: {out<<"Results in a .dat file"<<"\n";}
	 	case 3: {out<<"Results in a graphic on the screen and in a .dat file"<<"\n";}
	 }   
  
  
   switch(p.stop_crit){
	 	case 1: {out<<"Stopping criterion: H^1 norm of the increment"<<"\n\n";}
	 	case 2: {out<<"Stopping criterion: L^2 norm of the increment"<<"\n\n";}
	 	case 3: {out<<"Stopping criterion: R^n norm of the increment"<<"\n\n";}
	 }
  return out;
}
