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
#include <limits.h>         // INT_MAX, INT_MIN

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
test_init_lib()
{
    CU_ASSERT(!Init(Cwsw_Lib));
}

static void
test_critical_section_en_dis_able()
{
    extern int protection_count;
    CU_ASSERT_EQUAL(protection_count, 0);
    CU_ASSERT_EQUAL(Cwsw_Critical_Release(0), -1);
    CU_ASSERT_EQUAL(protection_count, -1);
    CU_ASSERT_EQUAL(Cwsw_Critical_Protect(0), 1);
    CU_ASSERT_EQUAL(protection_count, 1);
    CU_ASSERT_EQUAL(Cwsw_Critical_Release(0), 0);
    CU_ASSERT_EQUAL(protection_count, 0);
    protection_count = INT_MAX;
    CU_ASSERT_EQUAL(Cwsw_Critical_Protect(0), INT_MIN);
    CU_ASSERT_EQUAL(protection_count, INT_MIN);
}

int main(void)
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
	if( (NULL == CU_add_test(pSuite, "ConfirmUninit", test_init_lib))    ||
        (NULL == CU_add_test(pSuite, "Critical Section", test_critical_section_en_dis_able)))
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
