//LIC// ====================================================================
//LIC// This file forms part of oomph-lib, the object-oriented, 
//LIC// multi-physics finite-element library, available 
//LIC// at http://www.oomph-lib.org.
//LIC// 
//LIC//           Version 0.85. June 9, 2008.
//LIC// 
//LIC// Copyright (C) 2006-2008 Matthias Heil and Andrew Hazel
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
//Include guards
#ifndef OOMPH_PRECONDITION_ARRAY_HEADER
#define OOMPH_PRECONDITION_ARRAY_HEADER

// oomph-lib includes
#include "Vector.h"
#include "double_vector.h"
#include "matrices.h"
#include "preconditioner.h"


#ifdef OOMPH_HAS_MPI
#include "mpi.h"
#endif

// Config header generated by autoconfig
#ifdef HAVE_CONFIG_H
  #include <oomph-lib-config.h>
#endif


namespace oomph
{

//=============================================================================
/// \short PreconditionerArray - 
/// NOTE - first implementation, a number of assumptions / simplifications
/// were made:
/// 1. Only works with CRDoubleMatrices \n
/// 2. The number of processors must be greater than the number of 
///    preconditioners \n
/// 3. Currently only very crude load balancing - each preconditioner will
///    be setup and applied with the same number of processors (or as near to
///    as possible to the same number of processors) \n
/// 4. This class will, at the appropriate time, delete the all the 
///    Preconditioners passed setup_preconditioners(...) \n
/// 5. (but) Deletion of matrices passed to setup_preconditioners(...) is NOT 
///    performed by this class \n
/// 6. It is assumed that preconditioners do not require access to matrix
///    once setup(...) is called \n
/// 7. The matrix on the subset of processors will be the same type 
///    (distributed or global) as the matrix passed to 
///    setup_preconditioners(...) \n
/// 8. If the matrix is a distributed matrix - it will be assembled with 
///    a uniform distribution on the subset of processors.
//=============================================================================
 class PreconditionerArray
  {
   
    public:
   
   /// Constructor (empty)
   PreconditionerArray()
    : Preconditioner_pt(0), Global_communicator_pt(0), Local_communicator_pt(0)
    {};
   
   /// Broken copy constructor
   PreconditionerArray(const PreconditionerArray&) 
    { 
     BrokenCopy::broken_copy("PreconditionerArray");
    } 
   
   /// Broken assignment operator
   void operator=(const PreconditionerArray&) 
    {
     BrokenCopy::broken_assign("PreconditionerArray");
    }
   
   /// Destructor (empty)
   ~PreconditionerArray()
    {
     this->clean_up_memory();
    }
   
   /// \short Setup the preconditioners. Sets up each preconditioner in the
   /// array for the corresponding matrix in the vector matrix_pt (and the 
   /// problem at problem_pt). \n
   /// The number of preconditioners in the array is taken to be the length of 
   /// prec_pt \n
   /// The preconditioners that are not used on this processor are deleted.
   void setup_preconditioners(Problem* problem_pt, 
                              Vector<CRDoubleMatrix*> matrix_pt,
                              Vector<Preconditioner*> prec_pt);
   
   /// \short Applies each preconditioner to the corresponding vector in
   /// r and z
   void solve_preconditioners(const Vector<DoubleVector> &r, 
                              Vector<DoubleVector> &z);
   
   /// \short Clean up memory.
   void clean_up_memory()
    {
     // delete the preconditioner pt
     delete Preconditioner_pt;
     Preconditioner_pt = 0;

     // delete the communicators
     delete Global_communicator_pt;
     Global_communicator_pt = 0;
     delete Local_communicator_pt;
     Local_communicator_pt = 0;

     // clear vectors
     First_row_for_proc.clear();
     Nrow_local_for_proc.clear();
     First_row_from_proc.clear();
     Nrow_local_from_proc.clear();   
     First_proc_for_prec.clear();
     Nproc_for_prec.clear();

#ifdef PARANOID
     // delete PARANOID check distribution pts
     for (unsigned i = 0;i < Nprec; i++)
      {
       delete Distribution_pt[i];
      }
#endif
    }
   
   // access function to Method
   unsigned& method() { return Method; }

    private:
   
   /// \short helper method for computing the MPI_Isend and MPI_Irecv tags
   int compute_tag(const int& nproc, const int& source, const int& dest,
                   const int& type)
    {
     return source + (nproc * dest) + (nproc * nproc * type);
    }

   /// \short the number of preconditioner in the array
   unsigned Nprec;
   
   /// The pointer to the local preconditioner on this processor
   Preconditioner* Preconditioner_pt;
   
   /// \short The first_row component of the distribution of the processors 
   /// over the preconditioners
   Vector<unsigned> First_proc_for_prec;
   
   /// \short The nrow_local component of the distribution of the processors 
   /// over the preconditioners
   Vector<unsigned> Nproc_for_prec;

   /// \short Storage (indexed [i][j]) for the first row that will be sent 
   /// from this processor to processor j for preconditioner i
   Vector< Vector<unsigned> > First_row_for_proc;

   /// \short Storage (indexed [i][j]) for the nrow_local that will be sent 
   /// from this processor to processor j for preconditioner i
   Vector< Vector<unsigned> > Nrow_local_for_proc;

   /// \short Storage (indexed [i][j]) for the first row that will be received 
   /// by this processor from processor j for preconditioner i
   Vector< Vector<unsigned> > First_row_from_proc;

   /// \short Storage (indexed [i][j]) for the nrow_local that will be 
   /// received by this processor from processor j for preconditioner i
   Vector< Vector<unsigned> > Nrow_local_from_proc;
   
   /// the Color of this processor (or the preconditioner number)
   unsigned Color;
   
   /// pointer to the global communicator for this preconditioner array
   OomphCommunicator* Global_communicator_pt;
   
   /// Vector of communicators for the preconditioners
   OomphCommunicator* Local_communicator_pt;

#ifdef PARANOID
   // Vector of distribution of each preconditioner - for PARANOID checks only
   Vector<LinearAlgebraDistribution*> Distribution_pt;
#endif

   /// \short the communication method in the setup_preconditioners(...) method
   /// 1. Non-blocking Send with Blocking Recv \n
   /// 2. MPI_Datatypes with Non-blocking sends and receives
   unsigned Method;

  };//PreconditionerArray
}

#endif