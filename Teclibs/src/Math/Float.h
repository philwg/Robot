// **********************************************************************
// * FILE  : Float.h
// * GROUP : TecLibs/Math
// *---------------------------------------------------------------------
// * PURPOSE : Common Float operations
// * COMMENT : This unit serves to unify the notation for all standard
// *		   mathematical operations, whatever you defined the Float
// *		   type was (only float or double at the current time)
// *---------------------------------------------------------------------
// * DATES     : 30/06/2000
// * AUTHORS   : Loic Le Chevalier (llechevalier@fr.infogrames.com)
// *             Cédric Guérin (cguerin@fr.infogrames.com)
// * COPYRIGHT : (c) Infogrames/Teclab 2000
// **********************************************************************
#ifndef _Float_h_
#define _Float_h_

// ----------------------------------------------------------------------
// +---------
// | Common includes
// +---------
#include "../TecLibs.h"

#ifdef TEC_USE_DOUBLE

// double only require to overload the abs method (calling fabs)
// all other methods have the good name.
inline Float abs( const Float& );

#endif

#ifdef TEC_USE_FLOAT

// floats overloads
inline Float cos( const Float& );
inline Float sin( const Float& );
inline Float tan( const Float& );

inline Float acos( const Float& );
inline Float asin( const Float& );
inline Float atan( const Float& );

inline Float abs( const Float& );
inline Float sqrt( const Float& );

inline Float exp( const Float& );
inline Float log( const Float& );

#endif

#endif//_Float_h_
