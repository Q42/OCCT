// Created on: 2001-01-04
// Copyright (c) 2001-2014 OPEN CASCADE SAS
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

#include <Graphic3d_ArrayOfPolylines.ixx>

Graphic3d_ArrayOfPolylines :: Graphic3d_ArrayOfPolylines (
                        const Standard_Integer maxVertexs,
                        const Standard_Integer maxBounds,
                        const Standard_Integer maxEdges,
                        const Standard_Boolean hasVColors,
                        const Standard_Boolean hasFColors,
			const Standard_Boolean hasEdgeInfos)
	: Graphic3d_ArrayOfPrimitives(Graphic3d_TOPA_POLYLINES,maxVertexs,maxBounds,maxEdges,Standard_False,hasVColors,hasFColors,Standard_False,hasEdgeInfos) {}
