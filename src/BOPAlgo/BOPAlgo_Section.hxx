// Created by: Peter KURNEV
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement. 

#ifndef _BOPAlgo_Section_HeaderFile
#define _BOPAlgo_Section_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Handle.hxx>

#include <BOPAlgo_Builder.hxx>
#include <BOPCol_BaseAllocator.hxx>
#include <TopTools_ListOfShape.hxx>
class BOPAlgo_PaveFiller;
class TopoDS_Shape;



//! The algorithm to build a Section between the arguments.
//! The Section consists of vertices and edges.
//! The Section contains:
//! 1. new vertices that are subjects of V/V, E/E, E/F, F/F interferences
//! 2. vertices that are subjects of V/E, V/F interferences
//! 3. new edges that are subjects of F/F interferences
//! 4. edges that are Common Blocks
class BOPAlgo_Section  : public BOPAlgo_Builder
{
public:

  DEFINE_STANDARD_ALLOC

  
  //! Empty constructor
  Standard_EXPORT BOPAlgo_Section();
  Standard_EXPORT virtual ~BOPAlgo_Section();

  //! Constructor with allocator
  Standard_EXPORT BOPAlgo_Section(const BOPCol_BaseAllocator& theAllocator);

protected:

  //! Checks the data before performing the operation
  Standard_EXPORT virtual void CheckData() Standard_OVERRIDE;

  //! Combine the result of section operation
  Standard_EXPORT virtual void BuildSection();

  //! Performs calculations using prepared Filler object <thePF>
  Standard_EXPORT virtual void PerformInternal1(const BOPAlgo_PaveFiller& thePF) Standard_OVERRIDE;

private:

};

#endif // _BOPAlgo_Section_HeaderFile
