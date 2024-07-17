# PlcTestLib
UnitTest library for Bachmann Electronic PLC Developer

# Usage

the project sample contains some code showing the
usage of the library.

Download it with the compiled library here
https://www.hoox.software/downloads.html#bachmann

## First you have to register a testsuite 

PlcTest_CreateTestsuite(Name of testsuite, Path to tested function)

## register tests 

PlcTest_addTest(Testsuite ID, Testname, name of tested function, pointer to SPlcTest_Test)
SPlcTest_Test works as interface between library and test plc

## start test

SPlcTest_Test.bStart = true -> this test is running

## finish test

call PlcTest_TestFinished to tell the library that the next test can be
started

# Elements

## PlcTest_Start

## PlcTest_isFinished

## PlcTest_ExportResult

## PlcTest_getError

## PlcTest_TestFinished

## Assertions

### PlcTest_ASSERT_TRUE

### PlcTest_ASSERT_FALSE

### PlcTest_ASSERT_EQUAL_TIME

### PlcTest_ASSERT_NOT_EQUAL_TIME

### PlcTest_ASSERT_EQUAL_REAL

### PlcTest_ASSERT_NOT_EQUAL_REAL

### PlcTest_ASSERT_EQUAL_STRING

### PlcTest_ASSERT_NOT_EQUAL_STRING

### PlcTest_ASSERT_EQUAL_NSTRING

### PlcTest_ASSERT_NOT_EQUAL_NSTRING



