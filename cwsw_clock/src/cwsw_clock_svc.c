/** @file
 *	@brief	CWSW Clock Module
 *
 *	Description:
 *	Requires support of a hardware time module.
 *
 *	\copyright
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Created on: Sep 1, 2016
 *	@author Kevin L. Becker
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------

// ----	Project Headers -------------------------
#include "projcfg.h"

// ----	Module Headers --------------------------
#include "cwsw_clock.h"


// ============================================================================
// ----	Constants -------------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Type Definitions ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Global Variables ------------------------------------------------------
// ============================================================================

tCwswClockTics simclock = 0;


// ============================================================================
// ----	Module-level Variables ------------------------------------------------
// ============================================================================

static ptEvQ_QueueCtrlEx	pOsEvQX = NULL;
static tEvQ_Event			ev_os_heartbeat = {0};

/** Offset between value returned by clock(), and the number of tics since initialization.
 */
static tCwswClockTics	clockoffset = 0;

/** Current timer tic. */
static tCwswClockTics	thistic;

/** Maximum observed "missed" timer tics.
 *	For an interrupt-based system, one would expect that this should always be "1"; for a polled
 *	system, higher values may indicate lower system stability or responsiveness.
 */
static tCwswClockTics maxct = 0;


// ============================================================================
// ----	Private Prototypes ----------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public Functions ------------------------------------------------------
// ============================================================================

tCwswClockTics
Cwsw_ClockSvc__TimerTic(void)
{
	return thistic;
}


tCwswClockTics
Cwsw_ClockSvc__Task(void)
{
	static tCwswClockTics lasttic = 0;
	static tCwswClockTics thisct;

	thistic = CLOCK();	// MinGW on Windows has a 1-ms resolution
	if((thistic) != lasttic)
	{
		if(lasttic)
		{
			thisct = (thistic - lasttic);
			if(thisct > maxct)	{ maxct = thisct; }
		}
		lasttic = thistic;
		if(pOsEvQX)
		{
			ev_os_heartbeat.evData = (uint32_t)thistic;
			(void)Cwsw_EvQX__PostEvent(pOsEvQX, ev_os_heartbeat);
		}
	}
	return thistic - clockoffset;
}


void
Cwsw_ClockSvc__Init(ptEvQ_QueueCtrlEx pEvQX, int16_t HeatbeatEvId)
{
	pOsEvQX = pEvQX;									// remember the address of the OS event queue.
	ev_os_heartbeat.evId = (tEvQ_EventID)HeatbeatEvId;	// and also remember the event we're to post.

	clockoffset = CLOCK();
}


tClkSvc_ErrorCode
Cwsw_ClockSvc__SetTimer(pCwswClockTics pTimer, tCwswClockTics duration)
{
	if(!pTimer)			{ return kerr_ClkSvc_BadParm; }
	if(duration < 1)	{ return kerr_ClkSvc_BadParm; }

	*pTimer = thistic + duration;	// raw clock reading, rather than ClockSvc(), 'cuzza
	return kErr_ClkSvc_NoError;
}


tCwswClockTics
Cwsw_ClockSvc__GetMaxMissedTics(void)
{
	return maxct;
}
