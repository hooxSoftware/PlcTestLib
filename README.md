## PlcTestLib
UnitTest library for Bachmann Electronic PLC Developer

### Usage

the project sample contains some code showing the
usage of the library.

Download it with the compiled library here
https://www.hoox.software/downloads.html#bachmann

1. First you have to register a testsuite

PlcTest_CreateTestsuite(Name of testsuite, Path to tested function)

2. register tests

PlcTest_addTest(Testsuite ID, Testname, name of tested function, pointer to SPlcTest_Test)
SPlcTest_Test works as interface between library and test plc

3. start test

SPlcTest_Test.bStart = true -> this test is running

4. finish test 

call PlcTest_TestFinished to tell the library that the next test can be
started

### Elements

#### SPlcTest_Test

|Variable|Type|Description|
|---|---|---|
|bStart    |BOOL|---|
|bFinished |BOOL|---|
|s32State  |DINT|---|


#### Test State
|Value|Description|
|---   |--- |
|0    |skipped|
|1 	|passed|
|-1  	|failed|


#### PlcTest_CreateTestsuite
|Variable|Type|Description|
|--|--|--|
|strName   |String|--|
|strPackage|String|--|


#### PlcTest_addTest
|Variable|Type|Description|
|--|--|--|
|TestSuiteID   |DINT     |--|
|strName       |String   |--|
|strClass      |String   |--|
|pInfo         |POINTER TO SPlcTest_Test|--|


#### PlcTest_Start
run all registered tests


#### PlcTest_isFinished
check if testrun is finished
returns 
	true  : finished
	false : running or not started


#### PlcTest_ExportResult
|Variable|Type|Description|
|--|--|--|
|strPath   |String|--|
|strFile   |String|--|


#### PlcTest_getError
check if error occured during testrun
returns 
	true  : error occured
	false : no error


#### PlcTest_TestFinished
call if your test is finished

## Assertions

#### PlcTest_SetMessage
|Variable|Type|Description|
|--|--|--|
|strMessage   |String|--|


#### PlcTest_ASSERT_TRUE
|Variable|Type|Description|
|--|--|--|
|in   |BOOL|--|


#### PlcTest_ASSERT_FALSE
|Variable|Type|Description|
|--|--|--|
|in   |BOOL|--|


#### PlcTest_ASSERT_EQUAL
|Variable|Type|Description|
|--|--|--|
|actual   |DINT|--|
|expected |DINT|--|


#### PlcTest_ASSERT_NOT_EQUAL
|Variable|Type|Description|
|--|--|--|
|actual   |DINT|--|
|expected |DINT|--|


#### PlcTest_ASSERT_EQUAL_TIME
|Variable|Type|Description|
|--|--|--|
|actual   |TIME|--|
|expected |TIME|--|


#### PlcTest_ASSERT_NOT_EQUAL_TIME
|Variable|Type|Description|
|--|--|--|
|actual   |TIME|--|
|expected |TIME|--|


#### PlcTest_ASSERT_EQUAL_REAL
|Variable|Type|Description|
|--|--|--|
|actual   		|REAL|--|
|expected 		|REAL|--|
|granularity 	|REAL|--|


#### PlcTest_ASSERT_NOT_EQUAL_REAL
|Variable|Type|Description|
|--|--|--|
|actual   		|REAL|--|
|expected 		|REAL|--|
|granularity 	|REAL|--|


#### PlcTest_ASSERT_EQUAL_STRING
|Variable|Type|Description|
|--|--|--|
|actual   |STRING|--|
|expected |STRING|--|


#### PlcTest_ASSERT_NOT_EQUAL_STRING
|Variable|Type|Description|
|--|--|--|
|actual   |STRING|--|
|expected |STRING|--|


#### PlcTest_ASSERT_EQUAL_NSTRING
|Variable|Type|Description|
|--|--|--|
|actual   |STRING|--|
|expected |STRING|--|
|size 	 |UDINT|--|


#### PlcTest_ASSERT_NOT_EQUAL_NSTRING
|Variable|Type|Description|
|--|--|--|
|actual   |STRING|--|
|expected |STRING|--|
|size 	 |UDINT|--|


