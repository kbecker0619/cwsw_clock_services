/** @file cwsw_lib_test_op_states.c
 *	@brief	One-sentence short description of file.
 *
 *	Description:
 *
 *	Copyright (c) 2019 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Apr 21, 2019
 *	Author: KBECKE35
 *
 *	Current:
 *	$Revision: $
 *	$Date: $
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

/** Initialize the CUnit suite for the CWSW Library component.
 *  For this edition of this UT suite, all we're looking for is to confirm that
 *  the library has not yet been initialized.
 * 
 *	@return 0 for success.
 *  @return non-0 for failure.
 */
int
init_suite_lib_op_states(void)
{
    return Get(Cwsw_Lib, Initialized);
}

/** Perform final cleanup of the CUnit suite for the CWSW Library component.
 *  For this edition of this UT suite, there is no actual cleanup activity 
 *  required, we are only confirming that the library indicates it's been 
 *  initialized.
 * 
 *	@return 0 for success.
 *  @return non-0 for failure.
 */
int
clean_suite_lib_op_states(void)
{
    return !Get(Cwsw_Lib, Initialized);
}


void
test_init_lib(void)
{
    CU_ASSERT(!Init(Cwsw_Lib));
}

