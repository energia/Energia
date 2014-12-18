/* yvals.h values header for conforming compilers on various systems */
#ifndef _YVALS
#define _YVALS
#include <stdarg.h> 
#define _CPPLIB_VER	402


/* You can predefine (on the compile command line, for example):

_ALT_NS=1 -- to use namespace _Dinkum_std for C++
_ALT_NS=2 -- to use namespace _Dinkum_std for C++ and C
_C_AS_CPP -- to compile C library as C++
_C_IN_NS -- to define C names in std/_Dinkum_std instead of global namespace
_C99 -- to turn ON C99 library support
_ABRCPP -- to turn ON Abridged C++ dialect (implies _ECPP)
_ECPP -- to turn ON Embedded C++ dialect
_NO_EX -- to turn OFF use of try/throw
_NO_MT -- to turn OFF thread synchronization
_NO_NS -- to turn OFF use of namespace declarations
_STL_DB (or _STLP_DEBUG) -- to turn ON iterator/range debugging
__NO_LONG_LONG -- to define _Longlong as long, not long long

You can change (in this header):

_ADDED_C_LIB -- from 1 to 0 to omit declarations for C extensions
_COMPILER_TLS -- from 0 to 1 if _TLS_QUAL is not nil
_EXFAIL -- from 1 to any nonzero value for EXIT_FAILURE
_FILE_OP_LOCKS -- from 0 to 1 for file atomic locks
_GLOBAL_LOCALE -- from 0 to 1 for shared locales instead of per-thread
_HAS_IMMUTABLE_SETS -- from 1 to 0 to permit alterable set elements
_HAS_STRICT_CONFORMANCE -- from 0 to 1 to disable nonconforming extensions
_HAS_TRADITIONAL_IOSTREAMS -- from 1 to 0 to omit old iostreams functions
_HAS_TRADITIONAL_ITERATORS -- from 0 to 1 for vector/string pointer iterators
_HAS_TRADITIONAL_POS_TYPE -- from 0 to 1 for streampos same as streamoff
_HAS_TRADITIONAL_STL -- from 1 to 0 to omit old STL functions
_IOSTREAM_OP_LOCKS -- from 0 to 1 for iostream atomic locks
_TLS_QUAL -- from nil to compiler TLS qualifier, such as __declspec(thread)
_USE_EXISTING_SYSTEM_NAMES -- from 1 to 0 to disable mappings (_Open to open)

Include directories needed to compile with Dinkum C:

C -- include/c
C99 -- include/c (define _C99)
Embedded C++ -- include/c include/embedded (define _ECPP)
Abridged C++ -- include/c include/embedded include (define _ABRCPP)
Standard C++ -- include/c include
Standard C++ with export -- include/c include/export include
	(--export --template_dir=lib/export)

Include directories needed to compile with native C:

C -- none
C99 -- N/A
Embedded C++ -- include/embedded (define _ECPP)
Abridged C++ -- include/embedded include (define _ABRCPP)
Standard C++ -- include
Standard C++ with export -- include/export include
	(--export --template_dir=lib/export)
 */

#if defined(__TI_COMPILER_VERSION__)
 #define _C_IN_NS 1
 #define __EDG__  1
 #define __FPUTS_RETURN_NUM_BYTES__ 1
 #ifdef __EXCEPTIONS
    #undef _NO_EX 
 #else
    #define _NO_EX 1
 #endif /* __EXCEPTIONS */
 #if defined(__unsigned_chars__)
   #define __CHAR_UNSIGNED__ 1
 #else
   #undef __CHAR_UNSIGNED__
   #undef _CHAR_UNSIGNED
 #endif /* defined(__unsigned_chars__) */
 #undef _32_BIT_DOUBLE

 /* targets with "native" mode libraries don't support C9X */
 #define _HAS_C9X 0

 /* TI RTS supports the C9X snprintf() and vsnprintf() functions */
 #ifndef _C9X_SNPRINTF
  #define _C9X_SNPRINTF 1
 #endif /* _C9X_SNPRINTF */

#endif /* defined(__TI_COMPILER_VERSION__) */

 #ifndef __STDC_HOSTED__
  #define __STDC_HOSTED__	1
 #endif /* __STDC_HOSTED__ */

 #ifndef __STDC_IEC_559__
  #define __STDC_IEC_559__	1
 #endif /* __STDC_IEC_559__ */

 #ifndef __STDC_IEC_559_COMPLEX__
  #define __STDC_IEC_559_COMPLEX__	1
 #endif /* __STDC_IEC_559_COMPLEX__ */

 #ifndef __STDC_ISO_10646__
  #define __STDC_ISO_10646__	200009L	/* match glibc */
 #endif /* __STDC_ISO_10646__ */

		/* DETERMINE MACHINE TYPE */

 #if defined(_ARM_)	/* ARM */
  #define _D0		3	/* 0: big endian, 3: little endian floating-point */
  #define _DLONG	0	/* 0: 64, 1: 80, 2: 128 long double bits */
  #define _LBIAS	0x3fe	/* 64 long double bits */
  #define _LOFF		4	/* 64 long double bits */
  #define _FPP_TYPE	_FPP_ARM	/* ARM ARM FPP */

 #elif defined(_M68K)	/* Motorola 68K */
  #define _D0		0	/* 0: big endian, 3: little endian floating-point */
  #define _DLONG	1	/* 0: 64, 1: 80, 2: 128 long double bits */
  #define _LBIAS	0x3ffe	/* 80/128 long double bits */
  #define _LOFF		15	/* 80/128 long double bits */
  #define _FPP_TYPE	_FPP_M68K	/* Motorola 68xxx FPP */

 #elif defined(_SH4_)	/* SH4 */
  #define _D0		0	/* 0: big endian, 3: little endian floating-point */
  #define _DLONG	0	/* 0: 64, 1: 80, 2: 128 long double bits */
  #define _LBIAS	0x3fe	/* 64 long double bits */
  #define _LOFF		4	/* 64 long double bits */
  #define _FPP_TYPE	_FPP_SH4	/* Hitachi SH4 FPP */

 #elif defined(_M_IA64)	/* IA64 */
  #define _D0		3	/* 0: big endian, 3: little endian floating-point */
  #define _DLONG	0	/* 0: 64, 1: 80, 2: 128 long double bits */
  #define _LBIAS	0x3fe	/* 64 long double bits */
  #define _LOFF		4	/* 64 long double bits */
  #define _FPP_TYPE	_FPP_IA64	/* Intel IA64 FPP */

 #else
    #undef _D0
    #define _32_BIT_DOUBLE 1
 #endif /* system detector */

		/* DETERMINE _Ptrdifft AND _Sizet FROM MACHINE TYPE */

typedef long _Int32t;
typedef unsigned long _Uint32t;

 #if defined(__TI_COMPILER_VERSION__)
typedef  __PTRDIFF_T_TYPE__  _Ptrdifft;
 #else /* defined(_MACH_PDT) */
typedef int _Ptrdifft;
 #endif /* defined(_MACH_PDT) */

 #if defined(__TI_COMPILER_VERSION__)
typedef  __SIZE_T_TYPE__ _Sizet;
 #else /* defined(_MACH_SZT) */
typedef unsigned int _Sizet;
 #endif /* defined(_MACH_SZT) */

 #if defined(__linux)
  #define _LINUX_C_LIB	1	/* Linux-specific conventions */
 #endif /* defined(__linux) */

 #if defined(_M_IX86) || defined(_M_MRX000) || defined(_M_PPC) \
	|| defined(_M_ALPHA) || defined(_M_IA64) || defined(_WIN32_WCE)
  #define _WIN32_C_LIB	1	/* use Windows32 conventions */
 #elif defined(__TI_COMPILER_VERSION__)
   #undef _POSIX_C_LIB
 #else /* defined(_M_*) */
  #define _POSIX_C_LIB	1	/* use common Unix/Linux conventions */
 #endif /* defined(_M_*) */

 #if !defined(_HAS_C9X) && defined(_C99)
  #define _HAS_C9X	1
 #endif /* !defined(_HAS_C9X) etc. */

 #define _HAS_C9X_IMAGINARY_TYPE	(_HAS_C9X && __EDG__ \
	&& !defined(__cplusplus))

 #if !defined(_ECPP) && defined(_ABRCPP)
  #define _ECPP
 #endif /* !defined(_ECPP) && defined(_ABRCPP) */

 #if !defined(_IS_EMBEDDED) && defined(_ECPP)
  #define _IS_EMBEDDED	1	/* 1 for Embedded C++ */
 #endif /* _IS_EMBEDDED */

		/* EXCEPTION CONTROL */
 #ifndef _HAS_EXCEPTIONS
  #ifndef _NO_EX	/* don't simplify */
   #define _HAS_EXCEPTIONS	1	/* 1 for try/throw logic */

  #else	/* _NO_EX */
   #define _HAS_EXCEPTIONS	0
  #endif /* _NO_EX */

 #endif /* _HAS_EXCEPTIONS */

		/* NAMING PROPERTIES */
/* #define _STD_LINKAGE	defines C names as extern "C++" */
/* #define _STD_USING	defines C names in namespace std or _Dinkum_std */

 #ifndef _HAS_NAMESPACE
  #ifndef _NO_NS	/* don't simplify */
   #define _HAS_NAMESPACE	1	/* 1 for C++ names in std */

  #else	/* _NO_NS */
   #define _HAS_NAMESPACE	0
  #endif /* _NO_NS */

 #endif /* _HAS_NAMESPACE */
 
 #if !defined(_STD_USING) && defined(__cplusplus) \
	&& defined(_C_IN_NS)
  #define _STD_USING	/* exports C names to global, else reversed */

 #elif defined(_STD_USING) && !defined(__cplusplus)
  #undef _STD_USING	/* define only for C++ */
 #endif /* !defined(_STD_USING) */

 #if !defined(_HAS_STRICT_LINKAGE) \
	&& __EDG__ && !defined(_WIN32_C_LIB)
  #define _HAS_STRICT_LINKAGE __TI_STRICT_ANSI_MODE__   /* extern "C" in function type */
 #endif /* !defined(_HAS_STRICT_LINKAGE) */

		/* THREAD AND LOCALE CONTROL */
#if defined(__TI_COMPILER_VERSION__)
  #define _NO_MT 1
  #define _MULTI_THREAD	0
#else
 #ifndef _MULTI_THREAD

   #ifndef _NO_MT
    #define _MULTI_THREAD	1	/* 0 for no thread locks */

   #else
    #define _MULTI_THREAD	0
   #endif	/* _NO_MT */

 #endif /* _MULTI_THREAD */
#endif /* defined(__TI_COMPILER_VERSION__) */
 
#define _GLOBAL_LOCALE	0	/* 0 for per-thread locales, 1 for shared */
#define _FILE_OP_LOCKS	0	/* 0 for no FILE locks, 1 for atomic */
#define _IOSTREAM_OP_LOCKS	0	/* 0 for no iostream locks, 1 for atomic */

		/* THREAD-LOCAL STORAGE */
#define _COMPILER_TLS	0	/* 1 if compiler supports TLS directly */
#define _TLS_QUAL	/* TLS qualifier, such as __declspec(thread), if any */

 #define _HAS_IMMUTABLE_SETS	1
 #define _HAS_IMMUTABLE_SETS	1
 #define _HAS_TRADITIONAL_IOSTREAMS	0
 #define _HAS_TRADITIONAL_ITERATORS	0
 #define _HAS_TRADITIONAL_POS_TYPE	0
 #define _HAS_TRADITIONAL_STL	1
 #define _HAS_TRADITIONAL_IOSTREAMS	0
 #define _HAS_TRADITIONAL_ITERATORS	0
 #define _HAS_TRADITIONAL_POS_TYPE	0
 #define _HAS_TRADITIONAL_STL	1

 #define _ADDED_C_LIB	1
 #define _USE_EXISTING_SYSTEM_NAMES	1 /* _Open => open etc. */

 #if !defined(_HAS_STRICT_CONFORMANCE)
  #define _HAS_STRICT_CONFORMANCE	0	/* enable nonconforming extensions */
 #endif /* !defined(_HAS_STRICT_CONFORMANCE) */

 #if !defined(_HAS_ITERATOR_DEBUGGING) \
	&& (defined(_STL_DB) || defined(_STLP_DEBUG))
  #define _HAS_ITERATOR_DEBUGGING	1	/* for range checks, etc. */
 #endif /* define _HAS_ITERATOR_DEBUGGING */

		/* NAMESPACE CONTROL */

 #if defined(__cplusplus)

 #if _HAS_NAMESPACE
namespace std {}

 #if defined(_C_AS_CPP)
  #define _NO_CPP_INLINES	/* just for compiling C library as C++ */
 #endif /* _C_AS_CPP */

 #if defined(_STD_USING)
  #if defined(_C_AS_CPP)	/* define library in std */
   #define _STD_BEGIN	namespace std {_C_LIB_DECL
   #define _STD_END		_END_C_LIB_DECL }

  #else /* _C_AS_CPP */
   #define _STD_BEGIN	namespace std {
   #define _STD_END		}
  #endif /* _C_AS_CPP */

   #define _C_STD_BEGIN	namespace std {
   #define _C_STD_END	}
   #define _CSTD	        ::std::
   #define _STD			::std::

 #else /* _ALT_NS == 0 && !defined(_STD_USING) */

  #if defined(_C_AS_CPP)	/* define C++ library in std, C in global */
   #define _STD_BEGIN	_C_LIB_DECL
   #define _STD_END		_END_C_LIB_DECL

  #else /* _C_AS_CPP */
   #define _STD_BEGIN	namespace std {
   #define _STD_END		}
  #endif /* _C_AS_CPP */

   #define _C_STD_BEGIN	
   #define _C_STD_END	
   #define _CSTD		::
   #define _STD			::std::
 #endif /* _ALT_NS etc */

  #define _X_STD_BEGIN	namespace std {
  #define _X_STD_END	}
  #define _XSTD			::std::

  #if defined(_STD_USING)
   #undef _GLOBAL_USING		/* c* in std namespace, *.h imports to global */

  #else
   #define _GLOBAL_USING	/* *.h in global namespace, c* imports to std */
  #endif /* defined(_STD_USING) */

  #if defined(_STD_LINKAGE)
   #define _C_LIB_DECL		extern "C++" {	/* C has extern "C++" linkage */

  #else /* defined(_STD_LINKAGE) */
   #define _C_LIB_DECL		extern "C" {	/* C has extern "C" linkage */
  #endif /* defined(_STD_LINKAGE) */

  #define _END_C_LIB_DECL	}
  #define _EXTERN_C			extern "C" {
  #define _END_EXTERN_C		}

 #else /* _HAS_NAMESPACE */

  #define _STD_BEGIN
  #define _STD_END
  #define _STD	::

  #define _X_STD_BEGIN
  #define _X_STD_END
  #define _XSTD	::

  #define _C_STD_BEGIN
  #define _C_STD_END
  #define _CSTD	::

  #define _C_LIB_DECL		extern "C" {
  #define _END_C_LIB_DECL	}
  #define _EXTERN_C			extern "C" {
  #define _END_EXTERN_C		}
 #endif /* _HAS_NAMESPACE */

 #else /* __cplusplus */
  #define _STD_BEGIN
  #define _STD_END
  #define _STD

  #define _X_STD_BEGIN
  #define _X_STD_END
  #define _XSTD

  #define _C_STD_BEGIN
  #define _C_STD_END
  #define _CSTD

  #define _C_LIB_DECL
  #define _END_C_LIB_DECL
  #define _EXTERN_C
  #define _END_EXTERN_C
 #endif /* __cplusplus */

 #if 199901L <= __STDC_VERSION__

 #if defined(__GNUC__) || defined(__cplusplus)
  #define _Restrict

 #else /* defined(__GNUC__) || defined(__cplusplus) */
  #define _Restrict restrict
 #endif /* defined(__GNUC__) || defined(__cplusplus) */


 #else /* 199901L <= __STDC_VERSION__ */
 #define _Restrict
 #endif /* 199901L <= __STDC_VERSION__ */

 #ifdef __cplusplus
_STD_BEGIN
typedef bool _Bool;
_STD_END
 #endif /* __cplusplus */

		/* VC++ COMPILER PARAMETERS */
 #define _CRTIMP
 #define _CDECL


 #ifdef __NO_LONG_LONG

 #else
  #define _LONGLONG	long long
  #define _ULONGLONG	unsigned long long
  #define _LLONG_MAX    0x7fffffffff /* MAX VALUE FOR LONG LONG      	  */
  #define _ULLONG_MAX   0xffffffffff /* MAX VALUE FOR UNSIGNED LONG LONG       */ 
 #endif /* __NO_LONG_LONG */

		/* MAKE MINGW LOOK LIKE WIN32 HEREAFTER */



_C_STD_BEGIN
		/* FLOATING-POINT PROPERTIES */
#if (!defined(_32_BIT_DOUBLE))
#define _DBIAS	0x3fe	/* IEEE format double and float */
#define _DOFF	4
#define _FBIAS	0x7e
#define _FOFF	7
#define _FRND	1
#endif /* (!defined(_32_BIT_DOUBLE)) */

		/* INTEGER PROPERTIES */
#if (defined(__TMS320C55X__) && !defined(__TMS320C55X_PLUS_BYTE__)) ||\
    defined(__TMS320C5XX__) || defined(__TMS320C2000__)
#define _BITS_BYTE	16
#define _C2		1	/* 0 if not 2's complement */
#define _MBMAX		8	/* MB_LEN_MAX */
#define _ILONG		0	/* 0 if 16-bit int */
#elif defined(__MSP430__) || defined(__TMS320C55X_PLUS_BYTE__)
#define _BITS_BYTE	8
#define _C2		1	/* 0 if not 2's complement */
#define _MBMAX		8	/* MB_LEN_MAX */
#define _ILONG		0	/* 0 if 16-bit int */
#else
#define _BITS_BYTE	8
#define _C2		1	/* 0 if not 2's complement */
#define _MBMAX		8	/* MB_LEN_MAX */
#define _ILONG		1	/* 0 if 16-bit int */
#endif /* defined(__TMS320C55X__) || defined(__TMS320C5XX__) || defined(__TMS320C2000__) */

 #if defined(__s390__) || defined(__CHAR_UNSIGNED__)  \
	|| defined(_CHAR_UNSIGNED) 
  #define _CSIGN	0	/* 0 if char is not signed */ 
 #else /* defined(__s390__) etc */
  #define _CSIGN	1
 #endif /* defined(__s390__) etc */

#define _MAX_EXP_DIG	8	/* for parsing numerics */
#define _MAX_INT_DIG	32
#define _MAX_SIG_DIG	36

 #if defined(_LONGLONG)
typedef _LONGLONG _Longlong;
typedef _ULONGLONG _ULonglong;

 #else /* defined(_LONGLONG) */
     typedef long long _Longlong;
     typedef unsigned long long  _ULonglong; 
     #define _LLONG_MAX  0x7fffffffff
     #define _ULLONG_MAX 0xffffffffff      
 #endif /* defined(_LONGLONG) */

		/* wchar_t AND wint_t PROPERTIES */
 #if defined(_WCHAR_T) || defined(_WCHAR_T_DEFINED) \
	|| defined (_MSL_WCHAR_T_TYPE)
  #define _WCHART
 #endif /* defined(_WCHAR_T) || defined(_WCHAR_T_DEFINED) */

 #if defined(_WINT_T)
  #define _WINTT
 #endif /* _WINT_T */

 #ifdef __cplusplus
  #define _WCHART
typedef wchar_t _Wchart;
typedef wchar_t _Wintt;
 #endif /* __cplusplus */

 #if defined(__WCHAR_TYPE__)
  #define _WCMIN	(-_WCMAX - _C2)
  #define _WCMAX	0x7fffffff	/* assume signed 32-bit wchar_t */

  #ifndef __cplusplus
typedef __WCHAR_TYPE__ _Wchart;
typedef __WCHAR_TYPE__ _Wintt;
  #endif /* __cplusplus */
/******************************************************************************/
/* Here we define the _Wchart _Wintt for TI processors, they are all defined  */
/* as 16 bit unsigned integer type by the predefined macro __WCHAR_T_TYPE__   */
/******************************************************************************/
 #elif defined(__TI_COMPILER_VERSION__)
    #ifndef __cplusplus
       typedef __WCHAR_T_TYPE__ _Wchart;
       typedef __WCHAR_T_TYPE__ _Wintt;
    #endif /* __cplusplus */
    #define _WCMIN	0
    #define _WCMAX	0xffff
 #else /* default wchar_t/wint_t */
  #define _WCMIN	(-_WCMAX - _C2)
  #define _WCMAX	0x7fffffff

  #ifndef __cplusplus
typedef long _Wchart;
typedef long _Wintt;
  #endif /* __cplusplus */

 #endif /* compiler/library type */

		/* POINTER PROPERTIES */
#define _NULL		0	/* 0L if pointer same as long */

		/* signal PROPERTIES */

#define _SIGABRT	6
#define _SIGMAX		44

		/* stdarg PROPERTIES */
typedef _CSTD va_list _Va_list;

 #if _HAS_C9X

 #if __EDG__
  #undef va_copy
 #endif /* __EDG__ */

 #ifndef va_copy
_EXTERN_C
void _Vacopy(va_list *, va_list);
_END_EXTERN_C
  #define va_copy(apd, aps)	_Vacopy(&(apd), aps)
 #endif /* va_copy */

 #endif /* _IS_C9X */
		/* stdlib PROPERTIES */
#define _EXFAIL	1	/* EXIT_FAILURE */

_EXTERN_C
void _Atexit(void (*)(void));
_END_EXTERN_C

		/* stdio PROPERTIES */
#define _FNAMAX	256           /* Dinkum original value 260 */
#define _FOPMAX	10            /* Dinkum original value 20 */
#define _TNAMAX	16

 #define _FD_TYPE	signed char
  #define _FD_NO(str) ((str)->_Handle)
 #define _FD_VALID(fd)	(0 <= (fd))	/* fd is signed integer */
 #define _FD_INVALID	(-1)
 #define _SYSCH(x)	x
typedef char _Sysch_t;

		/* STORAGE ALIGNMENT PROPERTIES */
#define _MEMBND	3U /* eight-byte boundaries (2^^3) */

		/* time PROPERTIES */
  #define _CPS 200000000 /* 200 Mhz */
  #define _TBIAS	0
_C_STD_END

		/* MULTITHREAD PROPERTIES */
 #if _MULTI_THREAD
_EXTERN_C
void _Locksyslock(int);
void _Unlocksyslock(int);
_END_EXTERN_C

 #else /* _MULTI_THREAD */
   #if defined(__TI_COMPILER_VERSION__)
     #define _Locksyslock(x)   _lock()
     #define _Unlocksyslock(x) _unlock()
   #else /*!defined(__TI_COMPILER_VERSION__) */
     #define _Locksyslock(x)	(void)0
     #define _Unlocksyslock(x)	(void)0
   #endif /* defined(__TI_COMPILER_VERSION__)  */
 #endif /* _MULTI_THREAD */

		/* LOCK MACROS */
 #define _LOCK_LOCALE	0
 #define _LOCK_MALLOC	1
 #define _LOCK_STREAM	2
 #define _LOCK_DEBUG	3
 #define _MAX_LOCK		4	/* one more than highest lock number */

 #if _IOSTREAM_OP_LOCKS
  #define _MAYBE_LOCK

 #else /* _IOSTREAM_OP_LOCKS */
  #define _MAYBE_LOCK	\
	if (_Locktype == _LOCK_MALLOC || _Locktype == _LOCK_DEBUG)
 #endif /* _IOSTREAM_OP_LOCKS */

 #ifdef __cplusplus
_STD_BEGIN
extern "C++" {	// in case of _C_AS_CPP
		// CLASS _Lockit
class _Lockit
	{	// lock while object in existence -- MUST NEST
public:

  #if !_MULTI_THREAD
   #define _LOCKIT(x)

	explicit _Lockit()
		{	// do nothing
		}

	explicit _Lockit(int)
		{	// do nothing
		}

	~_Lockit()
		{	// do nothing
		}

  #else /* non-Windows multithreading */
   #define _LOCKIT(x)	lockit x

	explicit _Lockit()
		: _Locktype(_LOCK_MALLOC)
		{	// set default lock
		_MAYBE_LOCK
			_Locksyslock(_Locktype);
		}

	explicit _Lockit(int _Type)
		: _Locktype(_Type)
		{	// set the lock
		_MAYBE_LOCK
			_Locksyslock(_Locktype);
		}

	~_Lockit()
		{	// clear the lock
		_MAYBE_LOCK
			_Unlocksyslock(_Locktype);
		}

private:
	int _Locktype;
  #endif /* _MULTI_THREAD */

public:
	_Lockit(const _Lockit&);			// not defined
	_Lockit& operator=(const _Lockit&);	// not defined
	};

class _Mutex
	{	// lock under program control
public:

  #if !_MULTI_THREAD || !_IOSTREAM_OP_LOCKS
    void _Lock()
		{	// do nothing
		}

	void _Unlock()
		{	// do nothing
	}

  #else /* !_MULTI_THREAD || !_IOSTREAM_OP_LOCKS */
	_Mutex();
	~_Mutex();
	void _Lock();
	void _Unlock();

private:
	_Mutex(const _Mutex&);				// not defined
	_Mutex& operator=(const _Mutex&);	// not defined
	void *_Mtx;
  #endif /* !_MULTI_THREAD || !_IOSTREAM_OP_LOCKS */

	};
}	// extern "C++"
_STD_END
 #endif /* __cplusplus */

		/* MISCELLANEOUS MACROS */
#define _ATEXIT_T	void

#define _MAX	max
#define _MIN	min

#define _TEMPLATE_STAT

  #define _NO_RETURN(fun)	void fun

 #if _HAS_NAMESPACE

 #ifdef __cplusplus
  #ifndef _STDARG
  #if defined(_STD_USING)
_STD_BEGIN
using _CSTD va_list;
_STD_END
  #endif /* !defined(_C_AS_CPP) && defined(_GLOBAL_USING) */
  #endif /* _STDARG */
 #endif /* __cplusplus */
 #endif /* _HAS_NAMESPACE */

#if defined(__TI_COMPILER_VERSION__)
#include <linkage.h>
#ifndef __LOCK_H
#include <_lock.h>
#endif /* __LOCK_H */
#endif /* defined(__TI_COMPILER_VERSION__) */

#endif /* _YVALS */

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */

