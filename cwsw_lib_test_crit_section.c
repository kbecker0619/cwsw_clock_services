/** @file cwsw_lib_test_crit_section.c
 *
 *	Copyright (c) 2019 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Apr 22, 2019
 *	Author: KBECKE35
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include <limits.h>

// ----	Project Headers -------------------------
#include <CUnit/Basic.h>
#include "cwsw_eventsim.h"

// ----	Module Headers --------------------------
#include "cwsw_lib.h"
#include "cwsw_lib_test_op_states.h"


// ============================================================================
// ----	Constants -------------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Type Definitions ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Global Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Module-level Variables ------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Private Prototypes ----------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public Functions ------------------------------------------------------
// ============================================================================

/**	Initialize the CUnit Operating States suite for the CWSW Library component.
 *	For this edition of this UT suite, all we're looking for is to confirm that
 *	the library has not yet been initialized.
 *
 *	@return 0 for success.
 *	@return non-0 for failure.
 */
int
init_suite_lib_crit_section(void)
{
	/* at this time, there are no test environment things to set up, nor are
	 * there UUT environment things to set up. Simply do a nop.
	 */
	return CUE_SUCCESS;
}

/**	Perform final cleanup of the Operating States suite for the CWSW Library component.
 *	For this edition of this UT suite, there is no actual cleanup activity
 *	required, we are only confirming that the library indicates it's been
 *	initialized.
 *
 *	@return 0 for success.
 *	@return non-0 for failure.
 */
int
clean_suite_lib_crit_section(void)
{
	/* at this time, there are no UT environment nor UUT environment post-conditions that need to
	 * be affirmed, or activities that need to be done. Simply return success.
	 */
	return CUE_SUCCESS;
}


/**	Confirm presence of an API to support component tasks.
 *	@xreq{SR_LIB_0301}  API for entering critical sections.		(Primary)
 *	@xreq{SR_LIB_0300}  API for managing critical sections.		(Support)
 */
void
test_sr_lib_0301(void)
{
	/* if this compiles, we've satisfied the requirement (as of the current
	 * revision of the requirements document)
	 */
	int protct = Cwsw_Critical_Protect(0); UNUSED(protct);
	CU_PASS("Tasking API Exists");
}


/**	Confirm presence of an API to support component tasks.
 *	This test confirms the "leave" API that is complementary to the "enter" API
 *	tested as part of sr-lib-0301.
 *	@xreq{SR_LIB_0302}  API for leaving critical section.		(Primary)
 *	@xreq{SR_LIB_0300}  API for managing critical sections.		(Support)
 */
void
test_sr_lib_0302(void)
{
	/* if this compiles, we've satisfied the requirement (as of the current
	 * revision of the requirements document)
	 */
	int protct = Cwsw_Critical_Release(0); UNUSED(protct);
	CU_PASS("Tasking API Exists");
}


/**	Confirm behavior of critical-section nesting counter incrementation:
 *	begin @ floor of counter range.
 *
 *	@xreq{SR_LIB_0303}	Increment nesting counter upon entry.	(Primary)
 *	@xreq{SR_LIB_0305}	Data range of nesting counter.			(Primary, Shared)
 */
void
test_sr_lib_0303_floor(void)
{
	extern cwsw_lib_cs_protection_count;
	int localct = INT_MAX;	/* just want some value non-zero, unlikely to be seen */

	cwsw_lib_cs_protection_count = 0;	/* sr-lib-0305: data range floor is 0 */
	localct = Cwsw_Critical_Protect(0);
	CU_ASSERT_EQUAL(cwsw_lib_cs_protection_count, 1);
	CU_ASSERT_EQUAL(localct, 1);
}


/**	Confirm behavior of critical-section nesting counter incrementation:
 *	test at upper end of range.
 *	Since the data range is specified to be one-sided, there is no concern
 *	about "crossover" such as passing from negative to positive values.
 *
 *	@xreq{SR_LIB_0303}	Increment nesting counter upon entry.	(Primary)
 *	@xreq{SR_LIB_0305}	Data range of nesting counter.			(Primary, Shared)
 */
void
test_sr_lib_0303_ceiling(void)
{
	extern cwsw_lib_cs_protection_count;
	int localct = 1234;	/* just want some value non-zero, unlikely to be seen */

	cwsw_lib_cs_protection_count = INT_MAX - 1;	/* sr-lib-0305: data range ceiling is INT_MAX, after incrementation */
	localct = Cwsw_Critical_Protect(0);
	CU_ASSERT_EQUAL(cwsw_lib_cs_protection_count, INT_MAX);
	CU_ASSERT_EQUAL(localct, INT_MAX);
}


/**	Confirm behavior of critical-range nesting counter decrementation: begin @
 *	max value of counter range.
 *
 *	@xreq{SR_LIB_0304}	Decrement nesting counter upon entry 	(Primary)
 *	@xreq{SR_LIB_0305}	Data range of nesting counter.			(Primary, Shared)
 */
void
test_sr_lib_0304_ceiling(void)
{
	extern cwsw_lib_cs_protection_count;
	int localct = 1234;	/* just want some value non-zero, unlikely to be seen */

	cwsw_lib_cs_protection_count = INT_MAX;	/* sr-lib-0305: data range ceiling is INT_MAX */
	localct = Cwsw_Critical_Release(0);
	CU_ASSERT_EQUAL(cwsw_lib_cs_protection_count, INT_MAX - 1);
	CU_ASSERT_EQUAL(localct, INT_MAX - 1);
}
