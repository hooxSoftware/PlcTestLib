/**
 **********************************************************************
 * \file plc_Test.c
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
#include <plc_Test.h>
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


/*
 **********************************************************************
 function definitions
 **********************************************************************
 */



//----------------------------------------------------------------------------/
plc_pTest plc_create_Test(CHAR8* pName, CHAR8* pClass)
{
    plc_pTest pTest = (plc_pTest) sys_MemAlloc(sizeof(plc_Test));

    if (NULL != pTest)
    {
        memset(pTest, 0, sizeof(plc_Test));

        pTest->pName  = (CHAR8*) sys_MemAlloc(strlen(pName) + 1);
        pTest->pClass = (CHAR8*) sys_MemAlloc(strlen(pClass) + 1);

        if (NULL != pTest->pName && NULL != pTest->pClass)
        {
            bzero(pTest->pName, strlen(pName) + 1);
            strcpy(pTest->pName, pName);

            bzero(pTest->pClass, strlen(pClass) + 1);
            strcpy(pTest->pClass, pClass);
        }
        else
        {
            sys_MemFree(pTest);
            pTest = NULL;
        }
    }

    return pTest;
}

//----------------------------------------------------------------------------/
plc_EErrorCode plc_cleanup_Test(plc_pTest pTest)
{
    test_Info("plc_cleanup_Test");

    if (NULL != pTest->pName)
    {
        sys_MemFree(pTest->pName);
    }
    if (NULL != pTest->pClass)
    {
        sys_MemFree(pTest->pClass);
    }

    pTest->pName = NULL;

    return eSUCCESS;
}

//----------------------------------------------------------------------------/
plc_pTest plc_getFirstTest(plc_TestSuite* pSuite)
{

    if (pSuite != NULL)
    {
        return pSuite->pTest;
    }

    return NULL;
}

//----------------------------------------------------------------------------/
plc_pTest plc_getNextTest(plc_pTest pTest)
{

    if (pTest != NULL)
    {
        if (pTest->pData != NULL)
        {
            pTest->pData->bStart    = FALSE;
        }

        return pTest->pNext;
    }

    return NULL;
}

//----------------------------------------------------------------------------/
plc_EErrorCode plc_prepare_Test(plc_pTest pTest)
{
    if (pTest != NULL)
    {
        test_Info("PLCTEST: Prepare %s", pTest->pName);

        pTest->pData->bStart    = FALSE;
        pTest->pData->bFinished = FALSE;
        pTest->sResult.u32Failed = 0;
        pTest->sResult.u32Passed = 0;
        pTest->sEnd.tv_nsec   = 0;
        pTest->sEnd.tv_sec    = 0;
        pTest->sStart.tv_nsec = 0;
        pTest->sStart.tv_sec  = 0;
        bzero(&pTest->strMessage[0], sizeof(plc_TestMessage_t));

        if (pTest->pData != NULL)
        {
            pTest->pData->eState  = eSkipped;
        }
        if (pTest->pNext != NULL)
        {
            pTest->pNext->pData->bFinished = FALSE;
        }
    }
    return eSUCCESS;
}

//----------------------------------------------------------------------------/
plc_EErrorCode plc_run_Test(plc_pTest pTest)
{
    if (pTest != NULL)
    {
        if (pTest->pData != NULL)
        {
            if (pTest->pData->bStart == FALSE)
            {
                test_Info("PLCTEST: Start %s", pTest->pName);
                clock_gettime(CLOCK_MONOTONIC, &pTest->sStart);
            }
            pTest->pData->bStart    = TRUE;

        }
    }
    return eSUCCESS;
}



