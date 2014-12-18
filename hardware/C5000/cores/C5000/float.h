/********************************************************************/
/* float.h  v4.4.1                                                  */
/*                                                                  */
/* Copyright (c) 1996-2012 Texas Instruments Incorporated           */
/* http://www.ti.com/                                               */
/*                                                                  */
/*  Redistribution and  use in source  and binary forms, with  or without */
/*  modification,  are permitted provided  that the  following conditions */
/*  are met:                                                        */
/*                                                                  */
/*     Redistributions  of source  code must  retain the  above copyright */
/*     notice, this list of conditions and the following disclaimer. */
/*                                                                  */
/*     Redistributions in binary form  must reproduce the above copyright */
/*     notice, this  list of conditions  and the following  disclaimer in */
/*     the  documentation  and/or   other  materials  provided  with  the */
/*     distribution.                                                */
/*                                                                  */
/*     Neither the  name of Texas Instruments Incorporated  nor the names */
/*     of its  contributors may  be used to  endorse or  promote products */
/*     derived  from   this  software  without   specific  prior  written */
/*     permission.                                                  */
/*                                                                  */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */
/*                                                                  */
/*    KEY:  FLT_     - APPLIES TO TYPE FLOAT                        */
/*          DBL_     - APPLIES TO TYPE DOUBLE                       */
/*          LDBL_    - APPLIES TO TYPE LONG DOUBLE                  */
/********************************************************************/
#ifndef _FLOAT
#define _FLOAT

#define FLT_RADIX                         2   /* RADIX OF EXPONENT         */
#define FLT_ROUNDS                        1   /* ROUND TO NEAREST          */

#define FLT_DIG                           6   /* DECIMAL PRECISION         */
#define FLT_MANT_DIG                     24   /* BITS IN MANTISSA          */
#define FLT_MIN_EXP                    -125   /* SMALLEST EXPONENT         */
#define FLT_MAX_EXP                     128   /* LARGEST EXPONENT          */
#define FLT_EPSILON        1.192092896E-07F   /* SMALLEST X WHERE 1+X != 1 */
#define FLT_MIN            1.175494351E-38F   /* SMALLEST POSITIVE VALUE   */
#define FLT_MAX            3.402823466E+38F   /* LARGEST POSITIVE VALUE    */
#define FLT_MIN_10_EXP                  -37   /* MIN POWER OF 10           */
#define FLT_MAX_10_EXP                   38   /* MAX POWER OF 10           */

#define DBL_DIG                           6   /* DECIMAL PRECISION         */
#define DBL_MANT_DIG                     24   /* BITS IN MANTISSA          */
#define DBL_MIN_EXP                    -125   /* SMALLEST EXPONENT         */
#define DBL_MAX_EXP                     128   /* LARGEST EXPONENT          */
#define DBL_EPSILON        1.192092896E-07F   /* SMALLEST X WHERE 1+X != 1 */
#define DBL_MIN            1.175494351E-38F   /* SMALLEST POSITIVE VALUE   */
#define DBL_MAX            3.402823466E+38F   /* LARGEST POSITIVE VALUE    */
#define DBL_MIN_10_EXP                  -37   /* MIN POWER OF 10           */
#define DBL_MAX_10_EXP                   38   /* MAX POWER OF 10           */

#define LDBL_DIG                          6   /* DECIMAL PRECISION         */
#define LDBL_MANT_DIG                    24   /* BITS IN MANTISSA          */
#define LDBL_MIN_EXP                   -125   /* SMALLEST EXPONENT         */
#define LDBL_MAX_EXP                    128   /* LARGEST EXPONENT          */
#define LDBL_EPSILON       1.192092896E-07F   /* SMALLEST X WHERE 1+X != 1 */
#define LDBL_MIN           1.175494351E-38F   /* SMALLEST POSITIVE VALUE   */
#define LDBL_MAX           3.402823466E+38F   /* LARGEST POSITIVE VALUE    */
#define LDBL_MIN_10_EXP                 -37   /* MIN POWER OF 10           */
#define LDBL_MAX_10_EXP                  38   /* MAX POWER OF 10           */

#endif
