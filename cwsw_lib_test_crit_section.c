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

/** Initialize the CUnit Operating States suite for the CWSW Library component.
 *  For this edition of this UT suite, all we're looking for is to confirm that
 *  the library has not yet been initialized.
 *
 *	@return 0 for success.
 *  @return non-0 for failure.
 */
int
init_suite_lib_crit_section(void)
{
    /* at this time, there are no test environment things to set up, nor are
     * there UUT environment things to set up. Simply do a nop.
     */
    return CUE_SUCCESS;
}

/** Perform final cleanup of the Operating States suite for the CWSW Library component.
 *  For this edition of this UT suite, there is no actual cleanup activity
 *  required, we are only confirming that the library indicates it's been
 *  initialized.
 *
 *	@return 0 for success.
 *  @return non-0 for failure.
 */
int
clean_suite_lib_crit_section(void)
{
    /* at this time, there are no UT environment nor UUT environment post-conditions that need to
     * be affirmed, or activities that need to be done. Simply return success.
     */
    return CUE_SUCCESS;
}


/** Confirm presence of an API to support component tasks.
 *  @xreq{SR_LIB_0301}
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
