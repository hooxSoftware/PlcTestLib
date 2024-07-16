/**
 **********************************************************************
 * \file plc_UnitTest.h
 *
 * Short description of the file.
 * Long description of the file.
 *
 * Copyright (c) 2016, hoox.software, Helmbrechts \n
 * All Rights Reserved.
 *
 * Created on: 31.10.2016
 *     Author: patrickdressel
 *
 * Template: cpp_class_definition.hpp (Version 1)
 **********************************************************************
 */
#ifndef SRC_PLC_TESTREGISTRY_H_
#define SRC_PLC_TESTREGISTRY_H_
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
#include <plc_TestSuite.h>


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
plc_EErrorCode plc_initialize_TestRegistry();

plc_pTestRegistry plc_create_TestRegistry();

plc_EErrorCode plc_cleanup_TestRegistry();

plc_EErrorCode plc_run_all();

BOOL8 plc_is_test_running(void);

plc_pTest plc_getTest(CHAR8* pName);

plc_pTest plc_get_current_test(void);

void plc_export_TestRegistry(CHAR *strPath, CHAR *strFile);

#endif /* SRC_PLC_TESTREGISTRY_H_ */
