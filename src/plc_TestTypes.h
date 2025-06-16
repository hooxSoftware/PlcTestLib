/**
 **********************************************************************
 * \file plc_TestTypes.h
 *
 * Short description of the file.
 * Long description of the file.
 *
 * Copyright (c) 2024, Hoox.Software, Helmbrechts \n
 * All Rights Reserved.
 *
 * Created on: 08.03.2024
 *     Author: patrickdressel
 *
 * Template: cpp_class_definition.hpp (Version 1)
 **********************************************************************
 */


#ifndef SRC_PLC_TESTTYPES_H_
#define SRC_PLC_TESTTYPES_H_
#include <time.h>

typedef enum
{
  /* basic errors */
  eSUCCESS           = 0,  /**< No error condition. */
  eNOMEMORY          = 1,  /**< Memory allocation failed. */

  /* Test Registry Level Errors */
  eNOREGISTRY        = 10,  /**< Test registry not initialized. */
  eREGISTRY_EXISTS   = 11,  /**< Attempt to CU_set_registry() without CU_cleanup_registry(). */

  /* Test Suite Level Errors */
  eNOSUITE           = 20,  /**< A required CU_pSuite pointer was NULL. */
  eNO_SUITENAME      = 21,  /**< Required CU_Suite name not provided. */
  eSINIT_FAILED      = 22,  /**< Suite initialization failed. */
  eSCLEAN_FAILED     = 23,  /**< Suite cleanup failed. */
  eDUP_SUITE         = 24,  /**< Duplicate suite name not allowed. */
  eSUITE_INACTIVE    = 25,  /**< Test run initiated for an inactive suite. */

  /* Test Case Level Errors */
  eNOTEST            = 30,  /**< A required CU_pTest or CU_TestFunc pointer was NULL. */
  eNO_TESTNAME       = 31,  /**< Required CU_Test name not provided. */
  eDUP_TEST          = 32,  /**< Duplicate test case name not allowed. */
  eTEST_NOT_IN_SUITE = 33,  /**< Test not registered in specified suite. */
  eTEST_INACTIVE     = 34,  /**< Test run initiated for an inactive test. */

  /* File handling errors */
  eFOPEN_FAILED      = 40,  /**< An error occurred opening a file. */
  eFCLOSE_FAILED     = 41,  /**< An error occurred closing a file. */
  eBAD_FILENAME      = 42,  /**< A bad filename was requested (NULL, empty, nonexistent, etc.). */
  eWRITE_ERROR       = 43   /**< An error occurred during a write to a file. */
} plc_EErrorCode;


typedef enum
{

  eSkipped           = 0,   /**< Test not started */
  ePassed            = 1,   /**< Test ok */
  eFailed            = -1,  /**< Test failed */
  eFailedFatal       = -2   /**< Test failed */

} plc_ETestState;

/***********************************
 * Test Registry
 * Structure with List of Testsuites
 */
typedef struct plc_TestResult
{
  UINT32 u32Failed;
  UINT32 u32Passed;

} plc_TestResult;


/***********************************
 * Interface to M-PLC Library
 */
typedef struct __attribute__ ((packed))
{
     BOOL8 bStart;
     BOOL8 bFinished;
     plc_ETestState eState;

} plc_TestData;


typedef CHAR plc_TestMessage_t[255];

/***********************************
 * Unit Test
 * Structure of one single test
 */
typedef struct plc_Test
{
    CHAR8* pName;
    CHAR8* pClass;
    plc_TestMessage_t strMessage; // message on failed
    plc_TestMessage_t strActMessage; // actual message of test
    plc_TestResult sResult;
    plc_TestData* pData;
    struct plc_Test* pPrev;
    struct plc_Test* pNext;
    struct timespec sStart;
    struct timespec sEnd;

} plc_Test;

typedef plc_Test* plc_pTest;

/***********************************
 * Test Suite
 * Structure with list of Tests
 */
typedef struct plc_TestSuite
{
    CHAR8* pName;
    CHAR8* pPackage;
    BOOL8  bActive;
    plc_TestResult sResult;

    struct plc_Test* pTest;
    struct plc_TestSuite* pPrev;
    struct plc_TestSuite* pNext;

    UINT32 ui32NumberOfTests;

} plc_TestSuite;

typedef plc_TestSuite* plc_pTestSuite;


/***********************************
 * Test Registry
 * Structure with List of Testsuites
 */
typedef struct plc_TestRegistry
{
  struct plc_TestSuite* pSuite;

  UINT32 ui32NumberOfSuites;
  UINT32 ui32NumberOfTests;

} plc_TestRegistry;

typedef plc_TestRegistry* plc_pTestRegistry;


#endif /* SRC_PLC_TESTTYPES_H_ */
