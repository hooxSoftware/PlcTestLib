/**
 **********************************************************************
 * \file plc_Test.h
 *
 * Short description of the file.
 * Long description of the file.
 *
* Copyright (c) 2024, hoox.software, Helmbrechts \n
 * All Rights Reserved.
 *
 * Created on: 26.01.2024
 *     Author: patrickdressel
 *
 * Template: cpp_class_definition.hpp (Version 1)
 **********************************************************************
 */

#ifndef SRC_PLC_TEST_H_
#define SRC_PLC_TEST_H_
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
plc_pTest plc_create_Test(CHAR8* pName, CHAR8* pClass);

plc_EErrorCode plc_cleanup_Test(plc_pTest pTest);

plc_pTest plc_getFirstTest(plc_TestSuite* pSuite);

plc_pTest plc_getNextTest(plc_pTest pTest);

plc_EErrorCode plc_prepare_Test(plc_pTest pTest);

plc_EErrorCode plc_run_Test(plc_pTest pTest);






#endif /* SRC_PLC_TEST_H_ */
