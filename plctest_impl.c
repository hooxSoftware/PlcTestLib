/**
********************************************************************************
* This file was generated automatically and must be implemented.
********************************************************************************
* @file     plctestl_impl.c
* @author   Patrick Dressel
* @date     $LastChangeDate: ${DateAndTime} $
* @brief
*
********************************************************************************
* COPYRIGHT BY hoox.software (2024)
*******************************************************************************/

#define IMPLFILE
#include "src-gen/plctest_impl.h"
#include "src-gen/plctest.h"
#undef IMPLFILE

/*
 **********************************************************************
 system includes
 **********************************************************************
 */
#include <math.h>


/*
 **********************************************************************
 project includes
 **********************************************************************
 */
#include <plc_TestTypes.h>
#include <plc_TestRegistry.h>
#include <plc_assertions.h>
#include <plc_TestDebug.h>


/*
 **********************************************************************
 type definitions
 **********************************************************************
 */
typedef enum
{

  eIdle           = 0,   /**< Test not started */
  eExecute        = 1,   /**< Tests are executed */
  eExport         = 2,  /**< export result */
  eShowLog        = 3

} plc_ETestRun;

/*
 **********************************************************************
 variable definitions
 **********************************************************************
 */
UINT32 plctest_LibHandle;				/* library-handle */
SINT32 si32TaskHandle;
UINT32 ui32TaskDelay;
plc_EErrorCode eErrorCode;
CHAR* pPlcName;
CHAR strExportPath[255];
CHAR strExportFile[255];

plc_ETestRun eTestRun;

extern plc_pTestSuite    pActiveSuite;
extern plc_pTest         pActiveTest;

/*
 **********************************************************************
 function definitions
 **********************************************************************
 */
void PLCTEST_Main(void);



/**
 ********************************************************************************
 * @brief Function is called when a plc-project is installed.

 * @param[in]  pProject      plc-project
 * @param[in]  pInfo        information about library
 *
 * @param[out] pConfig      library configuration
 *
 * @retval     != Ok     : error, loading the project is interrupted
 * @retval     Ok        : initialization is ok
 *
*******************************************************************************/
MLOCAL SINT32 PLCTEST_PlcDllPrepareEx_Impl(PLCPROJ *pProject, PLC_LIBINFO *pInfo, PLC_EXTLIBCONFIG *pConfig)// @suppress("Unused static function")
{
    eErrorCode =  eNOREGISTRY;
    plc_SetDebugMode(0);
    return OK;
}

/**
 ********************************************************************************
 * @brief Function is called when a plc-project is initialized.

 * @param[in]  pProject      plc-project
 * @param[in]  pInfo        information about library
 *
 * @retval     N/A
*******************************************************************************/
MLOCAL VOID PLCTEST_PlcDllInit_Impl(PLCPROJ *pProject, PLC_LIBINFO *pInfo) // @suppress("Unused static function")
{
    plctest_LibHandle  = 0;
    ui32TaskDelay      = 0;
    si32TaskHandle     = 0;
    pPlcName           = libplc_GetProjectName(pProject);

    test_Info("%s Initialize Testregistry!", pPlcName);

    eErrorCode = plc_initialize_TestRegistry();

    if (eErrorCode != eSUCCESS)
    {
        test_Err("UNITTEST : Can not initalize registry (0x%x)", eErrorCode);
    }

    if (eErrorCode == eSUCCESS)
    {
        ui32TaskDelay = 20;

        si32TaskHandle =
        sys_TaskSpawn(libplc_GetProjectName(pProject),
                      "UnitTesttask",
                      255,
                      VX_FP_TASK,
                      10000,
                      (FUNCPTR)PLCTEST_Main);

        if (si32TaskHandle != 0)
        {
            test_Info("Task for Unittest spawned!");
        }


        return;
    }

	return;
}

/**
 ********************************************************************************
 * @brief Function is called when a plc-project is deinitialized.

 * @param[in]  pProject      plc-project
 * @param[in]  pInfo        information about library
 *
 * @retval     N/A
*******************************************************************************/
MLOCAL VOID PLCTEST_PlcDllDeinit_Impl(PLCPROJ *pProject, PLC_LIBINFO *pInfo)// @suppress("Unused static function")
{
    test_Info("Clean up Testregistry!");

    plc_cleanup_TestRegistry();

    if (si32TaskHandle != ERROR)
    {
        test_Info("Delete Test Task!");
        taskDelete(si32TaskHandle);
    }

	return;
}


/**
 ********************************************************************************
 * @brief Function

 * @param[in]  ret            plc-project
 * @param[in]  strName        information about library
 *
 * @retval     N/A
*******************************************************************************/
SINT32 PLCTEST_CREATETESTSUITE(CHAR *strName, CHAR *strPackage)
{
    SINT32 s32ElementId = 0;

    if (strName == NULL)
    {
        test_Err("PLCTEST_CREATETESTSUITE: Name is not valid!");
        return s32ElementId;
    }

    s32ElementId = plc_addTestSuite(strName, strPackage);

    if (0 == s32ElementId)
    {
        test_Err("PLCTEST_CREATETESTSUITE: Failed to create Testsuite %s", strName);
        return s32ElementId;
    }

    test_Info("PLCTEST_CREATETESTSUITE: Created Testsuite %s", strName);

    return s32ElementId;
}

/* ----------------------------------------------------------------- */
BOOL8 PLCTEST_ADDTEST(SINT32 TestSuiteID, CHAR *strName, CHAR *strClass, SPlcTest_Test *pTest)
{
    plc_pTestSuite l_pSuite  = (plc_pTestSuite)TestSuiteID;

    if (eSUCCESS == plc_addTest(l_pSuite, strName, strClass, pTest))
    {
        test_Info("PLCTEST_ADDTEST: Added Test %s to %s",
                strName, l_pSuite->pName);

        return TRUE;
    }

    return FALSE;
}

/* ----------------------------------------------------------------- */
BOOL8 PLCTEST_START(SINT32 dummy)
{
    if (eTestRun == eExecute)
    {
        test_Err("Test already executing, wait for finish");
        return FALSE;
    }

    if (pActiveSuite == NULL)
    {
        pActiveSuite = plc_getFirstSuite();
        if (pActiveSuite != NULL)
        {
            test_Info("PlcTest: Start Suite %s ", pActiveSuite->pName);
            pActiveSuite->bActive = TRUE;
        }
        pActiveTest  = plc_getFirstTest(pActiveSuite);
        if (pActiveTest != NULL)
        {
            plc_run_Test(pActiveTest);
        }
        eTestRun = eExecute;
    }

    return (pActiveSuite != NULL);
}

/* ----------------------------------------------------------------- */
BOOL8 PLCTEST_ISFINISHED(SINT32 dummy)
{
    return (pActiveSuite == NULL);
}

/* ----------------------------------------------------------------- */
BOOL8 PLCTEST_TESTFINISHED(SINT32 dummy)
{
    if (pActiveTest != NULL)
    {
        pActiveTest->pData->bFinished = TRUE;
        clock_gettime(CLOCK_MONOTONIC, &pActiveTest->sEnd);
    }
    return (pActiveTest != NULL);
}

/* ----------------------------------------------------------------- */
SINT32 PLCTEST_GETERROR(SINT32 dDummy)
{
    return 0;
}

/* ----------------------------------------------------------------- */
SINT32 PLCTEST_SETMESSAGE(CHAR *strMessage)
{
    if (pActiveTest != NULL)
    {
       if (pActiveTest->pData->eState > eFailed)
       {
           bzero(&pActiveTest->strMessage[0], sizeof(plc_TestMessage_t));

           snprintf(&pActiveTest->strMessage[0], sizeof(plc_TestMessage_t)-1,"%s", strMessage);
       }

    }
    return 0;
}

/* ----------------------------------------------------------------- */
void PLCTEST_Main(void)
{
    test_Info("PLCTEST_Main: Started");

    //--- Wait for cycle delay.
    do
    {
        sys_CycleEnd();
        taskDelay(ui32TaskDelay);
        sys_CycleStart();

        switch (eTestRun)
        {
        case eIdle:
            break;

        case eExecute:

            if (pActiveSuite != NULL && pActiveTest != NULL)
            {
                if (pActiveTest->pData->bFinished)
                {
                    pActiveTest = plc_getNextTest(pActiveTest);

                    plc_run_Test(pActiveTest);

                    if (pActiveTest == NULL)
                    {
                        pActiveSuite = plc_getNextSuite(pActiveSuite);

                        if (pActiveSuite != NULL)
                        {
                            test_Info("Start Testsuite %s", pActiveSuite->pName);
                        }

                        pActiveTest  = plc_getFirstTest(pActiveSuite);

                        if (pActiveTest != NULL)
                        {
                            plc_run_Test(pActiveTest);
                        }

                    }

                }
            }
            else
            {
                test_Info("PLCTEST: Testrun finished!");
                eTestRun = eIdle;
            }

            break;

        case eExport:

            test_Info("Export Started!");

            plc_export_TestRegistry(&strExportPath[0], &strExportFile[0]);

            test_Info("Export Finished!");
            eTestRun = eIdle;

            break;

        case eShowLog:


            log_Info("Result of last Test ");
            pActiveSuite = plc_getFirstSuite();
            pActiveTest  = plc_getFirstTest(pActiveSuite);

            while (pActiveTest != NULL)
            {
                log_Info("-----------------------------------------");
                switch (pActiveTest->pData->eState)
                {
                case eSkipped    :  log_Info("%s : SKIPPED", pActiveTest->pName); break;
                case ePassed     :  log_Info("%s : PASSED", pActiveTest->pName); break;
                case eFailed     :  log_Info("%s : FAILED", pActiveTest->pName); break;
                case eFailedFatal:  log_Info("%s : FAILED FATAL", pActiveTest->pName); break;
                }

                log_Info("Passed : %d", pActiveTest->sResult.u32Passed);
                log_Info("Failed : %d", pActiveTest->sResult.u32Failed);

                pActiveTest = plc_getNextTest(pActiveTest);

                if (pActiveTest == NULL)
                {
                    pActiveSuite = plc_getNextSuite(pActiveSuite);
                    pActiveTest  = plc_getFirstTest(pActiveSuite);
                }

                log_Info("-----------------------------------------");
            }

            eTestRun = eIdle;
            break;

        default:
            eTestRun = eIdle;
            break;
        }



    } while(1);

    test_Info("PLCTEST_Main: Removed");

}
/* ----------------------------------------------------------------- */
BOOL8 PLCTEST_ASSERT_TRUE(BOOL8 in)
{
    plc_Assert_TRUE(in == TRUE);

    return TRUE;
}
/* ----------------------------------------------------------------- */
BOOL8 PLCTEST_ASSERT_FALSE(BOOL8 in)
{
    plc_Assert_FALSE(in == FALSE);

    return TRUE;
}
/* ----------------------------------------------------------------- */
BOOL8 PLCTEST_ASSERT_EQUAL(SINT32 actual, SINT32 expected)
{
    plc_Assert_EQUAL(actual, expected);

    return TRUE;
}
/* ----------------------------------------------------------------- */
BOOL8 PLCTEST_ASSERT_NOT_EQUAL(SINT32 actual, SINT32 expected)
{
    plc_Assert_NOT_EQUAL(actual, expected);

    return TRUE;
}
/* ----------------------------------------------------------------- */
BOOL8 PLCTEST_ASSERT_EQUAL_REAL(REAL32 actual, REAL32 expected, REAL32 granularity)
{
    plc_Assert_TRUE((fabs(actual-expected) <= granularity));
    return TRUE;
}
/* ----------------------------------------------------------------- */
BOOL8 PLCTEST_ASSERT_NOT_EQUAL_REAL(REAL32 actual, REAL32 expected, REAL32 granularity)
{
    plc_Assert_FALSE( (fabs(actual-expected) <= granularity) );
    return TRUE;
}
/* ----------------------------------------------------------------- */
BOOL8 PLCTEST_ASSERT_EQUAL_TIME(UINT32 actual, UINT32 expected)
{
    plc_Assert_EQUAL(actual, expected);
    return TRUE;
}
/* ----------------------------------------------------------------- */
BOOL8 PLCTEST_ASSERT_NOT_EQUAL_TIME(UINT32 actual, UINT32 expected)
{
    plc_Assert_NOT_EQUAL(actual, expected);
    return TRUE;
}
/* ----------------------------------------------------------------- */
BOOL8 PLCTEST_ASSERT_EQUAL_STRING(CHAR *actual, CHAR *expected)
{
    plc_Assert_EQUAL(strcmp(actual, expected), 0);
    return TRUE;
};
/* ----------------------------------------------------------------- */
BOOL8 PLCTEST_ASSERT_NOT_EQUAL_STRING(CHAR *actual, CHAR *expected)
{
    plc_Assert_NOT_EQUAL(strcmp(actual, expected), 0);
    return TRUE;
};
/* ----------------------------------------------------------------- */
BOOL8 PLCTEST_ASSERT_EQUAL_NSTRING(CHAR *actual, CHAR *expected, UINT32 size)
{
    plc_Assert_EQUAL(strncmp(actual, expected, size), 0);
    return TRUE;
};
/* ----------------------------------------------------------------- */
BOOL8 PLCTEST_ASSERT_NOT_EQUAL_NSTRING(CHAR *actual, CHAR *expected, UINT32 size)
{
    plc_Assert_NOT_EQUAL(strncmp(actual, expected, size), 0);
    return TRUE;
};
/* ----------------------------------------------------------------- */
BOOL8 PLCTEST_EXPORTRESULT(CHAR *strPath, CHAR *strFile)
{
    memset(&strExportPath, 0, sizeof(strExportPath));
    memset(&strExportFile, 0, sizeof(strExportFile));

    strncpy(&strExportPath[0], &strPath[0], strlen(&strPath[0]));
    strncpy(&strExportFile[0], &strFile[0], strlen(&strFile[0]));

    if (eTestRun != eExecute)
    {
        eTestRun = eExport;
        return TRUE;
    }

    test_Err("Test is executing, no export possible!");

    return FALSE;
}
/* ----------------------------------------------------------------- */
BOOL8 PLCTEST_SHOWLOG(SINT32 dummy)
{
    eTestRun = eShowLog;
    return TRUE;
}
/* ----------------------------------------------------------------- */
BOOL8 PLCTEST_LOGGING(BOOL8 bActive)
{
    plc_SetDebugMode(0);

    if (bActive == TRUE)
    {
        plc_SetDebugMode(1);
    }

    return TRUE;
}
