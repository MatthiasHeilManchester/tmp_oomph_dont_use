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
//Header file for FoepplvonKarman elements
#ifndef OOMPH_FOEPPLVONKARMAN_ELEMENTS_HEADER
#define OOMPH_FOEPPLVONKARMAN_ELEMENTS_HEADER


// Config header generated by autoconfig
#ifdef HAVE_CONFIG_H
  #include <oomph-lib-config.h>
#endif

#include<sstream>

//OOMPH-LIB headers
// hierher
//#include "generic.h"

#include "../generic/projection.h"
#include "../generic/nodes.h"
#include "../generic/Qelements.h"
#include "../generic/oomph_utilities.h"



namespace oomph
{

//=============================================================
/// A class for all isoparametric elements that solve the
/// Foeppl von Karman equations.
/// \f[
/// \nabla^4 w - \eta\Diamond^4(w,\phi) = \lambda p(x,y)
/// \f]
/// and
/// \f[
/// \nabla^4 \phi + \frac{1}{2}\Diamond^4(w,w) = 0
/// \f]
/// This contains the generic maths. Shape functions, geometric
/// mapping etc. must get implemented in derived class.
//=============================================================

class FoepplvonKarmanEquations : public virtual FiniteElement
{

public:

 /// \short Function pointer to pressure function fct(x,f(x)) --
 /// x is a Vector!
 typedef void (*FoepplvonKarmanPressureFctPt)(
   const Vector<double>& x,
   double& f);


 /// \short Function pointer to gradient of pressure function fct(x,g(x)) --
 /// x is a Vector!
 typedef void (*FoepplvonKarmanPressureFctGradientPt)(
   const Vector<double>& x,
   Vector<double>& gradient);


 /// Constructor (must initialise the Pressure_fct_pt to null)
 /// Also set physical parameters to their default values
 FoepplvonKarmanEquations() : Pressure_fct_pt(0),
                              Pressure_fct_gradient_pt(0),
                              qPressure_fct_pt(0)
  {
   //Set all the physical constants to the default value (zero)
   Eta_pt = &Default_Physical_Constant_Value;
   Lambda_pt = &Default_Physical_Constant_Value;
  }

 /// Broken copy constructor
 FoepplvonKarmanEquations(const FoepplvonKarmanEquations& dummy)
  {
   BrokenCopy::broken_copy("FoepplvonKarmanEquations");
  }

 /// Broken assignment operator
 void operator=(const FoepplvonKarmanEquations&)
  {
   BrokenCopy::broken_assign("FoepplvonKarmanEquations");
  }

 // Access functions for the physical constants

 /// Eta
 const double &eta() const {return *Eta_pt;}

 /// Pointer to eta
 double* &eta_pt() {return Eta_pt;}

 /// Lambda
 const double &lambda() const {return *Lambda_pt;}

 /// Pointer to lambda
 double* &lambda_pt() {return Lambda_pt;}

 /// \short Return the index at which the i-th unknown value
 /// is stored. The default value, i, is appropriate for single-physics
 /// problems. By default, these are:
 /// 0: w
 /// 1: laplacian w
 /// 2: phi
 /// 3: laplacian phi
 /// 4-8: smooth first derivatives
 /// In derived multi-physics elements, this function should be overloaded
 /// to reflect the chosen storage scheme. Note that these equations require
 /// that the unknown is always stored at the same index at each node.
 virtual inline unsigned nodal_index_fvk(unsigned i=0) const {return i;}

 /// Output with default number of plot points
 void output(std::ostream &outfile)
  {
   const unsigned n_plot=5;
   output(outfile,n_plot);
  }

 /// \short Output FE representation of soln: x,y,w at
 /// n_plot^DIM plot points
 void output(std::ostream &outfile, const unsigned &n_plot);

 /// C_style output with default number of plot points
 void output(FILE* file_pt)
  {
   const unsigned n_plot=5;
   output(file_pt,n_plot);
  }

 /// \short C-style output FE representation of soln: x,y,w at
 /// n_plot^DIM plot points
 void output(FILE* file_pt, const unsigned &n_plot);

 /// Output exact soln: x,y,w_exact at n_plot^DIM plot points
 void output_fct(std::ostream &outfile, const unsigned &n_plot,
                 FiniteElement::SteadyExactSolutionFctPt exact_soln_pt);

 /// \short Output exact soln: x,y,w_exact at
 /// n_plot^DIM plot points (dummy time-dependent version to
 /// keep intel compiler happy)
 virtual void output_fct(std::ostream &outfile, const unsigned &n_plot,
                         const double& time,
                         FiniteElement::UnsteadyExactSolutionFctPt
                         exact_soln_pt)
  {
   throw OomphLibError(
    "There is no time-dependent output_fct() for Foeppl von Karman"
    "elements ",
    "FoepplvonKarmanEquations<DIM>::output_fct()",
    OOMPH_EXCEPTION_LOCATION);
  }


 /// Get error against and norm of exact solution
 void compute_error(std::ostream &outfile,
                    FiniteElement::SteadyExactSolutionFctPt exact_soln_pt,
                    double& error, double& norm);


 /// Dummy, time dependent error checker
 void compute_error(std::ostream &outfile,
                    FiniteElement::UnsteadyExactSolutionFctPt exact_soln_pt,
                    const double& time, double& error, double& norm)
  {
   throw OomphLibError(
    "There is no time-dependent compute_error() for Foeppl von Karman"
    "elements",
    "FoepplvonKarmanEquations<DIM>::compute_error()",
    OOMPH_EXCEPTION_LOCATION);
  }

 /// Access function: Pointer to pressure function
 FoepplvonKarmanPressureFctPt& pressure_fct_pt() {return Pressure_fct_pt;}

 /// Access function: Pointer to pressure function. Const version
 FoepplvonKarmanPressureFctPt pressure_fct_pt() const
  {return Pressure_fct_pt;}

 /// Access function: Pointer to gradient of pressure function
 FoepplvonKarmanPressureFctGradientPt& pressure_fct_gradient_pt()
  {return Pressure_fct_gradient_pt;}

 /// Access function: Pointer to gradient pressure function. Const version
 FoepplvonKarmanPressureFctGradientPt pressure_fct_gradient_pt() const
  {return Pressure_fct_gradient_pt;}

 //mjr Ridicu-hack for made-up second pressure, q
 /// Access function: Pointer to pressure function
 FoepplvonKarmanPressureFctPt& qpressure_fct_pt()
  {return qPressure_fct_pt;}

 /// Access function: Pointer to pressure function. Const version
 FoepplvonKarmanPressureFctPt qpressure_fct_pt()
  const {return qPressure_fct_pt;}

 /// Get pressure term at (Eulerian) position x. This function is
 /// virtual to allow overloading in multi-physics problems where
 /// the strength of the pressure function might be determined by
 /// another system of equations.
 inline virtual void get_pressure_fvk(const unsigned& ipt,
                                        const Vector<double>& x,
                                        double& pressure) const
  {
   //If no pressure function has been set, return zero
   if(Pressure_fct_pt==0) {pressure = 0.0;}
   else
    {
     // Get pressure strength
     (*Pressure_fct_pt)(x,pressure);
    }
  }

 /// Get pressure term at (Eulerian) position x. This function is
 /// virtual to allow overloading in multi-physics problems where
 /// the strength of the pressure function might be determined by
 /// another system of equations.
 inline virtual void qget_pressure_fvk(const unsigned& ipt,
                                        const Vector<double>& x,
                                        double& pressure) const
  {
   //If no pressure function has been set, return zero
   if(qPressure_fct_pt==0) {pressure = 0.0;}
   else
    {
     // Get pressure strength
     (*qPressure_fct_pt)(x,pressure);
    }
  }


 /// Get gradient of pressure term at (Eulerian) position x. This function is
 /// virtual to allow overloading in multi-physics problems where
 /// the strength of the pressure function might be determined by
 /// another system of equations. Computed via function pointer
 /// (if set) or by finite differencing (default)
 inline virtual void get_pressure_gradient_fvk(
  const unsigned& ipt,
  const Vector<double>& x,
  Vector<double>& gradient) const
  {
   //If no gradient function has been set, FD it
   if(Pressure_fct_gradient_pt==0)
    {
     // Reference value
     double pressure=0.0;
     get_pressure_fvk(ipt,x,pressure);

     // FD it
     double eps_fd=GeneralisedElement::Default_fd_jacobian_step;
     double pressure_pls=0.0;
     Vector<double> x_pls(x);

     for (unsigned i=0;i<2;i++)
      {
       x_pls[i]+=eps_fd;
       get_pressure_fvk(ipt,x_pls,pressure_pls);
       gradient[i]=(pressure_pls-pressure)/eps_fd;
       x_pls[i]=x[i];
      }
    }
   else
    {
     // Get gradient
     (*Pressure_fct_gradient_pt)(x,gradient);
    }
  }




 /// Get flux: flux[i] = dw/dx_i
 void get_flux(const Vector<double>& s, Vector<double>& flux) const
  {
   //Find out how many nodes there are in the element
   const unsigned n_node = nnode();

   //Get the index at which the unknown is stored
   const unsigned w_nodal_index = nodal_index_fvk(0);

   //Set up memory for the shape and test functions
   Shape psi(n_node);
   DShape dpsidx(n_node,2);

   //Call the derivatives of the shape and test functions
   dshape_eulerian(s,psi,dpsidx);

   //Initialise to zero
   for(unsigned j=0;j<2;j++)
    {
     flux[j] = 0.0;
    }

   // Loop over nodes
   for(unsigned l=0;l<n_node;l++)
    {
     //Loop over derivative directions
     for(unsigned j=0;j<2;j++)
      {
       flux[j] += this->nodal_value(l,w_nodal_index)*dpsidx(l,j);
      }
    }
  }

 void fill_in_contribution_to_residuals(Vector<double> &residuals);

 /// \short Return FE representation of function value w_fvk(s)
 /// at local coordinate s
 inline double interpolated_w_fvk(const Vector<double> &s,
                                  unsigned index=0) const
  {
   //Find number of nodes
   const unsigned n_node = nnode();

   //Get the index at which the poisson unknown is stored
   const unsigned w_nodal_index = nodal_index_fvk(index);
   //const unsigned w_nodal_index = nodal_index_fvk(4);
   //const unsigned w_nodal_index2 = nodal_index_fvk(5);

   //Local shape function
   Shape psi(n_node);
   //DShape dpsidx(n_node,2);

   //Find values of shape function
   shape(s,psi);
   //dshape_eulerian(s,psi,dpsidx);

   //Initialise value of u
   double interpolated_w = 0.0;

   //Loop over the local nodes and sum
   for(unsigned l=0;l<n_node;l++)
    {
     interpolated_w += this->nodal_value(l,w_nodal_index)*psi[l];
     // mjr testing the mixed derivatives
     //interpolated_w += 0.5*
     //                  (this->nodal_value(l,w_nodal_index)*dpsidx(l,1)
     //                  +this->nodal_value(l,w_nodal_index2)*dpsidx(l,0));
    }

   return(interpolated_w);
  }

 /// \short Return the integral of the displacement over the current
 /// element, effectively calculating its contribution to the volume under
 /// the membrane
 double get_integral_w() const
  {
   //Number of nodes and integration points for the current element
   const unsigned n_node = nnode();
   const unsigned n_intpt = integral_pt()->nweight();

   //Shape functions and their derivatives
   Shape psi(n_node);
   DShape dpsidx(n_node,2);

   //The nodal index at which the displacement is stored
   const unsigned w_nodal_index = nodal_index_fvk();

   //Initalise the integral variable
   double integral_w = 0;

   //Loop over the integration points
   for(unsigned ipt=0;ipt<n_intpt;ipt++)
    {
     //Get the integral weight
     double w = integral_pt()->weight(ipt);

     //Get determinant of the Jacobian of the mapping
     double J = dshape_eulerian_at_knot(ipt,psi,dpsidx);

     //Premultiply the weight and Jacobian
     double W = w*J;

     //Initialise storage for the w value and nodal value
     double interpolated_w = 0;
     double w_nodal_value;

     //Loop over the shape functions/nodes
     for(unsigned l=0;l<n_node;l++)
      {
       //Get the current nodal value
       w_nodal_value = raw_nodal_value(l,w_nodal_index);
       //Add the contribution to interpolated w
       interpolated_w += w_nodal_value*psi(l);
      }

     //Add the contribution from the current integration point
     integral_w += interpolated_w*W;
    }

   //Return the calculated integral
   return integral_w;
  }

 /// \short Self-test: Return 0 for OK
 unsigned self_test();


protected:

 /// \short Shape/test functions and derivs w.r.t. to global coords at
 /// local coord. s; return  Jacobian of mapping
 virtual double dshape_and_dtest_eulerian_fvk(const Vector<double> &s,
                                              Shape &psi,
                                              DShape &dpsidx, Shape &test,
                                              DShape &dtestdx) const=0;


 /// \short Shape/test functions and derivs w.r.t. to global coords at
 /// integration point ipt; return  Jacobian of mapping
 virtual double dshape_and_dtest_eulerian_at_knot_fvk(const unsigned &ipt,
                                                      Shape &psi,
                                                      DShape &dpsidx,
                                                      Shape &test,
                                                      DShape &dtestdx)
  const=0;

 /// \short Shape/test functions and derivs w.r.t. to global coords at
 /// integration point ipt; return Jacobian of mapping (J). Also compute
 /// derivatives of dpsidx, dtestdx and J w.r.t. nodal coordinates.
 virtual double dshape_and_dtest_eulerian_at_knot_fvk(
  const unsigned &ipt,
  Shape &psi,
  DShape &dpsidx,
  RankFourTensor<double> &d_dpsidx_dX,
  Shape &test,
  DShape &dtestdx,
  RankFourTensor<double> &d_dtestdx_dX,
  DenseMatrix<double> &djacobian_dX) const=0;

 // Pointers to global physical constants

 /// Pointer to global eta
 double *Eta_pt;

 /// Pointer to global lambda
 double *Lambda_pt;

 /// Pointer to pressure function:
 FoepplvonKarmanPressureFctPt Pressure_fct_pt;

 /// Pointer to gradient of pressure function
 FoepplvonKarmanPressureFctGradientPt Pressure_fct_gradient_pt;

 //mjr Ridicu-hack for made-up second pressure, q
 FoepplvonKarmanPressureFctPt qPressure_fct_pt;

private:
 /// Default value for physical constants
 static double Default_Physical_Constant_Value;
};






///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


// mjr QFoepplvonKarmanElements are untested!

//======================================================================
/// QFoepplvonKarmanElement elements are linear/quadrilateral/brick-shaped
/// Foeppl von Karman elements with isoparametric interpolation for the
/// function.
//======================================================================

template <unsigned NNODE_1D>
 class QFoepplvonKarmanElement : public virtual QElement<2,NNODE_1D>,
 public virtual FoepplvonKarmanEquations
{

private:

 /// \short Static int that holds the number of variables at
 /// nodes: always the same
 static const unsigned Initial_Nvalue;

public:

 ///\short  Constructor: Call constructors for QElement and
 /// FoepplvonKarmanEquations
 QFoepplvonKarmanElement() : QElement<2,NNODE_1D>(),
                             FoepplvonKarmanEquations()
  {}

 /// Broken copy constructor
 QFoepplvonKarmanElement(const QFoepplvonKarmanElement<NNODE_1D>& dummy)
  {
   BrokenCopy::broken_copy("QFoepplvonKarmanElement");
  }

 /// Broken assignment operator
 void operator=(const QFoepplvonKarmanElement<NNODE_1D>&)
  {
   BrokenCopy::broken_assign("QFoepplvonKarmanElement");
  }


 /// \short  Required  # of `values' (pinned or dofs)
 /// at node n
 inline unsigned required_nvalue(const unsigned &n) const
  {return Initial_Nvalue;}

 /// \short Output function:
 ///  x,y,w
 void output(std::ostream &outfile)
  {FoepplvonKarmanEquations::output(outfile);}


 ///  \short Output function:
 ///   x,y,w at n_plot^DIM plot points
 void output(std::ostream &outfile, const unsigned &n_plot)
  {FoepplvonKarmanEquations::output(outfile,n_plot);}


 /// \short C-style output function:
 ///  x,y,w
 void output(FILE* file_pt)
  {FoepplvonKarmanEquations::output(file_pt);}


 ///  \short C-style output function:
 ///   x,y,w at n_plot^DIM plot points
 void output(FILE* file_pt, const unsigned &n_plot)
  {FoepplvonKarmanEquations::output(file_pt,n_plot);}


 /// \short Output function for an exact solution:
 ///  x,y,w_exact at n_plot^DIM plot points
 void output_fct(std::ostream &outfile, const unsigned &n_plot,
                 FiniteElement::SteadyExactSolutionFctPt exact_soln_pt)
  {FoepplvonKarmanEquations::output_fct(outfile,n_plot,exact_soln_pt);}



 /// \short Output function for a time-dependent exact solution.
 ///  x,y,w_exact at n_plot^DIM plot points
 /// (Calls the steady version)
 void output_fct(std::ostream &outfile, const unsigned &n_plot,
                 const double& time,
                 FiniteElement::UnsteadyExactSolutionFctPt exact_soln_pt)
  {FoepplvonKarmanEquations::output_fct(outfile,n_plot,time,exact_soln_pt);}


protected:

/// Shape, test functions & derivs. w.r.t. to global coords. Return Jacobian.
 inline double dshape_and_dtest_eulerian_fvk(
  const Vector<double> &s, Shape &psi, DShape &dpsidx,
  Shape &test, DShape &dtestdx) const;


 /// \short Shape, test functions & derivs. w.r.t. to global coords. at
 /// integration point ipt. Return Jacobian.
 inline double dshape_and_dtest_eulerian_at_knot_fvk(const unsigned& ipt,
                                                     Shape &psi,
                                                     DShape &dpsidx,
                                                     Shape &test,
                                                     DShape &dtestdx)
  const;

 /// \short Shape/test functions and derivs w.r.t. to global coords at
 /// integration point ipt; return Jacobian of mapping (J). Also compute
 /// derivatives of dpsidx, dtestdx and J w.r.t. nodal coordinates.
 inline double dshape_and_dtest_eulerian_at_knot_fvk(
  const unsigned &ipt,
  Shape &psi,
  DShape &dpsidx,
  RankFourTensor<double> &d_dpsidx_dX,
  Shape &test,
  DShape &dtestdx,
  RankFourTensor<double> &d_dtestdx_dX,
  DenseMatrix<double> &djacobian_dX) const;

};




//Inline functions:


//======================================================================
/// Define the shape functions and test functions and derivatives
/// w.r.t. global coordinates and return Jacobian of mapping.
///
/// Galerkin: Test functions = shape functions
//======================================================================
template<unsigned NNODE_1D>
double QFoepplvonKarmanElement<NNODE_1D>::dshape_and_dtest_eulerian_fvk(
  const Vector<double> &s,
  Shape &psi,
  DShape &dpsidx,
  Shape &test,
  DShape &dtestdx) const
{
 //Call the geometrical shape functions and derivatives
 const double J = this->dshape_eulerian(s,psi,dpsidx);

 //Set the test functions equal to the shape functions
 test = psi;
 dtestdx= dpsidx;

 //Return the jacobian
 return J;
}




//======================================================================
/// Define the shape functions and test functions and derivatives
/// w.r.t. global coordinates and return Jacobian of mapping.
///
/// Galerkin: Test functions = shape functions
//======================================================================
template<unsigned NNODE_1D>
double QFoepplvonKarmanElement<NNODE_1D>::
 dshape_and_dtest_eulerian_at_knot_fvk(
  const unsigned &ipt,
  Shape &psi,
  DShape &dpsidx,
  Shape &test,
  DShape &dtestdx) const
{
 //Call the geometrical shape functions and derivatives
 const double J = this->dshape_eulerian_at_knot(ipt,psi,dpsidx);

 //Set the pointers of the test functions
 test = psi;
 dtestdx = dpsidx;

 //Return the jacobian
 return J;
}



//======================================================================
/// Define the shape functions (psi) and test functions (test) and
/// their derivatives w.r.t. global coordinates (dpsidx and dtestdx)
/// and return Jacobian of mapping (J). Additionally compute the
/// derivatives of dpsidx, dtestdx and J w.r.t. nodal coordinates.
///
/// Galerkin: Test functions = shape functions
//======================================================================
template<unsigned NNODE_1D>
double QFoepplvonKarmanElement<NNODE_1D>::
 dshape_and_dtest_eulerian_at_knot_fvk(
  const unsigned &ipt,
  Shape &psi,
  DShape &dpsidx,
  RankFourTensor<double> &d_dpsidx_dX,
  Shape &test,
  DShape &dtestdx,
  RankFourTensor<double> &d_dtestdx_dX,
  DenseMatrix<double> &djacobian_dX) const
 {
  // Call the geometrical shape functions and derivatives
  const double J = this->dshape_eulerian_at_knot(ipt,psi,dpsidx,
                                                 djacobian_dX,d_dpsidx_dX);

  // Set the pointers of the test functions
  test = psi;
  dtestdx = dpsidx;
  d_dtestdx_dX = d_dpsidx_dX;

  //Return the jacobian
  return J;
}



////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


//mjr
//No point in de-DIMming these classes since they're not used here anyway
//=======================================================================
/// Face geometry for the QFoepplvonKarmanElement elements: The spatial
/// dimension of the face elements is one lower than that of the
/// bulk element but they have the same number of points
/// along their 1D edges.
//=======================================================================
//template<unsigned DIM, unsigned NNODE_1D>
//class FaceGeometry<QFoepplvonKarmanElement<DIM,NNODE_1D> >:
// public virtual QElement<DIM-1,NNODE_1D>
//{
//
//  public:
//
// /// \short Constructor: Call the constructor for the
// /// appropriate lower-dimensional QElement
// FaceGeometry() : QElement<DIM-1,NNODE_1D>() {}
//
//};
//
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//
//
////=======================================================================
///// Face geometry for the 1D QFoepplvonKarmanElement elements: Point elements
////=======================================================================
//template<unsigned NNODE_1D>
//class FaceGeometry<QFoepplvonKarmanElement<1,NNODE_1D> >:
// public virtual PointElement
//{
//
//  public:
//
// /// \short Constructor: Call the constructor for the
// /// appropriate lower-dimensional QElement
// FaceGeometry() : PointElement() {}
//
//};



////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


//==========================================================
/// Foeppl von Karman upgraded to become projectable
//==========================================================
 template<class FVK_ELEMENT>
 class ProjectableFoepplvonKarmanElement :
  public virtual ProjectableElement<FVK_ELEMENT>
 {

 public:

  /// \short Specify the values associated with field fld.
  /// The information is returned in a vector of pairs which comprise
  /// the Data object and the value within it, that correspond to field fld.
  Vector<std::pair<Data*,unsigned> > data_values_of_field(const unsigned& fld)
   {

#ifdef PARANOID
    if (fld > 7)
     {
      std::stringstream error_stream;
      error_stream
       << "Foeppl von Karman elements only store eight fields so fld must be"
       << "0 to 7 rather than " << fld << std::endl;
      throw OomphLibError(
       error_stream.str(),
       "ProjectableFoepplvonKarmanElement::data_values_of_field()",
       OOMPH_EXCEPTION_LOCATION);
     }
#endif

    // Create the vector
    unsigned nnod=this->nnode();
    Vector<std::pair<Data*,unsigned> > data_values(nnod);

    // Loop over all nodes
    for (unsigned j=0;j<nnod;j++)
     {
      // Add the data value associated field: The node itself
      data_values[j]=std::make_pair(this->node_pt(j),fld);
     }

    // Return the vector
    return data_values;
   }

  /// \short Number of fields to be projected: Just two
  unsigned nfields_for_projection()
   {
    return 8;
   }

  /// \short Number of history values to be stored for fld-th field.
  unsigned nhistory_values_for_projection(const unsigned &fld)
  {
#ifdef PARANOID
    if (fld > 7)
     {
      std::stringstream error_stream;
      error_stream
       << "Foeppl von Karman elements only store eight fields so fld must be"
       << "0 to 7 rather than " << fld << std::endl;
      throw OomphLibError(
       error_stream.str(),
       "ProjectableFoepplvonKarmanElement::nhistory_values_for_projection()",
       OOMPH_EXCEPTION_LOCATION);
     }
#endif
   return this->node_pt(0)->ntstorage();
  }

  ///\short Number of positional history values
  unsigned nhistory_values_for_coordinate_projection()
   {
    return this->node_pt(0)->position_time_stepper_pt()->ntstorage();
   }

  /// \short Return Jacobian of mapping and shape functions of field fld
  /// at local coordinate s
  double jacobian_and_shape_of_field(const unsigned &fld,
                                     const Vector<double> &s,
                                     Shape &psi)
   {
#ifdef PARANOID
    if (fld > 7)
     {
      std::stringstream error_stream;
      error_stream
       << "Foeppl von Karman elements only store eight fields so fld must be"
       << "0 to 7 rather than " << fld << std::endl;
      throw OomphLibError(
       error_stream.str(),
       "ProjectableFoepplvonKarmanElement::jacobian_and_shape_of_field()",
       OOMPH_EXCEPTION_LOCATION);
     }
#endif
    unsigned n_dim=this->dim();
    unsigned n_node=this->nnode();
    Shape test(n_node);
    DShape dpsidx(n_node,n_dim), dtestdx(n_node,n_dim);
    double J=this->dshape_and_dtest_eulerian_fvk(s,psi,dpsidx,
                                                      test,dtestdx);
    return J;
   }



  /// \short Return interpolated field fld at local coordinate s, at time level
  /// t (t=0: present; t>0: history values)
  double get_field(const unsigned &t,
                   const unsigned &fld,
                   const Vector<double>& s)
   {
#ifdef PARANOID
    if (fld > 7)
     {
      std::stringstream error_stream;
      error_stream
       << "Foeppl von Karman elements only store eight fields so fld must be"
       << "0 to 7 rather than " << fld << std::endl;
      throw OomphLibError(
       error_stream.str(),
       "ProjectableFoepplvonKarmanElement::jget_field()",
       OOMPH_EXCEPTION_LOCATION);
     }
#endif
    //Find the index at which the variable is stored
    unsigned w_nodal_index = this->nodal_index_fvk(fld);

      //Local shape function
    unsigned n_node=this->nnode();
    Shape psi(n_node);

    //Find values of shape function
    this->shape(s,psi);

    //Initialise value of u
    double interpolated_w = 0.0;

    //Sum over the local nodes
    for(unsigned l=0;l<n_node;l++)
     {
      interpolated_w += this->nodal_value(l,w_nodal_index)*psi[l];
     }
    return interpolated_w;
   }




  ///Return number of values in field fld: One per node
  unsigned nvalue_of_field(const unsigned &fld)
   {
#ifdef PARANOID
    if (fld > 7)
     {
      std::stringstream error_stream;
      error_stream
       << "Foeppl von Karman elements only store eight fields so fld must be"
       << "0 to 7 rather than " << fld << std::endl;
      throw OomphLibError(
       error_stream.str(),
       "ProjectableFoepplvonKarmanElement::nvalue_of_field()",
       OOMPH_EXCEPTION_LOCATION);
     }
#endif
    return this->nnode();
   }


  ///Return local equation number of field fld of node j.
  int local_equation(const unsigned &fld,
                     const unsigned &j)
   {
#ifdef PARANOID
    if (fld > 7)
     {
      std::stringstream error_stream;
      error_stream
       << "Foeppl von Karman elements only store eight fields so fld must be"
       << "0 to 7 rather than " << fld << std::endl;
      throw OomphLibError(
       error_stream.str(),
       "ProjectableFoepplvonKarmanElement::local_equation()",
       OOMPH_EXCEPTION_LOCATION);
     }
#endif
    const unsigned w_nodal_index = this->nodal_index_fvk(fld);
    return this->nodal_local_eqn(j,w_nodal_index);
   }

 };

//=======================================================================
/// Face geometry for element is the same as that for the underlying
/// wrapped element
//=======================================================================
 template<class ELEMENT>
 class FaceGeometry<ProjectableFoepplvonKarmanElement<ELEMENT> >
  : public virtual FaceGeometry<ELEMENT>
 {
 public:
  FaceGeometry() : FaceGeometry<ELEMENT>() {}
 };


//=======================================================================
/// Face geometry of the Face Geometry for element is the same as
/// that for the underlying wrapped element
//=======================================================================
 template<class ELEMENT>
 class FaceGeometry<FaceGeometry<ProjectableFoepplvonKarmanElement<ELEMENT> > >
  : public virtual FaceGeometry<FaceGeometry<ELEMENT> >
 {
 public:
  FaceGeometry() : FaceGeometry<FaceGeometry<ELEMENT> >() {}
 };

}

#endif
