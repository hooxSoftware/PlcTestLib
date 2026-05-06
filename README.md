## PlcTestLib
UnitTest library for Bachmann Electronic PLC Developer

### Download

Download the compiled library and project sample here:
https://www.hoox.software/downloads.html#bachmann

---

### Claude AI Integration

This repository includes a Claude skill that enables AI-assisted test generation for the PlcTestLib framework.

#### Install Claude Skill

1. Download `bachmann-plctestlib.skill` from this repository
2. Open [claude.ai](https://claude.ai) and go to **Settings → Claude's skills**
3. Click **Import skill** and select the `.skill` file
4. Claude now understands the PlcTestLib framework and can generate test suites, assertions, and boilerplate code for Bachmann PLCs

#### Install SolutionCenter File Template

1. Open the Bachmann SolutionCenter
2. Go to **Window → Preferences → SolutionCenter → M200 → PLC Developer → File Templates**
3. Click **Import...** and select `assets/FB_Testsuite.tmp`
4. When creating a new Function Block, select **Use template → FB_Testsuite** to get a ready-to-use test suite scaffold

---

### Usage

The project sample contains some code showing the usage of the library.

1. First you have to register a testsuite

PlcTest_CreateTestsuite(Name of testsuite, Path to tested function)

2. register tests

PlcTest_addTest(Testsuite ID, Testname, name of tested function, pointer to SPlcTest_Test)<br>
SPlcTest_Test works as interface between library and test plc

3. start test

SPlcTest_Test.bStart = true -> this test is running

4. finish test 

call PlcTest_TestFinished to tell the library that the next test can be started

### Elements

#### SPlcTest_Test

|Variable|Type|Description|
|---|---|---|
|bStart    |BOOL|test starts|
|bFinished |BOOL|test is finished|
|s32State  |DINT|state of test |


#### Test State
|Value|Description|
|---   |--- |
|0    |skipped|
|1 	|passed|
|-1  	|failed|


#### PlcTest_CreateTestsuite
|Return|Description|
|---   |--- |
|0     |error|
|<> 0  |id (DINT) of created testsuite|

|Variable|Type|Description|
|--|--|--|
|strName   |String|Name of testsuite|
|strPackage|String|path to pous|


#### PlcTest_addTest
|Variable|Type|Description|
|--|--|--|
|TestSuiteID   |DINT     |--|
|strName       |String   |Name of test|
|strClass      |String   |name of pou to test|
|pInfo         |POINTER TO SPlcTest_Test| interface to controls structure|


#### PlcTest_Start
run all registered tests


#### PlcTest_isFinished
check if testrun is finished

|Return|Description|
|---    |--- |
|true   |finished|
|false  |running or not started|



#### PlcTest_ExportResult
|Variable|Type|Description|
|--|--|--|
|strPath   |String|where to store the result 'cfc0/test/'|
|strFile   |String|filename 'junit.xml'|


#### PlcTest_getError
check if error occured during testrun

|Return|Description|
|---    |--- |
|true   |error occured|
|false  |no error|


#### PlcTest_TestFinished
call if your test is finished

## Assertions
Assertion always compare an actual and an expected value. <br>
If both are equal or not_equal (depending on the called function)<br>
the test will pass or fail.

assert_true/assert_false are working with a single boolean <br>
comparison like <br> 
assert_true(0=1) : will fail <br>
assert_true(1=1) : will pass 

#### PlcTest_SetMessage
|Variable|Type|Description|
|--|--|--|
|strMessage   |String|message to store in result on error|


#### PlcTest_ASSERT_TRUE
|Variable|Type|
|--|--|
|in   |BOOL|


#### PlcTest_ASSERT_FALSE
|Variable|Type|
|--|--|
|in   |BOOL|


#### PlcTest_ASSERT_EQUAL
|Variable|Type|
|--|--|
|actual   |DINT|
|expected |DINT|


#### PlcTest_ASSERT_NOT_EQUAL
|Variable|Type|
|--|--|
|actual   |DINT|
|expected |DINT|


#### PlcTest_ASSERT_EQUAL_TIME
|Variable|Type|
|--|--|
|actual   |TIME|
|expected |TIME|


#### PlcTest_ASSERT_NOT_EQUAL_TIME
|Variable|Type|
|--|--|
|actual   |TIME|
|expected |TIME|


#### PlcTest_ASSERT_EQUAL_REAL
|Variable|Type|
|--|--|
|actual   		|REAL|
|expected 		|REAL|
|granularity 	|REAL|


#### PlcTest_ASSERT_NOT_EQUAL_REAL
|Variable|Type|
|--|--|
|actual   		|REAL|
|expected 		|REAL|
|granularity 	|REAL|


#### PlcTest_ASSERT_EQUAL_STRING
This assertion calls a simple strcmp <br>
|Variable|Type|
|--|--|
|actual   |STRING|
|expected |STRING|


#### PlcTest_ASSERT_NOT_EQUAL_STRING
This assertion calls a simple strcmp <br>
|Variable|Type|
|--|--|
|actual   |STRING|
|expected |STRING|


#### PlcTest_ASSERT_EQUAL_NSTRING
This assertion calls strncmp <br>
|Variable|Type|
|--|--|
|actual   |STRING|
|expected |STRING|
|size 	 |UDINT|


#### PlcTest_ASSERT_NOT_EQUAL_NSTRING
This assertion calls strncmp <br>
|Variable|Type|
|--|--|
|actual   |STRING|
|expected |STRING|
|size 	 |UDINT|


#### PlcTest_ASSERT_IS_INFINITE
|Variable|Type|
|--|--|
|actual   		|REAL|

#### PlcTest_ASSERT_IS_NAN
|Variable|Type|
|--|--|
|actual   		|REAL|