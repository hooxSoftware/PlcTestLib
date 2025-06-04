/**
 **********************************************************************
 * \file plc_TestExport.c
 *
 * Short description of the file.
 * Long description of the file.
 *
 * Copyright (c) 2024, Hoox.Software, Helmbrechts \n
 * All Rights Reserved.
 *
 * Created on: 15.03.2024
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
#include <stdio.h>
#include <string.h>
#include <ioLib.h>

/*
 **********************************************************************
 project includes
 **********************************************************************
*/
#include <plc_TestExport.h>
#include <plc_TestDebug.h>

/*
 **********************************************************************
 static member variable definitions
 **********************************************************************
*/
MLOCAL FILE* PLCTTEST_FileHandle  = NULL;     /*  Filehandle           */
const char* XML_START = "<?xml version=\"1.0\" ?>";
const char* XML_TESTSUITES_START = "<testsuites>";
const char* XML_TESTSUITES_END   = "</testsuites>";
const char* XML_TESTSUITE        = "<testsuite name=\"%s\" tests=\"%d\" disabled=\"%d\" errors=\"%d\" failures=\"%d\" package=\"%s\">";
const char* XML_TESTSUITE_END    = "</testsuite>";
const char* XML_TEST_START       = "<testcase name=\"%s\" assertions=\"%d\" classname=\"%s\" time=\"%d\">";
const char* XML_TEST_END         = "</testcase>";
const char* XML_TEST_PASSED      = "</passed>";
const char* XML_TEST_FAILED      = "</failed message=\"%s\">";
const char* XML_TEST_SKIPPED     = "</skipped>";

/*
 **********************************************************************
 function definitions
 **********************************************************************
*/


/* ----------------------------------------------------------------- */
VOID plc_CreateJunit(const CHAR* strPath, const CHAR* strFile, plc_TestRegistry* pData)
{
    plc_TestBuffer_t strBuffer;

    if (strPath == NULL)
    {
       test_Err("Export Failed, missing Path!");
       return;
    }
    if (strFile == NULL)
    {
       test_Err("Export Failed, missing Filename!");
       return;
    }
    if (pData == NULL)
    {
       test_Err("Export Failed, missing Data!");
       return;
    }

    plc_CreateFolder(strPath);

    bzero(strBuffer, sizeof(strBuffer));

    sprintf(&strBuffer[0], "%s/%s", strPath, strFile);

    log_Info("Export %s", strBuffer);

    PLCTTEST_FileHandle = fopen(strBuffer, "w");

    if (PLCTTEST_FileHandle > 0)
    {
        plc_CreateData(pData);

        fflush(PLCTTEST_FileHandle);

        fclose(PLCTTEST_FileHandle);
    }
    else
    {
        test_Err("Failed to open File for export!");
    }


}

/* ----------------------------------------------------------------- */
VOID plc_CreateData(plc_TestRegistry* pData)
{
    plc_TestSuite *pSuite = NULL;
    plc_Test      *pTest = NULL;
    plc_TestBuffer_t strBuffer;
    UINT32 u32Duration;

    if (pData == NULL)
    {
       test_Err("Export Failed, missing Data!");
       return;
    }

    fprintf(PLCTTEST_FileHandle, "%s\n", XML_START);
    fprintf(PLCTTEST_FileHandle, "%s\n", XML_TESTSUITES_START);

    pSuite = pData->pSuite;

    while(pSuite != NULL)
    {
        bzero(&strBuffer[0], sizeof(plc_TestBuffer_t));
        sprintf(&strBuffer[0], XML_TESTSUITE,
                pSuite->pName,
                pSuite->ui32NumberOfTests,
                0,
                0,
                pSuite->sResult.u32Failed,
                pSuite->pPackage);

        fprintf(PLCTTEST_FileHandle, "%s\n", strBuffer);

        pTest = pSuite->pTest;

        while (pTest != NULL)
        {
            u32Duration = plc_GetDuration(&pTest->sStart, &pTest->sEnd);

            bzero(&strBuffer[0], sizeof(plc_TestBuffer_t));
            sprintf(&strBuffer[0], XML_TEST_START,
                    pTest->pName,
                    pTest->sResult.u32Failed + pTest->sResult.u32Passed,
                    pTest->pClass,
                    u32Duration);

            fprintf(PLCTTEST_FileHandle, "%s\n", strBuffer);

            switch(pTest->pData->eState)
            {
            case ePassed        : fprintf(PLCTTEST_FileHandle, "%s\n", XML_TEST_PASSED); break;
            case eSkipped       : fprintf(PLCTTEST_FileHandle, "%s\n", XML_TEST_SKIPPED); break;
            case eFailed        :
            case eFailedFatal   :
                                  bzero(&strBuffer[0], sizeof(plc_TestBuffer_t));
                                  sprintf(&strBuffer[0], XML_TEST_FAILED, &pTest->strMessage[0]);
                                  fprintf(PLCTTEST_FileHandle, "%s\n", &strBuffer[0]);
                                  break;
            }

            fprintf(PLCTTEST_FileHandle, "%s\n", XML_TEST_END);

            pTest = pTest->pNext;
        }

        fprintf(PLCTTEST_FileHandle, "%s\n", XML_TESTSUITE_END);

        pSuite = pSuite->pNext;
    }

    fprintf(PLCTTEST_FileHandle, "%s\n", XML_TESTSUITES_END);

}

/* ----------------------------------------------------------------- */
UINT32 plc_GetDuration(struct timespec *sStart, struct timespec *sEnd)
{
    UINT32 u32Return = 0;
    UINT32 u32Seconds = 0;
    UINT32 u32nSeconds = 0;

    if (sStart != NULL && sEnd != NULL)
    {
        u32Seconds  = (sEnd->tv_sec  - sStart->tv_sec);
        u32nSeconds = (sEnd->tv_nsec - sStart->tv_nsec) / 1000000;

        u32Return = (u32Seconds * 1000) + u32nSeconds;
    }

    return u32Return;
}

/* ----------------------------------------------------------------- */
BOOL8 plc_CreateFolder(const CHAR* strPath)
{
    int fd;
    int state;
    CHAR strBuffer[255];

    bzero(&strBuffer[0], 255);
    strcpy(&strBuffer[0], strPath);

    if (plc_StrEndsWith(&strBuffer[0], '/') == FALSE)
    {
        strBuffer[strlen(&strBuffer[0])] = '/';
    }

    test_Info("Create folder %s", &strBuffer[0]);

    fd = open("/cfc0", 0, O_RDONLY);

    state = ioctl(fd, FIOMKDIR, (int)&strBuffer[0]);

    if (state == OK)
    {
        return TRUE;
    }

    test_Err("Create folder %s Failed", strPath);

    return FALSE;
}

/* ----------------------------------------------------------------- */
BOOL8 plc_StrEndsWith(const CHAR* strSource, const CHAR strSign)
{
    int len = strlen(strSource);

    if (len > 0 && strSource[len-1] == strSign)
    {
        return TRUE;
    }
    return FALSE;


}

// EOF
