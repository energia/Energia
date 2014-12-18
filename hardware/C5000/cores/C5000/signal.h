/* signal.h standard header */
#ifndef _SIGNAL
#define _SIGNAL
#ifndef _YVALS
 #include <yvals.h>
#endif /* _YVALS */



_C_STD_BEGIN


		/* SIGNAL CODES */
#define SIGABRT	_SIGABRT
#define SIGINT	2
#define SIGILL	4
#define SIGFPE	8
#define SIGSEGV	11
#define SIGTERM	15
#define _NSIG	_SIGMAX	/* one more than last code */

		/* SIGNAL RETURN VALUES */
#define SIG_DFL	((_CSTD _Sigfun *)0)
#define SIG_ERR	((_CSTD _Sigfun *)-1)
#define SIG_IGN	((_CSTD _Sigfun *)1)

_EXTERN_C
		/* TYPE DEFINITIONS */

typedef int sig_atomic_t;


typedef void _Sigfun(int);

		/* LOW-LEVEL FUNCTIONS */
_Sigfun * signal(int, _Sigfun *);
_END_EXTERN_C

_C_LIB_DECL		/* DECLARATIONS */
int raise(int);
_END_C_LIB_DECL
_C_STD_END
#endif /* _SIGNAL */

#ifdef _STD_USING
using _CSTD sig_atomic_t; using _CSTD raise; using _CSTD signal;
#endif /* _STD_USING */

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
