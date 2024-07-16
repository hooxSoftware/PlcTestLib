/**
 **********************************************************************
 * \file plc_TestExport.h
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


#ifndef SRC_PLC_TESTEXPORT_H_
#define SRC_PLC_TESTEXPORT_H_

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
#include <plc_TestTypes.h>

/******************************************************************************
 * Typedefinitions
 *****************************************************************************/
typedef CHAR plc_TestBuffer_t[512];

/*
 **********************************************************************
 declarations
 **********************************************************************
 */
VOID plc_CreateJunit(const CHAR* strPath, const CHAR* strFile, plc_TestRegistry* pData);

VOID plc_CreateData(plc_TestRegistry* pData);

UINT32 plc_GetDuration(struct timespec *sStart, struct timespec *sEnd);

BOOL8 plc_CreateFolder(const CHAR* strPath);

/*
 **********************************************************************
 inline function definitions
 **********************************************************************
 */

#endif /* SRC_PLC_TESTEXPORT_H_ */
