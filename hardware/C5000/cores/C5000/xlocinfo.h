/* xlocinfo.h internal header for gcc Linux */
#ifndef _XLOCINFO
#define _XLOCINFO
#include <locale.h>
#ifndef _YVALS
#include <yvals.h>
#endif

_C_STD_BEGIN
_C_LIB_DECL

		/* CTYPE CODE BITS */
#ifndef _XB
 #define _XB	0x400 /* extra blank */
 #define _XA	0x200 /* extra alphabetic */
 #define _XS	0x100 /* extra space */
 #define _BB	0x80 /* BEL, BS, etc. */
 #define _CN	0x40 /* CR, FF, HT, NL, VT */
 #define _DI	0x20 /* '0'-'9' */
 #define _LO	0x10 /* 'a'-'z' */
 #define _PU	0x08 /* punctuation */
 #define _SP	0x04 /* space */
 #define _UP	0x02 /* 'A'-'Z' */
 #define _XD	0x01 /* '0'-'9', 'A'-'F', 'a'-'f' */
#endif /* _XB */

		/* SUPPLEMENTAL LOCALE MACROS AND DECLARATIONS */

 #if defined(__BORLANDC__) || defined(__MWERKS__)
  #define _X_COLLATE	0
  #define _X_CTYPE		1
  #define _X_MONETARY	2
  #define _X_NUMERIC	3
  #define _X_TIME 		4
  #define _X_MESSAGES	5
  #define _X_MAX		_X_MESSAGES	/* highest real category */
  #define _CAT_TO_LC(cat)	_CATMASK(cat)

 #else	/* defined(__BORLANDC__) etc. */
  #define _X_COLLATE	LC_COLLATE
  #define _X_CTYPE		LC_CTYPE
  #define _X_MONETARY	LC_MONETARY
  #define _X_NUMERIC	LC_NUMERIC
  #define _X_TIME 		LC_TIME
  #define _X_MESSAGES	LC_MESSAGES
  #define _X_MAX		_X_MESSAGES	/* highest real category */
#endif /* defined(_BORLANDC_) etc. */

#ifndef _NCAT
 #define _NCAT			(_X_MESSAGES + 1)	/* maximum + 1 */

  #define _CATMASK(n)	\
	(1 << ((n) - (_X_COLLATE < _X_CTYPE ? _X_COLLATE : _X_CTYPE)))

 #define _M_COLLATE		_CATMASK(_X_COLLATE)
 #define _M_CTYPE		_CATMASK(_X_CTYPE)
 #define _M_MONETARY	_CATMASK(_X_MONETARY)
 #define _M_NUMERIC		_CATMASK(_X_NUMERIC)
 #define _M_TIME		_CATMASK(_X_TIME)
 #define _M_MESSAGES	_CATMASK(_X_MESSAGES)
 #define _M_ALL			(_CATMASK(_NCAT) - 1)
#endif /* _NCAT */

		/* FUNCTION DECLARATIONS */
const short *_Getctyptab();
extern float _Stof(const char *, char **, long);
extern double _Stod(const char *, char **, long);
extern long double _Stold(const char *, char **, long);
_END_C_LIB_DECL
_C_STD_END
#endif /* _XLOCINFO */

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
