/** @file cwsw_lib_test.c
 *	@brief	Primary Unit Test file for the CWSW Lib component.
 *
 *	Description:
 *
 *	Copyright (c) 2019 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Nov 11, 2018
 *	Author: kbecker
 *
 *	Current:
 *	$Revision: $
 *	$Date: $
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include <stdio.h>
#include <stdlib.h>

// ----	Project Headers -------------------------
#include <CUnit/Basic.h>
#include "cwsw_eventsim.h"

// ----	Module Headers --------------------------
#include "cwsw_lib.h"


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

static int
init_suite(void)
{
    return Get(Cwsw_Lib, Initialized);
}

static int
clean_suite(void)
{
    return !Get(Cwsw_Lib, Initialized);
}

static void
init_lib()
{
    CU_ASSERT(!Init(Cwsw_Lib));
}

void test2()
{
    CU_ASSERT(2 * 2 == 4);
}

int
main(void)
{
	CU_pSuite pSuite = NULL;

	/* Initialize the CUnit test registry */
	if(CUE_SUCCESS != CU_initialize_registry())
    {
        return CU_get_error();
    }

	/* Add a suite to the registry */
	pSuite = CU_add_suite("cwsw_lib_tests", init_suite, clean_suite);
	if(NULL == pSuite)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Add the tests to the suite */
	if( (NULL == CU_add_test(pSuite, "ConfirmUninit", init_lib))    ||
        (NULL == CU_add_test(pSuite, "test2", test2)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
