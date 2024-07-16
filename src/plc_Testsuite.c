/**
 **********************************************************************
 * \file plc_Testsuite.c
 *
 * Short description of the file.
 * Long description of the file.
 *
 * Copyright (c) 2024, Hoox.Software, Helmbrechts \n
 * All Rights Reserved.
 *
 * Created on: 29.01.2024
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
#include <plc_Testsuite.h>
#include <plc_TestDebug.h>

/*
 **********************************************************************
 static member variable definitions
 **********************************************************************
 */


/*
 **********************************************************************
 variable definitions
 **********************************************************************
 */
extern plc_pTestRegistry pTestRegistry;

/*
 **********************************************************************
 function definitions
 **********************************************************************
 */

//----------------------------------------------------------------------------/
plc_pTestSuite plc_createTestSuite(CHAR8* pName, CHAR8* pPackage)
{
    plc_pTestSuite pTestSuite = NULL;

    pTestSuite = (plc_pTestSuite) sys_MemAlloc(sizeof(plc_TestSuite));

    if (NULL != pTestSuite)
    {
        memset(pTestSuite, 0, sizeof(plc_TestSuite));
        pTestSuite->pName    = (CHAR8*) sys_MemAlloc(strlen(pName) + 1);
        pTestSuite->pPackage = (CHAR8*) sys_MemAlloc(strlen(pPackage) + 1);

        if (NULL != pTestSuite->pName && NULL != pTestSuite->pPackage)
        {
            bzero(pTestSuite->pName, strlen(pName) + 1);
            strcpy(pTestSuite->pName   , pName);

            bzero(pTestSuite->pPackage, strlen(pPackage) + 1);
            strcpy(pTestSuite->pPackage, pPackage);

            test_Info("plc_createTestSuite: created %s success!", pName);
        }
        else
        {
            test_Err("plc_createTestSuite: MemAlloc for Name failed!");
            sys_MemFree(pTestSuite);
            pTestSuite = NULL;
        }

    }
    else
    {
        test_Err("plc_createTestSuite: MemAlloc for TestSuite %s failed!", pName);
    }

    return pTestSuite;
}

//----------------------------------------------------------------------------/
SINT32 plc_addTestSuite(CHAR8* pName, CHAR8* pPackage)
{
    plc_pTestSuite pSuite = NULL;
    plc_pTestSuite pLastSuite = NULL;

    if (NULL == pName)
    {
        return 0;
    }

    pSuite = plc_createTestSuite(pName, pPackage);

    if (NULL != pSuite)
    {
        pLastSuite = plc_getLastSuite();

        if (pLastSuite == NULL)
        {
            pTestRegistry->pSuite = pSuite;
        }
        else
        {
            pLastSuite->pNext = pSuite;
        }
    }

    return (SINT32)pSuite;
}

//----------------------------------------------------------------------------/
plc_EErrorCode plc_cleanup_TestSuite(plc_pTestSuite pSuite)
{
    plc_pTest pCurTest = NULL;
    plc_pTest pNextTest = NULL;

    test_Info("plc_cleanup_TestSuite");

    pCurTest = pSuite->pTest;

    while (NULL != pCurTest)
    {
        pNextTest = pCurTest->pNext;

        plc_cleanup_Test(pCurTest);

        sys_MemFree(pCurTest);

        pCurTest = pNextTest;
    }

    if (NULL != pSuite->pName)
    {
        sys_MemFree(pSuite->pName);
    }
    if (NULL != pSuite->pPackage)
    {
        sys_MemFree(pSuite->pPackage);
    }

    pSuite->pName = NULL;
    pSuite->pTest = NULL;
    pSuite->ui32NumberOfTests = 0;

    return eSUCCESS;
}


//----------------------------------------------------------------------------/
plc_pTestSuite plc_getSuite(CHAR8* pName)
{
    plc_pTestSuite pSuite = NULL;
    plc_pTestRegistry pTestRegistry = NULL;

    if (pTestRegistry != NULL)
    {
        pSuite =  pTestRegistry->pSuite;

        while (pSuite != NULL)
        {
            if (strcmp(pSuite->pName, pName) == 0)
            {
                return pSuite;
            }

            pSuite = pSuite->pNext;
        }
    }

    return pSuite;
}



//----------------------------------------------------------------------------/
plc_pTestSuite plc_getFirstSuite()
{
    return pTestRegistry->pSuite;
}

//----------------------------------------------------------------------------/
plc_pTestSuite plc_getLastSuite()
{
    plc_pTestSuite pSuite = pTestRegistry->pSuite;

    if (pSuite == NULL)
    {
        return NULL;
    }

    while(pSuite->pNext != NULL)
    {
        pSuite = pSuite->pNext;
    }

    return pSuite;
}

//----------------------------------------------------------------------------/
plc_pTestSuite plc_getNextSuite(plc_pTestSuite pSuite)
{
    if (pSuite != NULL)
    {
        pSuite->bActive = FALSE;

        if (pSuite->pNext != NULL)
        {
            // check valid testlist
            if (pSuite->pNext->pTest == NULL)
            {
                return NULL;
            }
            pSuite->pNext->bActive = TRUE;
        }
        return pSuite->pNext;
    }

    return NULL;
}

//----------------------------------------------------------------------------/
plc_EErrorCode plc_run_Suite(CHAR8* pName)
{
    return eSUCCESS;
}



/*------------------------------------------------------------------------*/
plc_pTestSuite plc_get_current_suite(void)
{
    plc_pTestSuite pActiveSuite = NULL;

    return pActiveSuite;
}

//----------------------------------------------------------------------------/
plc_EErrorCode plc_addTest(plc_pTestSuite pSuite, CHAR8* pName, CHAR8* pClass,VOID* pTest)
{
    plc_Test* pTemp = NULL;
    plc_Test* pNextEntry = NULL;

    test_Info("plc_addTest: add %s", pName);

    if (pSuite == NULL)
    {
        test_Err("plc_addTest: no registry available!");
        return eNOSUITE;
    }

    pTemp = plc_create_Test(pName, pClass);

    if (pTemp == NULL)
    {
        test_Err("plc_addTest: Failed to create Test!");
        return eNOTEST;
    }

    pTemp->pData = pTest;

    pNextEntry = pSuite->pTest;

    if (pNextEntry != NULL)
    {
        while (pNextEntry->pNext != NULL)
        {
            pNextEntry = pNextEntry->pNext;
        }

        pTemp->pPrev = pNextEntry;
        pNextEntry->pNext = pTemp;
    }
    else
    {
        pSuite->pTest = pTemp;
    }

    pSuite->ui32NumberOfTests++;

    return eSUCCESS;


}


