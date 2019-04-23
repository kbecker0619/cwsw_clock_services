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
#include "cwsw_lib_test_op_states.h"
#include "cwsw_lib_test_task_support.h"


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


int
main(void)
{
	CU_pSuite pSuite = NULL;
	bool cu_setup_ok = false;

	/* Initialize the CUnit test registry for Operating States test suite */
	if(CUE_SUCCESS == CU_initialize_registry())
	{
		cu_setup_ok = true;
	}

	/* CWSW Library Operating States suite */
	do
	{
		CU_pTest tests[5];

		/* Add a suite to the registry.
		 * within the CWSW suite, we are using, generally, one suite per section of the requirements
		 * document, with a separate compilation unit for each suite. within the suite, distinct unit
		 * test files are used per requirement, or else, a distinct design element.
		 */
		if(cu_setup_ok)
		{
			pSuite = CU_add_suite(
					"CWSW Library Component, Operating States",
					init_suite_lib_op_states,
					clean_suite_lib_op_states);
			if(NULL == pSuite)
			{
				cu_setup_ok = false;
				break;
			}
		}

		/* add tests to Operating States test suite */
		tests[0] = CU_add_test(pSuite, "SR_LIB_0000: Initialization API", 					test_sr_lib_0000);
		tests[1] = CU_add_test(pSuite, "SR_LIB_0001: Initialization Status API", 			test_sr_lib_0001);
		tests[2] = CU_add_test(pSuite, "SR_LIB_0002: Initialization API Responsibilities",	test_sr_lib_0002);
		tests[3] = CU_add_test(pSuite, "SR_LIB_0003: Indication when uninitialized",		test_sr_lib_0003);
		tests[4] = CU_add_test(pSuite, "SR_LIB_0004: Behavior when uninitialized",			test_sr_lib_0005);
		if(!tests[0] || !tests[1] || !tests[2] || !tests[3] || !tests[4])
		{
			cu_setup_ok = false;
			break;
		}

		/* sr-lib-0004 & sr-lib-0005 are not yet ready for testing */
		(void)CU_set_test_active(tests[3], CU_FALSE);
		(void)CU_set_test_active(tests[4], CU_FALSE);
	} while(0);

	/* CWSW Library Tasking Support test suite */
	do
	{
		CU_pTest tests[1];
		if(cu_setup_ok)
		{
			pSuite = CU_add_suite(
					"CWSW Library Component, Tasking Support",
					init_suite_lib_task_support,
					clean_suite_lib_task_support);
			if(NULL == pSuite)
			{
				cu_setup_ok = false;
				break;
			}

			/* add tests to Operating States test suite */
			tests[0] = CU_add_test(pSuite, "SR_LIB_0200: Tasking Support API", 				test_sr_lib_0200);
			if(!tests[0])
			{
				cu_setup_ok = false;
				break;
			}

			/* sr-lib-0201 is not yet ready for testing */
			(void)CU_set_test_active(tests[0], CU_FALSE);
		}
	} while(0);

	/* Run all tests using the CUnit Basic interface */
	if(cu_setup_ok)
	{
		CU_basic_set_mode(CU_BRM_VERBOSE);
		CU_basic_run_tests();
	}

	CU_cleanup_registry();
	return CU_get_error();
}
