/* stdbool.h standard header */
#ifndef _STDBOOL
#define _STDBOOL
#ifndef _YVALS
 #include <yvals.h>
#endif /* _YVALS */

_C_STD_BEGIN

 #define __bool_true_false_are_defined	1

 #ifndef __cplusplus
		/* TYPES */

 #if 199901L <= __STDC_VERSION__


 #else /* 199901L <= __STDC_VERSION__ */
#if __TI_STRICT_ANSI_MODE__
typedef unsigned int _Bool;
#endif
 #endif /* 199901L <= __STDC_VERSION__ */

		/* MACROS */
 #define bool	_Bool
 #define false	0
 #define true	1
 #endif /* __cplusplus */

_C_STD_END
#endif /* _STDBOOL */

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
