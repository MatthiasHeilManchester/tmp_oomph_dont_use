//LIC// ====================================================================
//LIC// This file forms part of oomph-lib, the object-oriented, 
//LIC// multi-physics finite-element library, available 
//LIC// at http://www.oomph-lib.org.
//LIC// 
//LIC//           Version 0.90. August 3, 2009.
//LIC// 
//LIC// Copyright (C) 2006-2009 Matthias Heil and Andrew Hazel
//LIC// 
//LIC// This library is free software; you can redistribute it and/or
//LIC// modify it under the terms of the GNU Lesser General Public
//LIC// License as published by the Free Software Foundation; either
//LIC// version 2.1 of the License, or (at your option) any later version.
//LIC// 
//LIC// This library is distributed in the hope that it will be useful,
//LIC// but WITHOUT ANY WARRANTY; without even the implied warranty of
//LIC// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//LIC// Lesser General Public License for more details.
//LIC// 
//LIC// You should have received a copy of the GNU Lesser General Public
//LIC// License along with this library; if not, write to the Free Software
//LIC// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
//LIC// 02110-1301  USA.
//LIC// 
//LIC// The authors may be contacted at oomph-lib@maths.man.ac.uk.
//LIC// 
//LIC//====================================================================
//Non-inline functions for gen Helmholtz elements
#include "generalised_helmholtz_elements.h"



namespace oomph
{

//======================================================================
/// Set the data for the number of Variables at each node, always two
/// (real and imag part) in every case
//======================================================================
 template<unsigned DIM, unsigned NNODE_1D>
 const unsigned QGeneralisedHelmholtzElement<DIM,NNODE_1D>::Initial_Nvalue = 2;


//======================================================================
/// Compute element residual Vector and/or element Jacobian matrix 
/// 
/// flag=1: compute both
/// flag=0: compute only residual Vector
///
/// Pure version without hanging nodes
//======================================================================
template <unsigned DIM>
void  GeneralisedHelmholtzEquations<DIM>::
fill_in_generic_residual_contribution_helmholtz(Vector<double> &residuals, 
                                                DenseMatrix<double> &jacobian, 
                                                const unsigned& flag) 
{
 //Find out how many nodes there are
 const unsigned n_node = nnode();

 //Set up memory for the shape and test functions
 Shape psi(n_node), test(n_node);
 DShape dpsidx(n_node,DIM), dtestdx(n_node,DIM);
 
 //Set the value of n_intpt
 const unsigned n_intpt = integral_pt()->nweight();
 
 //Integers to store the local equation and unknown numbers
 int local_eqn_real=0, local_unknown_real=0;
 int local_eqn_imag=0, local_unknown_imag=0;

 //Loop over the integration points
 for(unsigned ipt=0;ipt<n_intpt;ipt++)
  {
   //Get the integral weight
   double w = integral_pt()->weight(ipt);
   
   //Call the derivatives of the shape and test functions
   double J = dshape_and_dtest_eulerian_at_knot_helmholtz(ipt,psi,dpsidx,
                                                          test,dtestdx);
   
   //Premultiply the weights and the Jacobian
   double W = w*J;
   
   //Calculate local values of unknown
   //Allocate and initialise to zero
   std::complex<double> interpolated_u(0.0,0.0);
   Vector<double> interpolated_x(DIM,0.0);
   Vector< std::complex<double> > interpolated_dudx(DIM);
   
   //Calculate function value and derivatives:
   //-----------------------------------------
   // Loop over nodes
   for(unsigned l=0;l<n_node;l++) 
    {
     // Loop over directions
     for(unsigned j=0;j<DIM;j++)
      {
       interpolated_x[j] += raw_nodal_position(l,j)*psi(l);
      }
     
     //Get the nodal value of the helmholtz unknown
     const std::complex<double> 
      u_value(raw_nodal_value(l,u_index_helmholtz().real()),
              raw_nodal_value(l,u_index_helmholtz().imag()));

     //Add to the interpolated value
     interpolated_u += u_value*psi(l);
     
     // Loop over directions
     for(unsigned j=0;j<DIM;j++)
      {
       interpolated_dudx[j] += u_value*dpsidx(l,j);
      }
    }
   
   //Get source function
   //-------------------
   std::complex<double> source(0.0,0.0);
   get_source_helmholtz(ipt,interpolated_x,source);

   // Get the value of the soundspeed at the respective point
   double c(0.0); 
   get_c_helmholtz(ipt,interpolated_x,c);
   
   // Get the value of the absorption at the respective point
   double alpha(0.0); 
   get_alpha_helmholtz(ipt,interpolated_x,alpha);

   /// \short Use soundspeed, absorption and frequency 
   /// to precompute expressions to be subsequently used
   double c_squared = c * c;
   double alpha_squared = alpha * alpha;
   double omega_squared = omega() * omega();
   // First expression containing c, alpha and omega
   double cao_expr1 = 2.0 * c * alpha * omega();
   // Second expression containing c and alpha 
   double ca_expr2 = alpha_squared * c_squared;

   // Declare a vector of complex numbers for pml weights on the Laplace bit
   Vector< std::complex<double> > pml_stiffness_weight(DIM);
   // Declare a complex number for pml weights on the mass matrix bit
   std::complex<double> pml_mass_weight = std::complex<double>(1.0,0.0);

   // All the PML weights that participate in the assemby process 
   // are computed here. pml_stiffness_weight will contain the entries
   // for the Laplace bit, while pml_mass_weight contains the contributions
   // to the Helmholtz bit. Both default to 1.0, should the PML not be 
   // enabled via enable_pml.
   compute_pml_coefficients(ipt, interpolated_x, 
                            pml_stiffness_weight, 
                            pml_mass_weight); 

   // Assemble residuals and Jacobian
   //--------------------------------
   // Loop over the test functions
   for(unsigned l=0;l<n_node;l++)
    {

     // first, compute the real part contribution 
     //-------------------------------------------  
    
     //Get the local equation
     local_eqn_real = nodal_local_eqn(l,u_index_helmholtz().real());
     local_eqn_imag = nodal_local_eqn(l,u_index_helmholtz().imag());

     /*IF it's not a boundary condition*/
     if(local_eqn_real >= 0)
      {
       // Add body force/source term and Helmholtz bit    
       residuals[local_eqn_real] += 
        ( source.real() - ( 
           pml_mass_weight.real() * ( 
            (omega_squared-ca_expr2)*interpolated_u.real() - 
             cao_expr1 * interpolated_u.imag() ) 
          -pml_mass_weight.imag() * ( 
            (omega_squared-ca_expr2)*interpolated_u.imag() + 
             cao_expr1 * interpolated_u.real() ) 
        ) )*test(l)*W;
       
       // The Laplace bit
       for(unsigned k=0;k<DIM;k++)
        {
         residuals[local_eqn_real] += c_squared * (
          pml_stiffness_weight[k].real() * interpolated_dudx[k].real()
         -pml_stiffness_weight[k].imag() * interpolated_dudx[k].imag()
         )*dtestdx(l,k)*W;
        }
       
       // Calculate the jacobian
       //-----------------------
       if(flag)
        {
         //Loop over the velocity shape functions again
         for(unsigned l2=0;l2<n_node;l2++)
          { 
           local_unknown_real = nodal_local_eqn(l2,u_index_helmholtz().real());
           local_unknown_imag = nodal_local_eqn(l2,u_index_helmholtz().imag());

           //If at a non-zero degree of freedom add in the entry
           if(local_unknown_real >= 0)
            {
             //Add contribution to Elemental Matrix
             for(unsigned i=0;i<DIM;i++)
              {
               jacobian(local_eqn_real,local_unknown_real) 
                += c_squared * pml_stiffness_weight[i].real() 
                             * dpsidx(l2,i)*dtestdx(l,i)*W;
              }
             // Add the helmholtz contribution
             jacobian(local_eqn_real,local_unknown_real) 
              += (pml_mass_weight.imag() * cao_expr1 - 
                  pml_mass_weight.real() * (omega_squared -  ca_expr2)) 
                * psi(l2)*test(l)*W;
            }
           //If at a non-zero degree of freedom add in the entry
           if(local_unknown_imag >= 0)
            {
             //Add contribution to Elemental Matrix
             for(unsigned i=0;i<DIM;i++)
              {
               jacobian(local_eqn_real,local_unknown_imag) 
                -= c_squared * pml_stiffness_weight[i].imag() 
                             * dpsidx(l2,i)*dtestdx(l,i)*W;

              }
             // Add the helmholtz contribution
             jacobian(local_eqn_real,local_unknown_imag) 
              += (pml_mass_weight.real() * cao_expr1 + 
                  pml_mass_weight.imag() * (omega_squared -  ca_expr2)) 
                * psi(l2)*test(l)*W;
            }
          }
        }
      }
     
     // Second, compute the imaginary part contribution 
     //------------------------------------------------

     //Get the local equation
     local_eqn_imag = nodal_local_eqn(l,u_index_helmholtz().imag());
     local_eqn_real = nodal_local_eqn(l,u_index_helmholtz().real());

     /*IF it's not a boundary condition*/
     if(local_eqn_imag >= 0)
      {
       // Add body force/source term and Helmholtz bit
       residuals[local_eqn_imag] += 
        ( source.imag() - ( 
           pml_mass_weight.imag() * ( 
            (omega_squared-ca_expr2)*interpolated_u.real() - 
             cao_expr1 * interpolated_u.imag() ) 
         + pml_mass_weight.real() * ( 
            (omega_squared-ca_expr2)*interpolated_u.imag() + 
            cao_expr1 * interpolated_u.real() ) 
         ) )*test(l)*W;
       
       // The Laplace bit
       for(unsigned k=0;k<DIM;k++)
        {
         residuals[local_eqn_imag] += c_squared * (
               pml_stiffness_weight[k].imag() * interpolated_dudx[k].real()
              +pml_stiffness_weight[k].real() * interpolated_dudx[k].imag()   
         )*dtestdx(l,k)*W;
        }
       
       // Calculate the jacobian
       //-----------------------
       if(flag)
        {
         //Loop over the velocity shape functions again
         for(unsigned l2=0;l2<n_node;l2++)
          { 
           local_unknown_imag = nodal_local_eqn(l2,u_index_helmholtz().imag());
           local_unknown_real = nodal_local_eqn(l2,u_index_helmholtz().real());

           //If at a non-zero degree of freedom add in the entry
           if(local_unknown_imag >= 0)
            {
             //Add contribution to Elemental Matrix
             for(unsigned i=0;i<DIM;i++)
              {
               jacobian(local_eqn_imag,local_unknown_imag) 
                += c_squared * pml_stiffness_weight[i].real() 
                             * dpsidx(l2,i)*dtestdx(l,i)*W;
              }
             // Add the helmholtz contribution
             jacobian(local_eqn_imag,local_unknown_imag)
              += (pml_mass_weight.imag() * cao_expr1 - 
                  pml_mass_weight.real() * (omega_squared -  ca_expr2)) 
                * psi(l2)*test(l)*W;
            }
           if(local_unknown_real >= 0)
            {
             //Add contribution to Elemental Matrix
             for(unsigned i=0;i<DIM;i++)
              {
               jacobian(local_eqn_imag,local_unknown_real) 
                += c_squared * pml_stiffness_weight[i].imag() 
                             * dpsidx(l2,i)*dtestdx(l,i)*W;
              }
             // Add the helmholtz contribution
             jacobian(local_eqn_imag,local_unknown_real)
              += (-pml_mass_weight.real() * cao_expr1 - 
                   pml_mass_weight.imag() * (omega_squared -  ca_expr2)) 
                 * psi(l2)*test(l)*W;

            }
          }
        }
      }   
    }
  } // End of loop over integration points
}   

 
//======================================================================
/// Self-test:  Return 0 for OK
//======================================================================
template <unsigned DIM>
unsigned  GeneralisedHelmholtzEquations<DIM>::self_test()
{

 bool passed=true;

 // Check lower-level stuff
 if (FiniteElement::self_test()!=0)
  {
   passed=false;
  }

 // Return verdict
 if (passed)
  {
   return 0;
  }
 else
  {
   return 1;
  }
   
}


//======================================================================
/// Output function:
///
///   x,y,u_re,u_imag   or    x,y,z,u_re,u_imag
///
/// nplot points in each coordinate direction
//======================================================================
template <unsigned DIM>
void  GeneralisedHelmholtzEquations<DIM>::output(std::ostream &outfile, 
                                    const unsigned &nplot)
{

 //Vector of local coordinates
 Vector<double> s(DIM);
 
 // Tecplot header info
 outfile << tecplot_zone_string(nplot);
 
 // Loop over plot points
 unsigned num_plot_points=nplot_points(nplot);
 for (unsigned iplot=0;iplot<num_plot_points;iplot++)
  {
   
   // Get local coordinates of plot point
   get_s_plot(iplot,nplot,s);
   std::complex<double> u(interpolated_u_generalised_helmholtz(s));
   for(unsigned i=0;i<DIM;i++) 
    {
     outfile << interpolated_x(s,i) << " ";
    }
   outfile << u.real() << " " << u.imag() << std::endl;   
   
  }

 // Write tecplot footer (e.g. FE connectivity lists)
 write_tecplot_zone_footer(outfile,nplot);

}
 



//======================================================================
/// Output function for real part of full time-dependent solution
///
///  u = Re( (u_r +i u_i) exp(-i omega t)
///
/// at phase angle omega t = phi.
///
///   x,y,u   or    x,y,z,u
///
/// Output at nplot points in each coordinate direction
//======================================================================
template <unsigned DIM>
void  GeneralisedHelmholtzEquations<DIM>::output_real(std::ostream &outfile, 
                                           const double& phi,
                                           const unsigned &nplot)
{
 
 //Vector of local coordinates
 Vector<double> s(DIM);
 
 // Tecplot header info
 outfile << tecplot_zone_string(nplot);
 
 // Loop over plot points
 unsigned num_plot_points=nplot_points(nplot);
 for (unsigned iplot=0;iplot<num_plot_points;iplot++)
  {
   
   // Get local coordinates of plot point
   get_s_plot(iplot,nplot,s);
   std::complex<double> u(interpolated_u_generalised_helmholtz(s));
   for(unsigned i=0;i<DIM;i++) 
    {
     outfile << interpolated_x(s,i) << " ";
    }
   outfile << u.real()*cos(phi)+u.imag()*sin(phi) << std::endl;   
   
  }

 // Write tecplot footer (e.g. FE connectivity lists)
 write_tecplot_zone_footer(outfile,nplot);

}

//======================================================================
/// Output function for imaginary part of full time-dependent solution
///
///  u = Im( (u_r +i u_i) exp(-i omega t))
///
/// at phase angle omega t = phi.
///
///   x,y,u   or    x,y,z,u
///
/// Output at nplot points in each coordinate direction
//======================================================================
template <unsigned DIM>
void  GeneralisedHelmholtzEquations<DIM>::output_imag(std::ostream &outfile, 
                                           const double& phi,
                                           const unsigned &nplot)
{
 
 //Vector of local coordinates
 Vector<double> s(DIM);
 
 // Tecplot header info
 outfile << tecplot_zone_string(nplot);
 
 // Loop over plot points
 unsigned num_plot_points=nplot_points(nplot);
 for (unsigned iplot=0;iplot<num_plot_points;iplot++)
  {
   
   // Get local coordinates of plot point
   get_s_plot(iplot,nplot,s);
   std::complex<double> u(interpolated_u_generalised_helmholtz(s));
   for(unsigned i=0;i<DIM;i++) 
    {
     outfile << interpolated_x(s,i) << " ";
    }
   outfile << u.imag()*cos(phi)-u.real()*sin(phi) << std::endl;   
   
  }

 // Write tecplot footer (e.g. FE connectivity lists)
 write_tecplot_zone_footer(outfile,nplot);

}
 
 
//======================================================================
/// C-style output function:
///
///   x,y,u   or    x,y,z,u
///
/// nplot points in each coordinate direction
//======================================================================
template <unsigned DIM>
void  GeneralisedHelmholtzEquations<DIM>::output(FILE* file_pt,
                                    const unsigned &nplot)
{
 //Vector of local coordinates
 Vector<double> s(DIM);
 
 // Tecplot header info
 fprintf(file_pt,"%s",tecplot_zone_string(nplot).c_str());

 // Loop over plot points
 unsigned num_plot_points=nplot_points(nplot);
 for (unsigned iplot=0;iplot<num_plot_points;iplot++)
  {
   // Get local coordinates of plot point
   get_s_plot(iplot,nplot,s);
   std::complex<double> u(interpolated_u_generalised_helmholtz(s));

   for(unsigned i=0;i<DIM;i++) 
    {
     fprintf(file_pt,"%g ",interpolated_x(s,i));
    }

   for(unsigned i=0;i<DIM;i++) 
    {
     fprintf(file_pt,"%g ",interpolated_x(s,i));
    }
   fprintf(file_pt,"%g ",u.real());
   fprintf(file_pt,"%g \n",u.imag());

  }

 // Write tecplot footer (e.g. FE connectivity lists)
 write_tecplot_zone_footer(file_pt,nplot);
}



//======================================================================
 /// Output exact solution
 /// 
 /// Solution is provided via function pointer.
 /// Plot at a given number of plot points.
 ///
 ///   x,y,u_exact    or    x,y,z,u_exact
//======================================================================
template <unsigned DIM>
void GeneralisedHelmholtzEquations<DIM>::output_fct(std::ostream &outfile, 
                                       const unsigned &nplot, 
                  FiniteElement::SteadyExactSolutionFctPt exact_soln_pt)
{
 //Vector of local coordinates
 Vector<double> s(DIM);
  
  // Vector for coordintes
  Vector<double> x(DIM);
  
 // Tecplot header info
 outfile << tecplot_zone_string(nplot);
 
 // Exact solution Vector 
 Vector<double> exact_soln(2);
 
 // Loop over plot points
 unsigned num_plot_points=nplot_points(nplot);
 for (unsigned iplot=0;iplot<num_plot_points;iplot++)
  {
   
   // Get local coordinates of plot point
   get_s_plot(iplot,nplot,s);
   
   // Get x position as Vector
   interpolated_x(s,x);
   
   // Get exact solution at this point
   (*exact_soln_pt)(x,exact_soln);
   
   //Output x,y,...,u_exact
   for(unsigned i=0;i<DIM;i++)
    {
     outfile << x[i] << " ";
    }
   outfile << exact_soln[0] << " " <<  exact_soln[1] << std::endl;  
  }
 
 // Write tecplot footer (e.g. FE connectivity lists)
 write_tecplot_zone_footer(outfile,nplot);
}



//======================================================================
/// Output function for real part of full time-dependent fct
///
///  u = Re( (u_r +i u_i) exp(-i omega t)
///
/// at phase angle omega t = phi.
///
///   x,y,u   or    x,y,z,u
///
/// Output at nplot points in each coordinate direction
//======================================================================
template <unsigned DIM>
void GeneralisedHelmholtzEquations<DIM>::output_real_fct(
 std::ostream &outfile, 
 const double& phi,
 const unsigned &nplot, 
 FiniteElement::SteadyExactSolutionFctPt exact_soln_pt)
{
 //Vector of local coordinates
 Vector<double> s(DIM);
  
  // Vector for coordintes
  Vector<double> x(DIM);
  
 // Tecplot header info
 outfile << tecplot_zone_string(nplot);
 
 // Exact solution Vector 
 Vector<double> exact_soln(2);
 
 // Loop over plot points
 unsigned num_plot_points=nplot_points(nplot);
 for (unsigned iplot=0;iplot<num_plot_points;iplot++)
  {
   
   // Get local coordinates of plot point
   get_s_plot(iplot,nplot,s);
   
   // Get x position as Vector
   interpolated_x(s,x);
   
   // Get exact solution at this point
   (*exact_soln_pt)(x,exact_soln);
   
   //Output x,y,...,u_exact
   for(unsigned i=0;i<DIM;i++)
    {
     outfile << x[i] << " ";
    }
   outfile << exact_soln[0]*cos(phi)+ exact_soln[1]*sin(phi) << std::endl;  
  }
 
 // Write tecplot footer (e.g. FE connectivity lists)
 write_tecplot_zone_footer(outfile,nplot);
}

//======================================================================
/// Output function for imaginary part of full time-dependent fct
///
///  u = Im( (u_r +i u_i) exp(-i omega t))
///
/// at phase angle omega t = phi.
///
///   x,y,u   or    x,y,z,u
///
/// Output at nplot points in each coordinate direction
//======================================================================
template <unsigned DIM>
void GeneralisedHelmholtzEquations<DIM>::output_imag_fct(
 std::ostream &outfile, 
 const double& phi,
 const unsigned &nplot, 
 FiniteElement::SteadyExactSolutionFctPt exact_soln_pt)
{
 //Vector of local coordinates
 Vector<double> s(DIM);
  
  // Vector for coordintes
  Vector<double> x(DIM);
  
 // Tecplot header info
 outfile << tecplot_zone_string(nplot);
 
 // Exact solution Vector 
 Vector<double> exact_soln(2);
 
 // Loop over plot points
 unsigned num_plot_points=nplot_points(nplot);
 for (unsigned iplot=0;iplot<num_plot_points;iplot++)
  {
   
   // Get local coordinates of plot point
   get_s_plot(iplot,nplot,s);
   
   // Get x position as Vector
   interpolated_x(s,x);
   
   // Get exact solution at this point
   (*exact_soln_pt)(x,exact_soln);
   
   //Output x,y,...,u_exact
   for(unsigned i=0;i<DIM;i++)
    {
     outfile << x[i] << " ";
    }
   outfile << exact_soln[1]*cos(phi) - exact_soln[0]*sin(phi) << std::endl;  
  }
 
 // Write tecplot footer (e.g. FE connectivity lists)
 write_tecplot_zone_footer(outfile,nplot);
}




//======================================================================
 /// Validate against exact solution
 /// 
 /// Solution is provided via function pointer.
 /// Plot error at a given number of plot points.
 ///
//======================================================================
template <unsigned DIM>
void GeneralisedHelmholtzEquations<DIM>::compute_error(std::ostream &outfile, 
                       FiniteElement::SteadyExactSolutionFctPt exact_soln_pt,
                       double& error, double& norm)
{ 
 
 // Initialise
 error=0.0;
 norm=0.0;
 
 //Vector of local coordinates
 Vector<double> s(DIM);
 
 // Vector for coordintes
 Vector<double> x(DIM);
 
 //Find out how many nodes there are in the element
 unsigned n_node = nnode();
 
 Shape psi(n_node);
 
 //Set the value of n_intpt
 unsigned n_intpt = integral_pt()->nweight();
  
 // Tecplot 
 outfile << "ZONE" << std::endl;
 
 // Exact solution Vector 
 Vector<double> exact_soln(2);
 
 //Loop over the integration points
 for(unsigned ipt=0;ipt<n_intpt;ipt++)
  {
   
   //Assign values of s
   for(unsigned i=0;i<DIM;i++)
    {
     s[i] = integral_pt()->knot(ipt,i);
    }
   
   //Get the integral weight
   double w = integral_pt()->weight(ipt);
   
   // Get jacobian of mapping
   double J=J_eulerian(s);
   
   //Premultiply the weights and the Jacobian
   double W = w*J;
   
   // Get x position as Vector
   interpolated_x(s,x);
   
   // Get FE function value
   std::complex<double> u_fe=interpolated_u_generalised_helmholtz(s);
   
   // Get exact solution at this point
   (*exact_soln_pt)(x,exact_soln);
   
   //Output x,y,...,error
   for(unsigned i=0;i<DIM;i++)
    {
     outfile << x[i] << " ";
    }
   outfile << exact_soln[0] << " "  << exact_soln[1] << " " 
           << exact_soln[0]-u_fe.real() << " " << exact_soln[1]-u_fe.imag() 
           << std::endl;  
   
   // Add to error and norm
   norm+=(exact_soln[0]*exact_soln[0]+exact_soln[1]*exact_soln[1])*W;
   error+=( (exact_soln[0]-u_fe.real())*(exact_soln[0]-u_fe.real())+
            (exact_soln[1]-u_fe.imag())*(exact_soln[1]-u_fe.imag()) )*W;
   
  }
}




//======================================================================
 /// Compute norm of fe solution
//======================================================================
template <unsigned DIM>
void GeneralisedHelmholtzEquations<DIM>::compute_norm(double& norm)
{ 
 
 // Initialise
 norm=0.0;
 
 //Vector of local coordinates
 Vector<double> s(2);
 
 // Vector for coordintes
 Vector<double> x(2);
 
 //Find out how many nodes there are in the element
  unsigned n_node = nnode();
  
  Shape psi(n_node);
  
  //Set the value of n_intpt
  unsigned n_intpt = integral_pt()->nweight();
  
  //Loop over the integration points
  for(unsigned ipt=0;ipt<n_intpt;ipt++)
   {
    
    //Assign values of s
    for(unsigned i=0;i<2;i++)
     {
      s[i] = integral_pt()->knot(ipt,i);
     }
    
    //Get the integral weight
    double w = integral_pt()->weight(ipt);
    
    // Get jacobian of mapping
    double J=J_eulerian(s);
    
    //Premultiply the weights and the Jacobian
    double W = w*J;
    
    // Get FE function value
    std::complex<double> u_fe=interpolated_u_generalised_helmholtz(s);
    
    // Add to  norm
    norm+=(u_fe.real()*u_fe.real()+u_fe.imag()*u_fe.imag())*W;
    
   }
 }
 
//====================================================================
// Force build of templates
//====================================================================
template class GeneralisedHelmholtzEquations<1>;
template class GeneralisedHelmholtzEquations<2>;
template class GeneralisedHelmholtzEquations<3>;

template class QGeneralisedHelmholtzElement<1,2>;
template class QGeneralisedHelmholtzElement<1,3>;
template class QGeneralisedHelmholtzElement<1,4>;

template class QGeneralisedHelmholtzElement<2,2>;
template class QGeneralisedHelmholtzElement<2,3>;
template class QGeneralisedHelmholtzElement<2,4>;

template class QGeneralisedHelmholtzElement<3,2>;
template class QGeneralisedHelmholtzElement<3,3>;
template class QGeneralisedHelmholtzElement<3,4>;

}
