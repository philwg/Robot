// **********************************************************************
// * FILE  : TecLibs.h
// * GROUP : TecLibs, base definitions
// *---------------------------------------------------------------------
// * PURPOSE : Common definitions for TecLibs
// * COMMENT : - Supported definitions
// *              - Platforms: Win32, PS2, etc.
// *              - Modes    : Debug, Release
// *           - Common includes:
// *              - <assert.h> -> To use assert
// *           - Common definitions:
// *              - Boolean values
// *           - Common macros:
// *              - Min/Max
// *           - Fast user types aliases (for all common traitments):
// *              - Integers: ie, int
// *              - Floats  : ie, float
// *              - Flags   : ie, bool
// *           - Sized types aliases (only for specific traitments):
// *              - Integers: ie, unsigned and signed 8, 16, 32 and 64
// *              - Floats  : ie, IEEE 754 sized floats
// *              - Flags   : ie, alias for unsigned integers
// *---------------------------------------------------------------------
// * DATES     : 16/06/2000
// * AUTHORS   : Loic Le Chevalier (llechevalier@fr.infogrames.com)
// * COPYRIGHT : (c) Infogrames/TecLab 2000
// **********************************************************************
#ifndef	_TecLibs_h_
#define _TecLibs_h_



// ----------------------------------------------------------------------
// +---------
// | Supported definitions
// +---------



// Supported platforms
#ifdef _ANY         // => no error
#endif
#ifdef _ANSI        // => #error ANSI C Standard librairies are needed
#endif
#ifdef _WIN32       // => #error Win32 platform is needed
#endif
#ifdef _PS2         // => #error PS2 platform is needed
#ifndef __int64
#define __int64 long long
#endif
#endif
#ifdef _LINUX       // => #error Linux platform is needed
#ifndef __int64
#define __int64 long long
#endif
#endif

// Supported modes
#ifdef _DEBUG
#endif
#ifdef _RELEASE
#endif

// Default definitions
#define _ANY        // We suppose that C++ language is defined!!
#define _ANSI       // We suppose that ANSI C Standard libraries are defined (most cases)



// ----------------------------------------------------------------------
// +---------
// | Common includes
// +---------

#include <assert.h> // To use assert()



// ----------------------------------------------------------------------
// +---------
// | Common definitions
// +---------

// Boolean values
#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

// NULL value
#ifndef NULL
#define NULL 0
#endif



// ----------------------------------------------------------------------
// +---------
// | Common macros
// +---------

// Min & max operations
#ifndef min
#define min(x,y)            ((x)<(y)?(y):(x))
#endif
#ifndef max
#define max(x,y)            ((x)<(y)?(x):(y))
#endif

// Signed new & delete operations
#ifndef snew
#define snew                new
#endif
#ifndef sdelete
#define sdelete             delete
#endif



// ----------------------------------------------------------------------
// +---------
// | Fast & Sized types
// +---------

// Fast integer
// -----User definition-----Sytem dependent type
typedef int                 Int;
typedef unsigned int		UInt;

// Sized integers
// -----User definition-----Type--------Bits count-----Signed------Range of value
typedef signed char         IntS8;   // 8              Yes         -128 to 127
typedef unsigned char       IntU8;   // 8              No          0 to 255
typedef signed short        IntS16;  // 16             Yes         -32768 to 32767
typedef unsigned short      IntU16;  // 16             No          0 to 65535
typedef long                IntS32;  // 32             Yes         -2147483648 to 2147483647
typedef unsigned long       IntU32;  // 32             No          0 to 4294967295
//typedef __int64             IntS64;  // 64             Yes         -9223372036854775808 to 9223372036854775807
//typedef unsigned __int64    IntU64;  // 64             No          0 to 18446744073709551615


// Fast float
// -----User definition-----Sytem dependent type
// default type is float. Use a project preprocessor define to use anything else
// to allow easy switching between types, all standard math.h methods are redefined
// in Float.h when needed with the same naming conventions.
// This concerns: cos, sin, tan, acos, asin, atan, abs, sqrt, exp, log  
#ifndef TEC_USE_DOUBLE
	#ifndef TEC_USE_FLOAT
		#define TEC_USE_FLOAT
	#endif
#endif
#ifdef TEC_USE_FLOAT
	typedef float           Float;
	const   Float		    Float_Max = 3.4e38f;
	const   Float           Float_Min = 1.2e-38f;
#endif
#ifdef TEC_USE_DOUBLE
	typedef double          Float;
	const	Float			Float_Max = 1.7e308;
	const	Float			Float_Min = 2.3e-308;
#endif

// Sized floats
// -----User definition-----Type--------Bits count-----Signed------Range of value
typedef float               Float32; // 32             Yes         +/-3.4E +/-  38  (precision 7 digits)
typedef double              Float64; // 64             Yes         +/-1.7E +/- 308  (precision 15 digits)
typedef double              Float64; // 64             Yes         +/-1.7E +/- 308  (precision 15 digits)
typedef long double         Float80; // 80             Yes         +/-1.2E +/- 4932 (precision 19 digits)


// Fast boolean
// -----User definition-----Sytem dependent type
typedef bool                Bool;

// Sized flags
// -----User definition-----Type--------Bits count-----Signed------Range of value
typedef unsigned char       Flag8;   // 8              No          0x00 to 0xFF
typedef unsigned short      Flag16;  // 16             No          0x0000 to 0xFFFF
typedef unsigned long       Flag32;  // 32             No          0x00000000 to 0xFFFFFFFF
//typedef unsigned __int64    Flag64;  // 64             No          0x0000000000000000 to 0xFFFFFFFFFFFFFFFF



#endif //_TecLibs_h_
