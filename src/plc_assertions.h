/**
 **********************************************************************
 * \file plc_assertions.h
 *
 * Short description of the file.
 * Long description of the file.
 *
 * Copyright (c) 2024, hoox.software, Helmbrechts
 * All Rights Reserved.
 *
 * Created on: 01.11.2016
 *     Author: patrickdressel
 *
 * Template: cpp_class_definition.hpp (Version 1)
 **********************************************************************
 */



#ifndef SRC_PLC_ASSERTIONS_H_
#define SRC_PLC_ASSERTIONS_H_

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
#include <plc_TestDebug.h>

void plc_AssertImpl(BOOL8 bInput, BOOL8 bFatal);

#define plc_Assert(value) \
  { plc_AssertImpl(value, FALSE); }

#define plc_Assert_Fatal(value) \
  { plc_AssertImpl(value, FALSE); }

#define plc_Assert_TRUE(value) \
  { plc_AssertImpl(value, FALSE); }

#define plc_Assert_TRUE_FATAL(value) \
  { plc_AssertImpl(value, FALSE); }

#define plc_Assert_FALSE(value) \
  { plc_AssertImpl(value, FALSE); }

#define plc_Assert_FALSE_FATAL(value) \
  { plc_AssertImpl(value, FALSE); }

#define plc_Assert_EQUAL(value, expected) \
  { plc_AssertImpl( (value == expected), FALSE); }

#define plc_Assert_EQUAL_Fatal(value, expected) \
  { plc_AssertImpl( (value == expected), TRUE); }

#define plc_Assert_NOT_EQUAL(value, expected) \
  { plc_AssertImpl( (value != expected), FALSE); }

#define plc_Assert_NOT_EQUAL_Fatal(value, expected) \
  { plc_AssertImpl( (value != expected), TRUE); }

#define plc_Assert_PTR_NULL(value) \
  { plc_AssertImpl( (value == NULL), FALSE); }

#define plc_Assert_PTR_NULL_Fatal(value) \
  { plc_AssertImpl( (value == NULL), TRUE); }

#define plc_Assert_PTR_NOT_NULL(value) \
  { plc_AssertImpl( (value != NULL), FALSE); }

#define plc_Assert_PTR_NOT_NULL_Fatal(value) \
  { plc_AssertImpl( (value != NULL), TRUE); }

#define plc_Assert_PTR_EQUAL(value, expected) \
  { plc_AssertImpl( (value != expected), TRUE); }

#define plc_Assert_PTR_EQUAL_Fatal(value, expected) \
  { plc_AssertImpl( (value != expected), TRUE); }

#define plc_Assert_PTR_NOT_EQUAL(value, expected) \
  { plc_AssertImpl( (value != expected), TRUE); }

#define plc_Assert_PTR_NOT_EQUAL_Fatal(value, expected) \
  { plc_AssertImpl( (value != expected), TRUE); }


#endif /* SRC_PLC_ASSERTIONS_H_ */
