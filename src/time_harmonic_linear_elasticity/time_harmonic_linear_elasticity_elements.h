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
//Header file for general linear elasticity elements

//Include guards to prevent multiple inclusion of the header
#ifndef OOMPH_LINEAR_ELASTICITY_ELEMENTS_HEADER
#define OOMPH_LINEAR_ELASTICITY_ELEMENTS_HEADER

// Config header generated by autoconfig
#ifdef HAVE_CONFIG_H
  #include <oomph-lib-config.h>
#endif


#include<complex>


//OOMPH-LIB headers
#include "../generic/Qelements.h"
#include "../generic/mesh.h"
#include "../generic/hermite_elements.h"
#include "./time_harmonic_elasticity_tensor.h"

namespace oomph
{
//=======================================================================
/// A base class for elements that solve the equations of time-harmonic linear 
/// elasticity in Cartesian coordinates.
/// Combines a few generic functions that are shared by 
/// TimeHarmonicLinearElasticityEquations
/// and TimeHarmonicLinearElasticityEquationsWithPressure (hierher: The latter
/// don't exist yet but will be written as soon as somebody needs them...)
//=======================================================================
 template <unsigned DIM>
  class TimeHarmonicLinearElasticityEquationsBase : public virtual FiniteElement
  {
    public:
   
   /// \short Return the index at which the i-th real or imag unknown 
   /// displacement component is stored. The default value is appropriate for
   /// single-physics problems: 
   virtual inline std::complex<unsigned> 
    u_index_time_harmonic_linear_elasticity(const unsigned i) const
    {
     return std::complex<unsigned>(i,i+DIM);
    }
   
   /// Compute vector of FE interpolated displacement u at local coordinate s
   void interpolated_u_time_harmonic_linear_elasticity(
    const Vector<double> &s, 
    Vector<std::complex<double> >& disp) 
    const
   {
    //Find number of nodes
    unsigned n_node = nnode();
    
    //Local shape function
    Shape psi(n_node);
    
    //Find values of shape function
    shape(s,psi);
    
    for (unsigned i=0;i<DIM;i++)
     {
      //Index at which the nodal value is stored
      std::complex<unsigned> u_nodal_index = 
       u_index_time_harmonic_linear_elasticity(i);
      
      //Initialise value of u
      disp[i] = std::complex<double>(0.0,0.0);
      
      //Loop over the local nodes and sum
      for(unsigned l=0;l<n_node;l++) 
       {
        disp[i].real() += nodal_value(l,u_nodal_index.real())*psi[l];
        disp[i].imag() += nodal_value(l,u_nodal_index.imag())*psi[l];
       }
     }
   }
   
   /// Return FE interpolated displacement u[i] at local coordinate s
   std::complex<double> interpolated_u_time_harmonic_linear_elasticity(
    const Vector<double> &s, 
    const unsigned &i) const
    {
     //Find number of nodes
     unsigned n_node = nnode();
     
     //Local shape function
     Shape psi(n_node);
     
     //Find values of shape function
     shape(s,psi);
     
     //Get nodal index at which i-th velocity is stored
     std::complex<unsigned> u_nodal_index = 
      u_index_time_harmonic_linear_elasticity(i);
     
     //Initialise value of u
     std::complex<double> interpolated_u = std::complex<double>(0.0,0.0);
     
     //Loop over the local nodes and sum
     for(unsigned l=0;l<n_node;l++) 
      {
       interpolated_u.real() += nodal_value(l,u_nodal_index.real())*psi[l];
       interpolated_u.imag() += nodal_value(l,u_nodal_index.imag())*psi[l];
      }
     
     return(interpolated_u);
    }
   
   
   /// \short Function pointer to function that specifies the body force
   /// as a function of the Cartesian coordinates and time FCT(t,x,b) -- 
   /// x and b are  Vectors! 
   typedef void (*BodyForceFctPt)(const double& t,
                                  const Vector<double>& x,
                                  Vector<std::complex<double> >& b);
   
   /// \short Constructor: Set null pointers for constitutive law and for
   /// isotropic growth function. Set physical parameter values to 
   /// default values, and set body force to zero.
    TimeHarmonicLinearElasticityEquationsBase() : Elasticity_tensor_pt(0),
    Omega_pt(&Default_omega_value), Body_force_fct_pt(0) {}
   
   /// Return the pointer to the elasticity_tensor
   TimeHarmonicElasticityTensor* &elasticity_tensor_pt()
    {return Elasticity_tensor_pt;}
   
   /// Access function to the entries in the elasticity tensor
   inline double E(const unsigned &i,const unsigned &j,
                   const unsigned &k, const unsigned &l) const
   {
    return (*Elasticity_tensor_pt)(i,j,k,l);
   }
   
   ///Access function for non-dim frequency
   const double& omega() const {return *Omega_pt;}
   
   /// Access function for non-dim frequency
   double* &omega_pt() {return Omega_pt;}
   
   /// Access function: Pointer to body force function
   BodyForceFctPt& body_force_fct_pt() {return Body_force_fct_pt;}
   
   /// Access function: Pointer to body force function (const version)
   BodyForceFctPt body_force_fct_pt() const {return Body_force_fct_pt;}
   
   /// \short Return the Cauchy stress tensor, as calculated
   /// from the elasticity tensor at specified local coordinate
   /// Virtual so separaete versions can (and must!) be provided
   /// for displacement and pressure-displacement formulations.
   virtual void get_stress(const Vector<double> &s, 
                           DenseMatrix<std::complex<double> > &sigma) const=0;
   
   /// \short Return the strain tensor
   void get_strain(const Vector<double> &s, 
                   DenseMatrix<std::complex<double> >&strain) const;
   
   /// \short Evaluate body force at Eulerian coordinate x at present time
   /// (returns zero vector if no body force function pointer has been set)
   inline void body_force(const Vector<double>& x, 
                          Vector<std::complex<double> >& b) const
   {
    //If no function has been set, return zero vector
    if(Body_force_fct_pt==0)
     {
      // Get spatial dimension of element
      unsigned n=dim();
      for (unsigned i=0;i<n;i++)
       {
        b[i] = std::complex<double>(0.0,0.0);
       }
     }
    else
     {
      // Get body force
      if (time_pt()!=0)
       {
        (*Body_force_fct_pt)(time_pt()->time(),x,b);
       }
      else
       {
        (*Body_force_fct_pt)(0.0,x,b);
       }
     }
   }
   
   /// \short The number of "blocks" that degrees of freedom in this element
   /// are sub-divided into: for now lump them all into one block.
   /// Can be adjusted later
   unsigned nblock_types()
   {
    return 1;
   }
   
   /// \short Create a list of pairs for all unknowns in this element,
   /// so that the first entry in each pair contains the global equation
   /// number of the unknown, while the second one contains the number
   /// of the "block" that this unknown is associated with.
   /// (Function can obviously only be called if the equation numbering
   /// scheme has been set up.) 
   void get_dof_numbers_for_unknowns(
    std::list<std::pair<unsigned long,unsigned> >& block_lookup_list)
   {

    // temporary pair (used to store block lookup prior to being added 
    // to list)
    std::pair<unsigned long,unsigned> block_lookup;
    
    // number of nodes
    const unsigned n_node = this->nnode();
    
    //Integer storage for local unknown
    int local_unknown=0;
    
    //Loop over the nodes
    for(unsigned n=0;n<n_node;n++)
     {
      //Loop over dimension (real and imag)
      for(unsigned i=0;i<2*DIM;i++)
       {
        //If the variable is free
        local_unknown = nodal_local_eqn(n,i);
        
        // ignore pinned values
        if (local_unknown >= 0)
         {
          // store block lookup in temporary pair: First entry in pair
          // is global equation number; second entry is block type
          block_lookup.first = this->eqn_number(local_unknown);
          block_lookup.second = 0;
          
          // add to list
          block_lookup_list.push_front(block_lookup);
          
         }
       }
     }
   }
   
   
    protected:
   
   /// Pointer to the elasticity tensor
   TimeHarmonicElasticityTensor *Elasticity_tensor_pt;
   
   /// Nondim frequency
   double* Omega_pt;

   /// Pointer to body force function
   BodyForceFctPt Body_force_fct_pt;
   
   /// Static default value for frequency (1.0 -- for natural scaling) 
   static double Default_omega_value;
   
  };
 
 
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////


//=======================================================================
/// A class for elements that solve the equations of linear elasticity
/// in cartesian coordinates.
//=======================================================================
 template <unsigned DIM>
  class TimeHarmonicLinearElasticityEquations : 
  public TimeHarmonicLinearElasticityEquationsBase<DIM>
  {
    public:
   
   /// \short  Constructor
   TimeHarmonicLinearElasticityEquations() {}
   
   /// Number of values required at node n.
   unsigned required_nvalue(const unsigned &n) const {return 2*DIM;}
   
   /// \short Return the residuals for the solid equations (the discretised
   /// principle of virtual displacements)
   void fill_in_contribution_to_residuals(Vector<double> &residuals)
   {
    fill_in_generic_contribution_to_residuals_time_harmonic_linear_elasticity(
     residuals,GeneralisedElement::Dummy_matrix,0);
   }
   
   
   /// The jacobian is calculated by finite differences by default,
   /// We need only to take finite differences w.r.t. positional variables
   /// For this element
   void fill_in_contribution_to_jacobian(Vector<double> &residuals,
                                         DenseMatrix<double> &jacobian)
   {
    //Add the contribution to the residuals
    this->fill_in_generic_contribution_to_residuals_time_harmonic_linear_elasticity(
     residuals,jacobian,1);
   }
   
   /// \short Return the Cauchy stress tensor, as calculated
   /// from the elasticity tensor at specified local coordinate
   void get_stress(const Vector<double> &s, 
                   DenseMatrix<std::complex<double> >&sigma) const;
   
   ///Output exact solution x,y,[z],u_r,v_r,[w_r],u_i,v_i,[w_i]
   void output_fct(std::ostream &outfile, 
                   const unsigned &nplot, 
                   FiniteElement::SteadyExactSolutionFctPt exact_soln_pt);
   
   /// Output: x,y,[z],u_r,v_r,[w_r],u_i,v_i,[w_i]
   void output(std::ostream &outfile) 
   {
    unsigned n_plot=5;
    output(outfile,n_plot);
   }
   
   /// Output: x,y,[z],u_r,v_r,[w_r],u_i,v_i,[w_i]
   void output(std::ostream &outfile, const unsigned &n_plot);
   
   
   /// C-style output: x,y,[z],u_r,v_r,[w_r],u_i,v_i,[w_i]
   void output(FILE* file_pt) 
   {
    unsigned n_plot=5;
    output(file_pt,n_plot);
   }
   
   /// Output: x,y,[z],u_r,v_r,[w_r],u_i,v_i,[w_i]
   void output(FILE* file_pt, const unsigned &n_plot);
   
   
    private:
   
   /// \short Private helper function to compute residuals and (if requested
   /// via flag) also the Jacobian matrix.
   virtual void fill_in_generic_contribution_to_residuals_time_harmonic_linear_elasticity(
    Vector<double> &residuals,DenseMatrix<double> &jacobian,unsigned flag);
   
  }; 
 

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


//===========================================================================
/// An Element that solves the equations of linear elasticity 
/// in Cartesian coordinates, using QElements for the geometry
//============================================================================
 template<unsigned DIM, unsigned NNODE_1D>
  class QTimeHarmonicLinearElasticityElement : public virtual QElement<DIM,NNODE_1D>,
  public virtual TimeHarmonicLinearElasticityEquations<DIM>
  {
    public:
   
   /// Constructor
    QTimeHarmonicLinearElasticityElement() : QElement<DIM,NNODE_1D>(), 
    TimeHarmonicLinearElasticityEquations<DIM>() { }
   
   /// Output function
   void output(std::ostream &outfile) 
   {TimeHarmonicLinearElasticityEquations<DIM>::output(outfile);}
   
   /// Output function
   void output(std::ostream &outfile, const unsigned &n_plot)
   {TimeHarmonicLinearElasticityEquations<DIM>::output(outfile,n_plot);}
   
   
   /// C-style output function
   void output(FILE* file_pt) 
   {TimeHarmonicLinearElasticityEquations<DIM>::output(file_pt);}
   
   /// C-style output function
   void output(FILE* file_pt, const unsigned &n_plot)
   {TimeHarmonicLinearElasticityEquations<DIM>::output(file_pt,n_plot);}
   
  };
 

//============================================================================
/// FaceGeometry of a linear 2D QTimeHarmonicLinearElasticityElement element
//============================================================================
 template<>
  class FaceGeometry<QTimeHarmonicLinearElasticityElement<2,2> > :
 public virtual QElement<1,2>
  {
    public:
   /// Constructor must call the constructor of the underlying solid element
    FaceGeometry() : QElement<1,2>() {}
  };
 
 
 
//============================================================================
/// FaceGeometry of a quadratic 2D QTimeHarmonicLinearElasticityElement element
//============================================================================
 template<>
  class FaceGeometry<QTimeHarmonicLinearElasticityElement<2,3> > :
 public virtual QElement<1,3>
  {
    public:
   /// Constructor must call the constructor of the underlying element
    FaceGeometry() : QElement<1,3>() {}
  };
 
 
 
//============================================================================
/// FaceGeometry of a cubic 2D QTimeHarmonicLinearElasticityElement element
//============================================================================
 template<>
  class FaceGeometry<QTimeHarmonicLinearElasticityElement<2,4> > :
  public virtual QElement<1,4>
  {
    public:
   /// Constructor must call the constructor of the underlying element
    FaceGeometry() : QElement<1,4>() {}
  };
  
  
//============================================================================
/// FaceGeometry of a linear 3D QTimeHarmonicLinearElasticityElement element
//============================================================================
  template<>
   class FaceGeometry<QTimeHarmonicLinearElasticityElement<3,2> > :
  public virtual QElement<2,2>
   {
     public:
    /// Constructor must call the constructor of the underlying element
     FaceGeometry() : QElement<2,2>() {}
   };
  
//============================================================================
/// FaceGeometry of a quadratic 3D QTimeHarmonicLinearElasticityElement element
//============================================================================
  template<>
   class FaceGeometry<QTimeHarmonicLinearElasticityElement<3,3> > :
  public virtual QElement<2,3>
   {
     public:
    /// Constructor must call the constructor of the underlying element
     FaceGeometry() : QElement<2,3>() {}
   };
  
  
//============================================================================
/// FaceGeometry of a cubic 3D QTimeHarmonicLinearElasticityElement element
//============================================================================
  template<>
   class FaceGeometry<QTimeHarmonicLinearElasticityElement<3,4> > :
  public virtual QElement<2,4>
   {
     public:
    /// Constructor must call the constructor of the underlying element
     FaceGeometry() : QElement<2,4>() {}
   };

}

#endif




