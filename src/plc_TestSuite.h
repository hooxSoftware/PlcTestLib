/**
 **********************************************************************
 * \file plc_TestSuite.h
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
#ifndef SRC_PLC_TESTSUITE_H_
#define SRC_PLC_TESTSUITE_H_
/*
 **********************************************************************
 system includes
 **********************************************************************
 */
#include <mtypes.h>

/*
 **********************************************************************
 project includes
 **********************************************************************
 */
#include <plc_Test.h>

/*
 **********************************************************************
 Typedefintions
 **********************************************************************
 */
#include <plc_TestTypes.h>


/*
 **********************************************************************
 variable defintions
 **********************************************************************
 */


/*
 **********************************************************************
 functiondefintions
 **********************************************************************
 */

plc_pTestSuite plc_createTestSuite(CHAR8* pName, CHAR8* pPackage);

SINT32 plc_addTestSuite(CHAR8* pName, CHAR8* pPackage);

plc_EErrorCode plc_cleanup_TestSuite(plc_pTestSuite pSuite);

plc_pTestSuite plc_getSuite(CHAR8* pName);

plc_pTestSuite plc_getFirstSuite();

plc_pTestSuite plc_getLastSuite();

plc_pTestSuite plc_getNextSuite(plc_pTestSuite);

plc_EErrorCode plc_run_Suite(CHAR8* pName);

plc_pTestSuite plc_get_current_suite(void);

plc_EErrorCode plc_addTest(plc_pTestSuite pSuite, CHAR8* pName, CHAR8* pClass, VOID* pTest);



#endif //SRC_PLC_TESTSUITE_H_
