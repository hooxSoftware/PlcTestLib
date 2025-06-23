/**
 **********************************************************************
 * \file plc_UnitTest.c
 *
 * Short description of the file.
 * Long description of the file.
 *
 * Copyright (c) 2024, hoox.software, Helmbrechts \n
 * All Rights Reserved.
 *
 * Created on: 31.10.2016
 *     Author: patrickdressel
 *
 * Template: cpp_class_definition.hpp (Version 1)
 **********************************************************************
 */



/*
 **********************************************************************
 system includes
 **********************************************************************
 */
#include <msys_e.h>
#include <stdio.h>
#include <string.h>
#include <log_e.h>
/*
 **********************************************************************
 project includes
 **********************************************************************
 */
#include <plc_TestRegistry.h>
#include <plc_TestDebug.h>
#include <plc_TestExport.h>

/*
 **********************************************************************
 static member variable definitions
 **********************************************************************
 */
plc_pTestRegistry pTestRegistry;
plc_pTestSuite    pActiveSuite;
plc_pTest         pActiveTest;


/*
 **********************************************************************
 function definitions
 **********************************************************************
 */

//----------------------------------------------------------------------------/
plc_EErrorCode plc_initialize_TestRegistry()
{

    test_Info("plc_initialize_TestRegistry");

    pTestRegistry = NULL;
    pActiveTest  = NULL;
    pActiveSuite = NULL;

    if (pTestRegistry != NULL)
    {
        plc_cleanup_TestRegistry();
    }

    pTestRegistry = plc_create_TestRegistry();

    if (pTestRegistry == NULL)
    {
        return eNOMEMORY;
    }

    return eSUCCESS;
}

//----------------------------------------------------------------------------/
plc_pTestRegistry plc_create_TestRegistry(void)
{
    plc_pTestRegistry pRegistry = NULL;

    test_Info("plc_create_TestRegistry");

    pRegistry = (plc_pTestRegistry) sys_MemAlloc(sizeof(plc_TestRegistry));

    if (NULL != pRegistry)
    {
        pRegistry->pSuite             = NULL;
        pRegistry->ui32NumberOfSuites = 0;
        pRegistry->ui32NumberOfTests  = 0;
    }

    return pRegistry;
}

//----------------------------------------------------------------------------/
plc_EErrorCode plc_cleanup_TestRegistry()
{
    plc_pTestSuite pCurSuite = NULL;
    plc_pTestSuite pNextSuite = NULL;

    test_Info("plc_cleanup_TestRegistry");

    pCurSuite = pTestRegistry->pSuite;

    while (NULL != pCurSuite)
    {
        pNextSuite = pCurSuite->pNext;

        plc_cleanup_TestSuite(pCurSuite);

        sys_MemFree(pCurSuite);

        pCurSuite = pNextSuite;
    }

    pTestRegistry->pSuite = NULL;
    pTestRegistry->ui32NumberOfSuites = 0;
    pTestRegistry->ui32NumberOfTests = 0;

    sys_MemFree(pTestRegistry);

    return eSUCCESS;
}



//----------------------------------------------------------------------------/
plc_EErrorCode plc_run_all()
{
    return eSUCCESS;
}


/*------------------------------------------------------------------------*/
BOOL8 plc_is_test_running(void)
{
    return (pActiveTest != NULL);
}

//----------------------------------------------------------------------------/
void plc_AssertImpl(BOOL8 bInput, BOOL8 bFatal)
{
    //log_Info("AssertImpl: %d, %d\n", b8Input, b8Fatal);

    if (pActiveTest == NULL)
    {
        test_Err("Assertion: no Test selected, ActiveTest == NULL!");
        return;
    }

    if (bInput == TRUE)
    {
        pActiveTest->sResult.u32Passed++;
        pActiveSuite->sResult.u32Passed++;
        if (pActiveTest->pData->eState > eFailed)
        {
            pActiveTest->pData->eState = ePassed;
        }
    }
    else
    {
        pActiveTest->sResult.u32Failed++;
        if (pActiveTest->pData->eState > eFailed)
        {
            pActiveSuite->sResult.u32Failed++;
        }

        pActiveTest->pData->eState = eFailed;

        if (bFatal)
        {
            test_Err("Assertion: Test %s failed fatal", pActiveTest->pName);
            pActiveTest->pData->eState = eFailedFatal;
            pActiveTest->pData->bFinished = TRUE;
            pActiveTest->pData->bStart = FALSE;
            clock_gettime(CLOCK_MONOTONIC, &pActiveTest->sEnd);
        }
        else
        {
            test_Err("Assertion: Test %s failed", pActiveTest->pName);
        }

        test_Err("Assertion: Message %s", pActiveTest->strActMessage);
    }
}

//----------------------------------------------------------------------------/
plc_pTest plc_getTest(CHAR8* pName)
{
    plc_pTest pTest         = NULL;
    plc_pTestSuite pSuite   = NULL;

    if (pTestRegistry != NULL)
    {
        pSuite =  pTestRegistry->pSuite;

        while(pSuite != NULL)
        {
            pTest = pSuite->pTest;

            while (pTest != NULL)
            {
                if (strcmp(pTest->pName, pName) == 0)
                {
                    return pTest;
                }

                pTest = pTest->pNext;
            }

            pSuite = pSuite->pNext;
        }
    }


    return pTest;
}


/*------------------------------------------------------------------------*/
plc_pTest plc_get_current_test(void)
{
    return pActiveTest;
}

/*------------------------------------------------------------------------*/
void plc_export_TestRegistry(CHAR *strPath, CHAR *strFile)
{
    plc_CreateJunit(strPath, strFile, pTestRegistry);
}


// EOF
