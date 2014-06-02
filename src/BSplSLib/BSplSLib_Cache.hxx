// Copyright (c) 2014 OPEN CASCADE SAS
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

#ifndef _BSplSLib_Cache_Headerfile
#define _BSplSLib_Cache_Headerfile

#include <Standard.hxx>
#include <Standard_Macro.hxx>
#include <Standard_Type.hxx>
#include <Standard_Transient.hxx>

#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>

#include <TColgp_Array2OfPnt.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <TColStd_HArray2OfReal.hxx>
#include <TColStd_HArray1OfReal.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array2OfReal.hxx>

#ifndef NOWEIGHTS_SURF
#define NOWEIGHTS_SURF (*((TColStd_Array2OfReal*) NULL))
#endif

//! \brief A cache class for B-spline surfaces.
//!
//! Defines all data, that can be cached on a span of B-spline surface.
//! The data should be recalculated in going from span to span.
class BSplSLib_Cache : public Standard_Transient
{
public:
  //! Default constructor
  Standard_EXPORT BSplSLib_Cache();
  //! Constructor for caching of the span for B-spline surface
  //! \param theDegreeU    degree along the first parameter (U) of the B-spline
  //! \param thePeriodicU  identify the B-spline is periodical along U axis
  //! \param theFlatKnotsU knots of B-spline curve (with repetition) along U axis
  //! \param theDegreeV    degree alogn the second parameter (V) of the B-spline
  //! \param thePeriodicV  identify the B-spline is periodical along V axis
  //! \param theFlatKnotsV knots of B-spline curve (with repetition) along V axis
  //! \param thePoles      array of poles of the B-spline surface
  //! \param theWeights    array of weights of corresponding poles
  Standard_EXPORT BSplSLib_Cache(const Standard_Integer&        theDegreeU,
                                 const Standard_Boolean&        thePeriodicU,
                                 const TColStd_Array1OfReal&    theFlatKnotsU,
                                 const Standard_Integer&        theDegreeV,
                                 const Standard_Boolean&        thePeriodicV,
                                 const TColStd_Array1OfReal&    theFlatKnotsV,
                                 const TColgp_Array2OfPnt&      thePoles,
                                 const TColStd_Array2OfReal&    theWeights = NOWEIGHTS_SURF);

  //! Verifies validity of the cache using parameters of the point
  //! \param theParameterU  first parameter of the point placed in the span
  //! \param theParameterV  second parameter of the point placed in the span
  Standard_EXPORT Standard_Boolean IsCacheValid(Standard_Real theParameterU,
                                                Standard_Real theParameterV) const;

  //! Recomputes the cache data. Does not verify validity of the cache
  //! \param theParameterU  the parametric value on the U axis to identify the span
  //! \param theParameterV  the parametric value on the V axis to identify the span
  //! \param theDegreeU     degree of the B-spline along U axis
  //! \param thePeriodicU   identify the B-spline is periodic along U axis
  //! \param theFlatKnotsU  flat knots of B-spline surface along U axis
  //! \param theDegreeV     degree of the B-spline along V axis
  //! \param thePeriodicV   identify the B-spline is periodic along V axis
  //! \param theFlatKnotsV  flat knots of B-spline surface along V axis
  //! \param thePoles       array of poles of B-spline
  //! \param theWeights     array of weights of corresponding poles
  Standard_EXPORT void BuildCache(const Standard_Real&           theParameterU, 
                                  const Standard_Real&           theParameterV, 
                                  const Standard_Integer&        theDegreeU, 
                                  const Standard_Boolean&        thePeriodicU, 
                                  const TColStd_Array1OfReal&    theFlatKnotsU, 
                                  const Standard_Integer&        theDegreeV, 
                                  const Standard_Boolean&        thePeriodicV, 
                                  const TColStd_Array1OfReal&    theFlatKnotsV, 
                                  const TColgp_Array2OfPnt&      thePoles, 
                                  const TColStd_Array2OfReal&    theWeights = NOWEIGHTS_SURF);

  //! Calculates the point on B-spline for specified parameters
  //! \param[in]  theU      first parameter for calculation of the value
  //! \param[in]  theV      second parameter for calculation of the value
  //! \param[out] thePoint  the result of calculation (the point on the B-spline)
  Standard_EXPORT void D0(const Standard_Real& theU, const Standard_Real& theV, gp_Pnt& thePoint) const;

  //! Calculates the point on B-spline and its first derivative
  //! \param[in]  theU         first parameter of calculation of the value
  //! \param[in]  theV         second parameter of calculation of the value
  //! \param[out] thePoint     the result of calculation (the point on the B-spline)
  //! \param[out] theTangentU  tangent vector along U axis in the calculated point
  //! \param[out] theTangentV  tangent vector along V axis in the calculated point
  Standard_EXPORT void D1(const Standard_Real& theU, 
                          const Standard_Real& theV, 
                                gp_Pnt&        thePoint, 
                                gp_Vec&        theTangentU, 
                                gp_Vec&        theTangentV) const;

  //! Calculates the point on B-spline and derivatives till second order
  //! \param[in]  theU            first parameter of calculation of the value
  //! \param[in]  theV            second parameter of calculation of the value
  //! \param[out] thePoint        the result of calculation (the point on B-spline)
  //! \param[out] theTangentU     tangent vector along U axis in the calculated point
  //! \param[out] theTangentV     tangent vector along V axis in the calculated point
  //! \param[out] theCurvatureU   curvature vector (2nd derivative on U) along U axis
  //! \param[out] theCurvatureV   curvature vector (2nd derivative on V) along V axis
  //! \param[out] theCurvatureUV  2nd mixed derivative on U anv V
  Standard_EXPORT void D2(const Standard_Real& theU, 
                          const Standard_Real& theV, 
                                gp_Pnt&        thePoint, 
                                gp_Vec&        theTangentU, 
                                gp_Vec&        theTangentV, 
                                gp_Vec&        theCurvatureU, 
                                gp_Vec&        theCurvatureV, 
                                gp_Vec&        theCurvatureUV) const;


  DEFINE_STANDARD_RTTI(BSplSLib_Cache, Standard_Transient)

protected:
  //! Normalizes the parameter for periodical B-splines
  //! \param[in]     theDegree     degree of B-spline along selected direction
  //! \param[in]     theFlatKnots  knots with repetitions along selected direction
  //! \param[in,out] theParameter  the value to be normalized into the knots array
  void PeriodicNormalization(const Standard_Integer& theDegree, 
                             const TColStd_Array1OfReal& theFlatKnots, 
                                   Standard_Real& theParameter) const;

private:
  Handle(TColStd_HArray2OfReal) myPolesWeights; ///< array of poles and weights of calculated cache
                                                // the array has following structure:
                                                //       x11 y11 z11 [w11] x12 y12 z12 [w12] ...
                                                //       x21 y21 z21 [w21] x22 y22 z22 [w22] etc
                                                // for non-rational surfaces there is no weight;
                                                // size of array: (max(myDegree)+1) * A*(min(myDegree)+1), where A = 4 or 3

  Standard_Boolean              myIsRational;    ///< identifies the rationality of B-spline
  Standard_Real                 mySpanStart[2];  ///< parameters (u, v) for the frst point of the span
  Standard_Real                 mySpanLength[2]; ///< lengths of the span along corresponding parameter
  Standard_Integer              mySpanIndex[2];  ///< indexes of the span on B-spline surface
  Standard_Integer              mySpanIndexMax[2]; ///< maximal indexes of span
  Standard_Integer              myDegree[2];     ///< degrees of B-spline for each parameter
  Handle(TColStd_HArray1OfReal) myFlatKnots[2];  ///< arrays of knots of B-spline 
                                                 // (used for periodic normalization of parameters, Null for non-periodical splines)
};

DEFINE_STANDARD_HANDLE(BSplSLib_Cache, Standard_Transient)

#endif
