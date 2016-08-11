#pragma once
#ifndef TYPES
#define TYPES
#include<cstdint>

#ifndef TARDY_VERSION
#define TARDY_VERSION "0_0_1"
#endif // !TARDY_VERSION



#ifdef __GNUC__
#define TR_GNUC
#endif


#ifdef _MSC_VER 
#define TR_MSC
#endif // _MSC_VER 

typedef int32_t TRint;
typedef signed char TRbyte;
typedef unsigned char TRbool;
#define TR_TRUE 1
#define TR_FALSE 0
typedef float TRfloat;
typedef double TRdouble;
typedef short TRshort;

typedef unsigned int TRenum;
typedef unsigned int TRbitfield;
typedef unsigned int TRuint;
typedef int TRsizei;
typedef unsigned char TRubyte;
typedef unsigned short TRushort;
typedef unsigned long TRulong;
typedef float TRclampf;
typedef double TRclampd;
typedef void TRvoid;


typedef int* TRsizeiptr,* TRintptr;
#define TARDY_API _stdcall 


//color struct
struct ColorRGBAf
{
	TRfloat red;
	TRfloat green;
	TRfloat blue;
	TRfloat alpha;
};
typedef struct ColorRGBAf ColorRGBAf;


struct ColorRGBAd
{
	TRdouble red;
	TRdouble green;
	TRdouble blue;
	TRdouble alpha;
};
typedef struct ColorRGBAd ColorRGBAd;

struct ColorRGBAi
{
	TRint red;
	TRint green;
	TRint blue;
	TRint alpha;
};
typedef struct ColorRGBAi ColorRGBAi;






#endif // !TYPES
