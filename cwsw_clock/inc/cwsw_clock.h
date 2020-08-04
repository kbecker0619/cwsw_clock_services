/** @file
 *	@brief	CWSW Clock Module
 *
 *	Description:
 *
 *	\copyright
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Sep 5, 2016
 *	Author: Kevin L. Becker
 */

#ifndef CWSW_CLOCK_H
#define CWSW_CLOCK_H

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include <time.h>
#include <stdint.h>

// ----	Project Headers -------------------------
#include "cwsw_evqueue_ex.h"	/* tEvQ_Event, et. al. */

// ----	Module Headers --------------------------


#ifdef	__cplusplus
extern "C" {
#endif


// ============================================================================
// ----	Constants -------------------------------------------------------------
// ============================================================================

enum { Cwsw_ClockSvc_TicResolution = 1 };	//!< number of milliseconds per clock tic

enum eErrorCodes_ClkSvc {
	kErr_ClkSvc_NoError = kErr_Lib_NoError,
	kerr_ClkSvc_NotInitialized,
	kerr_ClkSvc_BadParm,
};


// ============================================================================
// ----	Type Definitions ------------------------------------------------------
// ============================================================================

typedef enum eErrorCodes_ClkSvc tClkSvc_ErrorCode;


#if defined(_CVI_)
typedef signed long tCwswClockTics, *pCwswClockTics;

#else
/*	building on windows, for windows, we can take advantage of MinGW's
 *	time.h...
 */
typedef clock_t tCwswClockTics, *pCwswClockTics;

#endif


// ============================================================================
// ----	Public Variables ------------------------------------------------------
// ============================================================================

extern tCwswClockTics simclock;


// ============================================================================
// ----	Public API ------------------------------------------------------------
// ============================================================================

#if 0
#define CLOCK()		clock()
#else
#define CLOCK()		(simclock++)
#endif


// ---- Discrete Functions -------------------------------------------------- {

/**	Initialize Clock Services module.
 *
 *	@param [in]	pEvQX			Reference to an extended event queue.
 *	@param [in]	HeatbeatEvId	Event to post when it's time to issue a timer tic.
 *
 *	While the name format complies with the init signature for sister CWSW
 *	components, but this function requires 2 parameters, so we can't use the
 *	`Init(component)` API.
 *
 *	@note	We need to know about CWSW event queues, but because we want to
 *	support a system that might use a different event queue for OS events than
 *	it does for application events, we'll use a generic container for the event
 *	parameter.
 */
extern void Cwsw_ClockSvc__Init(ptEvQ_QueueCtrlEx pEvQX, int16_t HeatbeatEvId);

/** Task function for clock services.
 *	For systems which have an interrupt-driven timer tic, this function's major purpose is to post
 *	an event for each timer tic. For polled systems, this is the main workhorse for all SW timers
 *	and alarms and it is quite important to poll as quickly as possible.
 *
 *	If a valid OS event queue is referenced (specified in the init call), we post an OS event on
 *	every change; we assume this is a 1 ms resolution, though nothing (as yet) depends on this
 *	identity.
 *
 *	@returns Number of clock tics since initialization.
 */
extern tCwswClockTics Cwsw_ClockSvc__Task(void);

/**	Return the current clock tic.
 *	@returns Raw tic value. For polled systems, this may be related to the time of day; for systems
 *			with an interrupt-driven system tic, this will probably be the number of tics since
 *			initialization.
 *	@note Requires regular calls and a high timer tic resolution; assumption is 1ms.
 */
extern tCwswClockTics Cwsw_ClockSvc__TimerTic(void);

/**	Set the duration of a timer.
 *	@param[out]	timer		Reference to the specified timer.
 *	@param[in]	duration	Duration of the timer in timer tics. Negative values are not possible.
 *	@returns Error code, where 0 is no error.
 */
extern tClkSvc_ErrorCode Cwsw_ClockSvc__SetTimer(pCwswClockTics pTimer, tCwswClockTics duration);

/**	Return the number of ms between start and stop times.
 * 	@note Assumptions:
 * 	- We are assuming there is 1 clock tic per ms; this is what is true for MinGW and so of course
 * 	  that means the whole world does it the same way.
 * 	- The math only works for 2s-complement encodings; 1s-complement and sign-magnitude will need to
 * 	  find another way.
 */
#define Cwsw_ElapsedTimeMs(start, stop)	(tCwswClockTics)(stop - start)

/**	Get the time left in a specified timer.
 *
 *	@param timer - the timer to be inspected.
 *
 * 	@returns the time left in said timer.
 *	Negative values indicate expiration of timer.
 *
 *	@note In usage, do not compare one time directly to another.
 *	Doing this will not properly handle timer tic rollover.
 *	Instead, subtract one time from another, and compare the result to zero.
 */
#define Cwsw_GetTimeLeft(timer)		Cwsw_ElapsedTimeMs(Cwsw_ClockSvc__TimerTic(), timer)

/** Return the maximum number of missed task iterations.
 */
extern tCwswClockTics Cwsw_ClockSvc__GetMaxMissedTics(void);

// ---- /Discrete Functions ------------------------------------------------- }

// ---- Targets for Get/Set APIs -------------------------------------------- {
/** "Chapter Designator" for Get/Set API.
 *	Intentionally unused symbol, designed to get you to the correct starting
 *	point, when you want to find macros for the Get/Set API; simply highlight
 *	the Module argument in your IDE (e.g, Eclipse, NetBeans, etc.), and select
 *	Go To Definition.
 */
enum { Cwsw_ClockSvc, Cwsw_Clock };	/* Component ID for Clock Services */

/**	Target for Set(Cwsw_Clock, timer, duration) API.
 */
#define Cwsw_Clock__Set(timer, timeout)		Cwsw_ClockSvc__SetTimer(&timer, timeout)

/** Target for Get(Cwsw_Clock, timer) API.
 */
#define Cwsw_Clock__Get(timer)				Cwsw_GetTimeLeft(timer)

/** Target for Get(Cwsw_ClockSvc, CurrentTime)
 */
#define Cwsw_ClockSvc__Get(CurrentTime)		Cwsw_ClockSvc__TimerTic()


/**	Determine if timer "a" has expired (i.e., matured) or not.
 *	@param   a - name of timer
 *	@return  Boolean where TRUE indicates the timer has indeed expired.
 */
//  Expansion of HAS_TIMER_EXPIRED(TIMER_NAME)
//! @{
#define HAS_TIMER_EXPIRED(a)            	_HAS_TIMER_EXPIRED(a)
#define _HAS_TIMER_EXPIRED(a)           	(GET(a) <= 0)
//! @}

/**	Has a timer expired?
 *	This definition provided to accommodate UML notation.
 */
#define TM(tmr)                         	HAS_TIMER_EXPIRED(tmr)

// ---- /Targets for Get/Set APIs ------------------------------------------- }


#ifdef	__cplusplus
}
#endif

#endif /* CWSW_CLOCK_H */
