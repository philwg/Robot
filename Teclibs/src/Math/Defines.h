// **********************************************************************
// * FILE  : Defines.h
// * GROUP : TecLibs/Math
// *---------------------------------------------------------------------
// * PURPOSE : Math definitions
// * COMMENT : ...
// *---------------------------------------------------------------------
// * DATES     : 30/06/2000
// * AUTHORS   : Loic Le Chevalier (llechevalier@fr.infogrames.com)
// * COPYRIGHT : (c) Infogrames/TecLab 2000
// **********************************************************************
#ifndef _Defines_h_
#define _Defines_h_



// ----------------------------------------------------------------------
// +---------
// | Useful definitions
// +---------

// PI constants (<math.h> notation: '_'=divide)
#ifndef PI
#define PI          3.14159265358979
#endif
#ifndef PI_2
#define PI_2        (PI/2.0)
#endif
#ifndef PI_180
#define PI_180      0.01745329251994
#endif

// Other constants
#ifndef SQRT2
#define SQRT2       1.41421356237309
#endif
#ifndef EPSILON
#define EPSILON     0.001
#endif


// Conversion operations
#ifndef deg2rad
#define deg2rad(Angle)      ((Angle)*PI_180)
#endif

// Sqr & cube operations
#ifndef sqr
#define sqr(x)              ((x)*(x))
#endif
#ifndef cube
#define cube(x)             ((x)*(x)*(x))
#endif

// Other operations
#ifndef inv
#define inv(x)              (1/(x))
#endif



#endif//_Defines_h_
