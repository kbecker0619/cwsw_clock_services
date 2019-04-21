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

    /* Initialize the CUnit test registry for Operating States test suite */
    if(CUE_SUCCESS != CU_initialize_registry())
    {
        return CU_get_error();
    }

    /* Note that all of these initialization and execution steps are designed to bail early upon
     * any problem.
     */

    do {	/* CUnit initialization */
        /* Add a suite to the registry.
         * within the CWSW suite, we are using, generally, one suite per section of the requirements
         * document, with a separate compilation unit for each suite. within the suite, distinct unit
         * test files are used per requirement, or else, a distinct design element.
         */
        pSuite = CU_add_suite(
                "CWSW Library Component, Operating States",
                init_suite_lib_op_states,
                clean_suite_lib_op_states);
        if(NULL == pSuite)
        {
            CU_cleanup_registry();
            return CU_get_error();
        }
    } while(0);

    do {	/* add tests to Operating States test suite */
        if(!CU_add_test(pSuite, "Initialization Status API", test_sr_lib_0001))
        {
            CU_cleanup_registry();
            return CU_get_error();
        }

        if( (NULL == CU_add_test(pSuite, "ConfirmUninit", test_sr_lib_0002))
            /* || (NULL == CU_add_test(pSuite, "Critical Section", test_critical_section_en_dis_able)) */
        )
        {
            CU_cleanup_registry();
            return CU_get_error();
        }
    } while(0);


	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
