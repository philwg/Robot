// **********************************************************************
// * FILE  : Float.inl
// * GROUP : TecLibs/Math
// *---------------------------------------------------------------------
// * PURPOSE : Common Float operations
// * COMMENT : This unit serves to unify the notation for all standard
// *		   mathematical operations, whatever you defined the Float
// *		   type was (only float or double at the current time)
// *---------------------------------------------------------------------
// * DATES     : 09/11/2000
// * AUTHORS   : Loic Le Chevalier (llechevalier@fr.infogrames.com)
// *             Cédric Guérin (cguerin@fr.infogrames.com)
// * COPYRIGHT : (c) Infogrames/Teclab 2000
// **********************************************************************

// ----------------------------------------------------------------------
// +---------
// | Platform test
// +---------
#ifndef _ANSI
#error ANSI C Standard librairies are needed (Cf. in Math/Float.h)
#endif



// ----------------------------------------------------------------------
// +---------
// | Local includes
// +---------
#include <math.h>

#ifdef TEC_USE_DOUBLE

Float abs( const Float& dValue )
{
	return fabs(dValue);
}

#endif

#ifdef TEC_USE_FLOAT

// float overloads

Float cos( const Float& fValue )
{
	return cosf( fValue );
}

Float sin( const Float& fValue )
{
	return sinf( fValue );
}

Float tan( const Float& fValue )
{
	return tanf( fValue );
}

Float acos( const Float& fValue )
{
	return acosf( fValue );
}

Float asin( const Float& fValue )
{
	return asinf( fValue );
}

Float atan( const Float& fValue )
{
	return atanf( fValue );
}

Float abs( const Float& fValue )
{
	return  fabsf( fValue );
}

Float sqrt( const Float& fValue )
{
	return sqrtf( fValue );
}

Float log( const Float& fValue)
{
	return logf(fValue);
}

Float exp( const Float& fValue)
{
	return expf(fValue);
}

#endif
