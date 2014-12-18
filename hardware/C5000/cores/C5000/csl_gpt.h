/* ============================================================================
 * Copyright (c) 2008-2012 Texas Instruments Incorporated.
 * Except for those rights granted to you in your license from TI, all rights
 * reserved.
 *
 * Software License Agreement
 * Texas Instruments (TI) is supplying this software for use solely and
 * exclusively on TI devices. The software is owned by TI and/or its suppliers,
 * and is protected under applicable patent and copyright laws.  You may not
 * combine this software with any open-source software if such combination would
 * cause this software to become subject to any of the license terms applicable
 * to such open source software.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
 * NO WARRANTIES APPLY TO THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY.
 * EXAMPLES OF EXCLUDED WARRANTIES ARE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE AND WARRANTIES OF NON-INFRINGEMENT,
 * BUT ALL OTHER WARRANTY EXCLUSIONS ALSO APPLY. FURTHERMORE, TI SHALL NOT,
 * UNDER ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, CONSEQUENTIAL
 * OR PUNITIVE DAMAGES, FOR ANY REASON WHATSOEVER.
 * ============================================================================
 */

/** @file csl_gpt.h
 *
 *  @brief Functional layer API header file for GPT CSL
 *
 *  Path: \(CSLPATH)/inc
 */

/* ============================================================================
 * Revision History
 * ================
 * 28-Sep-2008 Added GPT for CSL.
 * 13-Aug-2010 CSL v2.10 release
 * 06-Jul-2011 CSL v2.50 release
 * 13-Sep-2012 CSL v3.00 release
 * 20-Dec-2012 CSL v3.01 release
 * ============================================================================
 */

/** @defgroup CSL_GPT_API GPT
 *
 * @section Introduction
 *
 * @subsection GPT Overview
 * C5505 includes three 32-bit timer with 13-bit prescaler that can divide the
 * CPU clock and uses this scaled value as a reference clock.
 *
 */

#ifndef _CSL_GPT_H_
#define _CSL_GPT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "soc.h"
#include "csl_error.h"
#include "csl_types.h"
#include "csl_general.h"

/**
@defgroup CSL_GPT_SYMBOL  GPT Symbols Defined
@ingroup CSL_GPT_API
*/

/**
@defgroup CSL_GPT_DATASTRUCT  GPT Data Structures
@ingroup CSL_GPT_API
*/

/**
@defgroup CSL_GPT_ENUM GPT Enumerated Data Types
@ingroup CSL_GPT_API
*/

/**
@defgroup CSL_GPT_FUNCTION  GPT Functions
@ingroup CSL_GPT_API
*/

/*****************************************************************************\
          GPT global macro declarations
\*****************************************************************************/
/** @addtogroup CSL_GPT_SYMBOL
 @{ */

/** IAFR flag for GPT 0														*/
#define CSL_IAFR_TIMER_FLAG_0_RESETVAL (0x0001u)
/** IAFR flag for GPT 1														*/
#define CSL_IAFR_TIMER_FLAG_1_RESETVAL (0x0002u)
/** IAFR flag for GPT 2														*/
#define CSL_IAFR_TIMER_FLAG_2_RESETVAL (0x0004u)
/** IAFR flag for GPT 0,1 &2												*/
#define CSL_IAFR_TIMER_FLAG_0_1_2_RESETVAL (0x0007u)

/**
@} */


/**************************************************************************\
* GPT global typedef declarations                                         *
\**************************************************************************/

/** @addtogroup CSL_GPT_ENUM
@{ */

/**
 * \brief Instance number.
 *
 * Enumeration for instance number (maximum 3 instance).
 */
typedef enum{
	GPT_0 = 0,		/**< Timer instace 0						*/
	GPT_1,			/**< Timer instace 1						*/
	GPT_2,			/**< Timer instace 2						*/
	GPT_INVALID		/**< Timer Invalid Instance					*/
}CSL_Instance;

/**
 * \brief Autoload Timer Mode.
 *
 * Enumeration for auto load timer enable or disable.
 */
typedef enum{
	GPT_AUTO_DISABLE = 0,	/**< Auto re-load disable				*/
	GPT_AUTO_ENABLE			/**< Auto re-load enable				*/
}CSL_AutoReLoad;


/**
 * \brief Timer enable/disable.
 *
 * Enumeration for pre-scale functionality timer enable or disable.
 */
typedef enum{
	GPT_TIMER_DISABLE = 0,	/**< Pre scale timer disable			*/
	GPT_TIMER_ENABLE 		/**< Pre scale timer enable				*/
}CSL_CtrlTimer;

/**
 * \brief Pre-Scale division.
 *
 * Enumeration for pre-scale devider value.
 */
typedef enum{
	GPT_PRE_SC_DIV_0 = 0,	/**< Pre scale Divide input clock by 2		*/
	GPT_PRE_SC_DIV_1,		/**< Pre scale Divide input clock by 4		*/
	GPT_PRE_SC_DIV_2,		/**< Pre scale Divide input clock by 8		*/
	GPT_PRE_SC_DIV_3,		/**< Pre scale Divide input clock by 16		*/
	GPT_PRE_SC_DIV_4,		/**< Pre scale Divide input clock by 32		*/
	GPT_PRE_SC_DIV_5,		/**< Pre scale Divide input clock by 64		*/
	GPT_PRE_SC_DIV_6,		/**< Pre scale Divide input clock by 128	*/
	GPT_PRE_SC_DIV_7,		/**< Pre scale Divide input clock by 256	*/
	GPT_PRE_SC_DIV_8,		/**< Pre scale Divide input clock by 512	*/
	GPT_PRE_SC_DIV_9,		/**< Pre scale Divide input clock by 1024	*/
	GPT_PRE_SC_DIV_10,		/**< Pre scale Divide input clock by 2048	*/
	GPT_PRE_SC_DIV_11,		/**< Pre scale Divide input clock by 4096	*/
	GPT_PRE_SC_DIV_12,		/**< Pre scale Divide input clock by 8192	*/
	GPT_PRE_SC_DIV_RESERVE	/**< Reserve								*/
}CSL_PreScale;

/**
@} */


/**
\addtogroup CSL_GPT_DATASTRUCT
@{ */

/**
 * \brief Configuration structure.
 *
 * Contains the Information of a GPT configuration.
 */
typedef struct{
	CSL_AutoReLoad	autoLoad;      /**< Auto reload						*/
	CSL_PreScale	preScaleDiv;   /**< Prescale division				*/
	CSL_CtrlTimer	ctrlTim;       /**< control timer					*/
	Uint16			prdLow;        /**< period low						*/
	Uint16			prdHigh;       /**< period high						*/
}CSL_Config;

/**
 * \brief Object structure.
 *
 * Contains the Information of a GPT object handler.
 */
typedef struct {
	CSL_Instance	Instance;   /**< Instance               		*/
	Uint16			EventId;	/**< Event tigger for Interrupt		*/
	CSL_TimRegsOvly	regs;		/**< GPT hardware registers			*/
} CSL_GptObj;

/**
 * \brief GPT CSL handle
 */
typedef CSL_GptObj *CSL_Handle;


/**
@} */


/******************************************************************************
 * GPT function declarations
 *****************************************************************************/

/** @addtogroup CSL_GPT_FUNCTION
 @{ */
/** ===========================================================================
 *   @n@b GPT_open
 *
 *   @b Description
 *   @n This is the initialization function for the GPT CSL. The function
 *      must be called before calling any other API from this CSL. This
 *      function is idem-potent. Currently, the function just returns handler
 *      to application.
 *
 *   @b Arguments
 *   @verbatim
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                        CSL_SOK - Always returns
 *
 *	                        CSL_Handle
 *                              Pointer to the object structure.
 *   <b> Pre Condition </b>
 *   @n  This should be call first before calling any other GPT Function.
 *
 *   <b> Post Condition </b>
 *   @n  The status is updated in the status variable. If status
 *        returned is
 *   @li        CSL_SOK            - Valid GPT handle is returned
 *   @li        CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *   @b Modifies
 *   @n 1. The status variable
 *   @n 2. The object structure handler.
 *
 *   @b Example
 *   @verbatim
            CSL_Handle		hgpt;
            CSL_Instance	instance;
			CSL_GptObj		gptObj;
		  	CSL_Status 		status;
			....
			....
			instance = GPT_0.

            hgpt = GPT_open(GPT_0, &gptObj, &status);
     @endverbatim
 *  ===========================================================================
 */
CSL_Handle GPT_open(CSL_Instance	instance,
					CSL_GptObj		*gptObj,
		  			CSL_Status 		*status);

/** ===========================================================================
 *   @n@b GPT_reset
 *
 *   @b Description
 *   @n This function reset specific register to GPT.
 *
 *   @b Arguments
 *   @verbatim
            hGpt            Handle to the GPT
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Close successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  GPT_open() must be called before this function call.
 *
 *   <b> Post Condition </b>
 *   @n  After calling this function  GPT_close() API should call to close
 *      gpt operation.
 *
 *   @b Modifies
 *   @n    1. The object structure handler.
 *
 *   @b Example
 *   @verbatim
            CSL_status           status;
            CSL_Handle 			 hGpt;
            ...

           hgpt = GPT_open(GPT_0, &gptObj, &status);
           status = GPT_reset(hgpt);
     @endverbatim
 *  ===========================================================================
 */
CSL_Status GPT_reset(CSL_Handle hGpt);

/** ===========================================================================
 *   @n@b GPT_close
 *
 *   @b Description
 *   @n This function close GPT operation.
 *
 *   @b Arguments
 *   @verbatim
            hGpt            Handle to the GPT
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Close successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  GPT_open() must be called before this function call.
 *
 *   <b> Post Condition </b>
 *   @n  After calling this function no other function can call.
 *
 *   @b Modifies
 *   @n    None
 *
 *   @b Example
 *   @verbatim
            CSL_status           status;
            CSL_Handle 			 hGpt;
            ...

           hgpt = GPT_open(GPT_0, &gptObj, &status);
           status = GPT_close(hgpt);
     @endverbatim
 *  ===========================================================================
 */
CSL_Status GPT_close(CSL_Handle hGpt);


/** ===========================================================================
 *   @n@b GPT_start
 *
 *   @b Description
 *   @n This function start to load value from period register to
 *      count down register.
 *
 *   @b Arguments
 *   @verbatim
            hGpt            Handle to the GPT
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Close successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  GPT_config() must be called before this function call.
 *
 *   <b> Post Condition </b>
 *   @n  After calling this function GPT_stop() function can call to
 *       stop loading from period register to countdown register.
 *
 *   @b Modifies
 *   @n    None
 *
 *   @b Example
 *   @verbatim
            CSL_status           status;
            CSL_Handle 			 hGpt;
            ...

           hgpt = GPT_config(hGpt, &hwConfig);
           status = GPT_start(hgpt);
     @endverbatim
 *  ===========================================================================
 */
CSL_Status GPT_start(CSL_Handle hGpt);

/** ===========================================================================
 *   @n@b GPT_stop
 *
 *   @b Description
 *   @n This function stop to load value from period register to
 *      count down register.
 *
 *   @b Arguments
 *   @verbatim
            hGpt            Handle to the GPT
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Close successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  GPT_config() must be called before this function call.
 *
 *   <b> Post Condition </b>
 *   @n  After calling this function  GPT_close() API should call to close
 *      gpt operation.
 *
 *   @b Modifies
 *   @n    None
 *
 *   @b Example
 *   @verbatim
            CSL_status           status;
            CSL_Handle 			 hGpt;
            ...

           status = GPT_start(hgpt);
		   status = GPT_stop(hgpt);
     @endverbatim
 *  ===========================================================================
 */
CSL_Status GPT_stop(CSL_Handle hGpt);

/** ===========================================================================
 *   @n@b GPT_getCnt
 *
 *   @b Description
 *   @n This function is to get condown value from countdown register
 *
 *   @b Arguments
 *   @verbatim
            hGpt            Handle to the GPT
			timeCnt         Pointer to the countdown value
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Close successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  GPT_start() must be called before this function call.
 *
 *   <b> Post Condition </b>
 *   @n  After calling this function  GPT_close() API should call to close
 *      gpt operation.
 *
 *   @b Modifies
 *   @n    None
 *
 *   @b Example
 *   @verbatim
            CSL_status           status;
            CSL_Handle 			 hGpt;
            Uint32               timeCnt;
            ...

           status = GPT_start(hgpt);
		   status = GPT_getCnt(hgpt, &timeCnt);
     @endverbatim
 *  ===========================================================================
 */
CSL_Status GPT_getCnt(CSL_Handle hGpt, Uint32 *timeCnt);

/** ===========================================================================
 *   @n@b GPT_config
 *
 *   @b Description
 *   @n This function is to Configure the GPT haware related registers
 *
 *   @b Arguments
 *   @verbatim
            hGpt            Handle to the GPT
			hwConfig        configuration structure.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Close successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  GPT_open() must be called before this function call.
 *
 *   <b> Post Condition </b>
 *   @n  After calling this function  GPT_reset() API should call to close
 *      gpt operation.
 *
 *   @b Modifies
 *   @n    This function modifies the GPT object structure.
 *
 *   @b Example
 *   @verbatim
            CSL_status           status;
            CSL_Handle 			 hGpt;
             CSL_Config          hwConfig;
            ...
			hwConfig.autoLoad 		= GPT_AUTO_ENABLE;
	        hwConfig.ctrlTim 		= GPT_TIMER_ENABLE;
	        hwConfig.preScaleDiv 	= GPT_PRE_SC_DIV_3;
	        hwConfig.prdLow 		= 0xFFFF;
	        hwConfig.prdHigh 		= 0x0000;

           hgpt = GPT_open(GPT_0, &gptObj, &status);
		   status = GPT_config(hgpt, &hwConfig);
     @endverbatim
 *  ===========================================================================
 */
CSL_Status GPT_config(CSL_Handle hGpt, CSL_Config *hwConfig);
/**
@} */

#ifdef __cplusplus
}
#endif

#endif /* _CSL_GPT_H_ */



