/*
 * Source: PC ASM tutorial
 *
 * Define macros to specify the standard C calling convention
 * The macros are designed so that they will work with all
 * supported C/C++ compilers.
 *
 * To use define your function prototype like this:
 *
 * return_type PRE_CDECL func_name( args ) POST_CDECL;
 *
 * For example:
 *
 * int PRE_CDECL f( int x, int y) POST_CDECL;
 */

#ifndef CDECL_H_
#define CDECL_H_

#ifdef __GNUC__
#	define CDECL(decl)	decl __attribute__((cdecl))
#else
#	define CDECL(decl)	__cdecl decl
#endif

#endif
