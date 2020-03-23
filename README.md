# 🧪 ZenUnit &  ZenMock ⚗️</h1>

[![Standard](https://img.shields.io/badge/c%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17) [![License: Unlicense](https://img.shields.io/badge/license-Unlicense-blue.svg)](http://unlicense.org/)

ZenUnit is a single-header C++ unit testing framework designed for assertion exactness and long-term test readability. ZenUnit's signature feature is its intuitive syntax for writing value-parameterized and type-parameterized unit tests.

ZenMock is a single-header C++ mocking framework designed for function mocking exactness. ZenMock features an intuitive arrange-act-assert syntax for expecting and asserting the correctness of arguments and return values to and from virtual, non-virtual, static, and free functions.

|Build|Build Status|
|----------|------------|
|Travis CI Linux Clang 6.0.0 and GCC 7.4.0 Debug And Release|<a href="https://travis-ci.org/NeilJustice/ZenUnitAndZenMock"><img src="https://travis-ci.org/NeilJustice/ZenUnitAndZenMock.svg?branch=master"/></a>|
|AppVeyor Windows Visual Studio 2019 x64 and Win32 Debug And Release|<a href="https://ci.appveyor.com/project/NeilJustice/ZenUnitAndZenMock"><img src="https://ci.appveyor.com/api/projects/status/neqqkha7xbc93260?svg=true"/></a>|
|Code Coverage Of The Travis CI GCC 7.4.0 Release Build|[![codecov](https://codecov.io/gh/NeilJustice/ZenUnitAndZenMock/branch/master/graph/badge.svg)](https://codecov.io/gh/NeilJustice/ZenUnitAndZenMock)|

##### ZenUnit.h: [![download](https://img.shields.io/badge/download%20%20-link-blue.svg)](https://raw.githubusercontent.com/NeilJustice/ZenUnitAndZenMock/master/ZenUnit/ZenUnit.h)
##### ZenMock.h: [![download](https://img.shields.io/badge/download%20%20-link-blue.svg)](https://raw.githubusercontent.com/NeilJustice/ZenUnitAndZenMock/master/ZenMock/ZenMock.h)

   * [Unit Testing FizzBuzz With ZenUnit's Value-Parameterized Test Case Syntax](#unit-testing-fizzbuzz-with-zenunits-value-parameterized-test-case-syntax)
   * [ZenUnit Console Output](#zenunit-console-output)
   * [ZenUnit Command Line Usage](#zenunit-command-line-usage)
   * [ZenUnit Assertions](#zenunit-assertions)
      * [Value Assertions](#value-assertions)
      * [Pointer Assertions](#pointer-assertions)
      * [Data Structure Assertions](#data-structure-assertions)
      * [Floating Point Assertions](#floating-point-assertions)
      * [Exception Assertions](#exception-assertions)
      * [Function Assertions](#function-assertions)
      * [Memory Allocation Assertions](#memory-allocation-assertions)
      * [The FAIL_TEST Assertion](#the-fail_test-assertion)
   * [Macros For Defining And Running ZenUnit Unit Tests](#macros-for-defining-and-running-zenunit-unit-tests)
   * [Maximize Mutation Coverage By Testing With Random Values](#maximize-mutation-coverage-by-testing-with-random-values)
   * [Linux Jenkins Jobs That Build, Unit Test, clang-tidy, AddressSanitize, UndefinedBehaviorSanitize, And ThreadSanitize ZenUnit And ZenMock](#linux-jenkins-jobs-that-build-unit-test-clang-tidy-addresssanitize-undefinedbehaviorsanitize-and-threadsanitize-zenunit-and-zenmock)
   * [Windows Jenkins Jobs That Build And Unit Test ZenUnit And ZenMock](#windows-jenkins-jobs-that-build-and-unit-test-zenunit-and-zenmock)
   * [How To Build, Unit Test, And Install ZenUnit.h And ZenMock.h On Linux](#how-to-build-unit-test-and-install-zenunith-and-zenmockh-on-linux)
   * [How To Build, Unit Test, And Install ZenUnit.h And ZenMock.h On Windows](#how-to-build-unit-test-and-install-zenunith-and-zenmockh-on-windows)

### Unit Testing FizzBuzz With ZenUnit's Value-Parameterized Test Case Syntax

```cpp
#include "ZenUnit.h"

// Function to be unit tested with ZenUnit
std::string FizzBuzz(int endNumber);

// TESTS defines a ZenUnit test class and begins the FACTS section.
TESTS(FizzBuzzTests)
// FACTS declares an N-by-N value-parameterized test, the signature feature of ZenUnit.
FACTS(FizzBuzz_EndNumberIs0OrNegative_ThrowsInvalidArgument)
FACTS(FizzBuzz_EndNumberIsGreaterThan0_ReturnsFizzBuzzSequence)
// EVIDENCE concludes the declaration of facts section
// and begins the presentation of evidence section - also known as the test class body.
EVIDENCE

// In ZenUnit test names are duplicated between the FACTS section and the EVIDENCE section
// by way of a carefully-considered design decision to maximize long-term readability
// of safety-critical unit test code.
// This design of test names always up top instead of scattered throughout test files
// makes it easy to quickly confirm that a test class tests
// a cohesive set of functionality using a consistent test naming convention
// by simply reading the top of a ZenUnit tests file.

// TEST1X1 defines a 1-by-1 value-parameterized test
// that processes its typesafe variadic arguments list 1-by-1.
// This TEST1X1 defines 4 independent unit tests for FizzBuzz(),
// each of which will run sequentially within separate instances of test class FizzBuzzTests.
TEST1X1(FizzBuzz_EndNumberIs0OrNegative_ThrowsInvalidArgument,
   int invalidFizzBuzzEndNumber,
   std::numeric_limits<int>::min(),
   -2,
   -1,
   0)
{
   // The ZenUnit THROWS_EXCEPTION assertion asserts that an expression throws
   // *exactly* (not a derived class of) an expected exception type with
   // *exactly* expected exception what() text.

   // This double-exactness design of THROWS_EXCEPTION maximize mutation coverage,
   // the next frontier in software quality metrics beyond code coverage,
   // by rendering the THROWS_EXCEPTION assertion immune to these two easy-to-induce code mutations:
   // mutate-exception-type and mutate-exception-message.

   THROWS_EXCEPTION(FizzBuzz(invalidFizzBuzzEndNumber), std::invalid_argument,
      "Invalid FizzBuzz(int endNumber) argument: endNumber must be 1 or greater. endNumber="
         + std::to_string(invalidFizzBuzzEndNumber));
}

// TEST2X2 defines a 2-by-2 value-parameterized test
// that processes its typesafe variadic arguments list 2-by-2.
// This TEST2X2 defines 16 independent unit tests for FizzBuzz(),
// each of which will run sequentially within separate instances of test class FizzBuzzTests.
TEST2X2(FizzBuzz_EndNumberIsGreaterThan0_ReturnsFizzBuzzSequence,
   int endNumber, std::string_view expectedFizzBuzzSequence,
   1, "1",
   2, "1 2",
   3, "1 2 Fizz",
   4, "1 2 Fizz 4",
   5, "1 2 Fizz 4 Buzz",
   6, "1 2 Fizz 4 Buzz Fizz",
   7, "1 2 Fizz 4 Buzz Fizz 7",
   8, "1 2 Fizz 4 Buzz Fizz 7 8",
   9, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz",
   10, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz",
   11, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11",
   12, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz",
   13, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz 13",
   14, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz 13 14",
   15, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz 13 14 FizzBuzz",
   16, "1 2 Fizz 4 Buzz Fizz 7 8 Fizz Buzz 11 Fizz 13 14 FizzBuzz 16")
{
   const std::string fizzBuzzSequence = FizzBuzz(endNumber);
   // ZenUnit assertion names are declarative in language style (ARE_EQUAL, THROWS_EXCEPTION)
   // instead of procedural in language style (ASSERT_EQUAL, ASSERT_THROWS)
   // to give ZenUnit a test reading experience akin to reading an executable specification document.
   ARE_EQUAL(expectedFizzBuzzSequence, fizzBuzzSequence);
}

std::string FizzBuzz(int endNumber)
{
   if (endNumber <= 0)
   {
      throw std::invalid_argument(
         "Invalid FizzBuzz(int endNumber) argument: endNumber must be 1 or greater. endNumber="
         + std::to_string(endNumber));
   }
   std::ostringstream fizzBuzzSequenceBuilder;
   for (int i = 1; i <= endNumber; ++i)
   {
      const bool divisibleBy3 = i % 3 == 0;
      const bool divisibleBy5 = i % 5 == 0;
      if (divisibleBy3)
      {
         fizzBuzzSequenceBuilder << "Fizz";
      }
      if (divisibleBy5)
      {
         fizzBuzzSequenceBuilder << "Buzz";
      }
      if (!divisibleBy3 && !divisibleBy5)
      {
         fizzBuzzSequenceBuilder << i;
      }
      if (i < endNumber)
      {
         fizzBuzzSequenceBuilder << ' ';
      }
   }
   const std::string fizzBuzzSequence(fizzBuzzSequenceBuilder.str());
   return fizzBuzzSequence;
}

// RUN_TESTS registers a ZenUnit test class to be run when ZenUnit::RunTests(argc, argv) is called.
RUN_TESTS(FizzBuzzTests)

int main(int argc, char* argv[])
{
   const int exitCode = ZenUnit::RunTests(argc, argv);
   return exitCode;
}
```

### ZenUnit Console Output

![ZenUnit Console Output Design](Screenshots/FizzBuzzConsoleOutput.png)

### ZenUnit Command Line Usage

```
C++ Unit Testing Framework ZenUnit 0.6.0
https://github.com/NeilJustice/ZenUnitAndZenMock

Usage: <ZenUnitTestsBinaryName> [Options...]

Options For Testing Rigor:

--test-runs=<N>
   Repeat N times the running of all tests.
   Specify a negative number to repeat the running of run tests indefinitely.
--random-test-ordering
   Run test classes, tests, and value-parameterized test cases in a random order.
--random-seed=<32BitUnsignedValue>
   Sets the random seed which sets the ordering for --random-test-ordering and
   the ZenUnit::Random<T> family of random-value-generating functions.
   The default random seed is the number of seconds since 1970-01-01 00:00:00 UTC.
--exit-1-if-tests-skipped
   After having run all tests, exit with code 1 if any tests were skipped.

Options For Testing Selection:

--fail-fast
   If a test fails, call exit(1).
--run=<TestClassName>[::TestName][/TestCaseNumber][,...]
   Run only the specified case-insensitive test classes, tests, and/or test case numbers.
   Add a '*' character to the end of a test class name or test name
   filter string to specify name-starts-with filtration.
 Example 1: --run=APITests
   Run only test class APITests.
 Example 2: --run=APITests::FunctionUnderTest*
   Run only tests in APITests that start with "FunctionUnderTest".
 Example 3: --run=APITests::FunctionUnderTest_ArgumentsUnderTest_ExpectedReturnValue/3
   Run only the third test case of the value-parameterized test named
   APITests::FunctionUnderTest_ArgumentsUnderTest_ExpectedReturnValue.

Options For Testing Utility:

--pause-before
   Wait for any key before running tests to allow attaching of a profiler or debugger.
--pause-after
   Wait for any key after running tests.
   This is a useful command line argument for desktop shortcuts that run ZenUnit tests.
--always-exit-0
   Always exit with code 0 even if there are test failures.
--help
   Print this help message.
--version
   Print the ZenUnit version number.

Example ZenUnit command line arguments:

--test-runs=5 --random-test-ordering --exit-1-if-tests-skipped
```

## ZenUnit Assertions

#### Value Assertions
|Assertion|Behavior|
|---------|--------|
|`ARE_EQUAL(expectedValue, actualValue, messages...)`|By default, asserts that `expectedValue == actualValue` returns true, otherwise throws a `ZenUnit::Anomaly`, which is caught by ZenUnit to fail the current test. `messages...` are variables of any type writable with `operator<<(std::ostream&, const T&)` or `ZenUnit::Printer<T>::Print(std::ostream&, const T&)`.|
|`ARE_NOT_EQUAL(notExpectedValue, actualValue, messages...)`|By default, asserts that `!(expectedValue == actualValue)` returns true, otherwise throws a `ZenUnit::Anomaly`.|
|`ARE_COPIES(expectedObject, actualObject, messages...)`|Asserts that `&expectedObject != &actualObject` then asserts `ARE_EQUAL(expectedObject, actualObject)`.|
|`IS_TRUE(value, messages...)`|Asserts that `value` is true.|
|`IS_FALSE(value, messages...)`|Asserts that `value` is false.|
|`IS_ZERO(value, messages...)`|Asserts that `value == 0` is true.|
|`IS_DEFAULT_VALUE(value, messages...)`|Asserts that `value == ValueType{}` is true.|
|`IS_NOT_DEFAULT_VALUE(value, messages...)`|Asserts that `value == ValueType{}` is false.|

#### Pointer Assertions
|Assertion|Behavior|
|---------|--------|
|`POINTER_IS_NULL(pointer, messages...)`|Asserts that `pointer == nullptr`.|
|`POINTER_IS_NOT_NULL(pointer, messages...)`|Asserts that `pointer != nullptr`.|
|`ARE_SAME(expectedObject, actualObject, messages...)`|Asserts that `&expectedObject == &actualObject`.|
|`ARE_NOT_SAME(notExpectedObject, actualObject, messages...)`|Asserts that `&expectedObject != &actualObject`.
|`POINTEES_ARE_EQUAL(expectedPointer, actualPointer, messages...)`|Asserts that `expectedPointer != nullptr` and `actualPointer != nullptr` then asserts `ARE_EQUAL(*expectedPointer, *actualPointer)`.|
|`POINTEE_IS_EXACT_TYPE(expectedPolymorphicPointeeType, actualPointer, messages...)`|First statically asserts `static_assert(std::is_polymorphic_v<expectedPolymorphicPointeeType>)`, then asserts `actualPointer != nullptr`, then asserts `typeid(expectedPolymorphicPointeeType) == typeid(*actualPointer)`. This is a useful assertion for confirming the correctness of factory functions that return a newed instance of a subclass as a base class pointer.|

#### Data Structure Assertions
|Assertion|Behavior|
|---------|--------|
|`VECTORS_EQUAL(expectedVector, actualVector, messages...)`|Asserts that `expectedVector.size() == actualVector.size()` then calls `ARE_EQUAL(ithExpectedElement, ithActualElement)` on each pair of expected and actual elements.|
|`SETS_EQUAL(expectedSet, actualSet, messages...)`|Asserts that `expectedSet.size() == actualSet.size()` then calls `ARE_EQUAL(expectedElement, actualElement)` on each pair of expected and actual elements.|
|`MAPS_EQUAL(expectedMap, actualMap, messages...)`|Asserts that `expectedMap.size() == actualMap.size()` then calls `ARE_EQUAL(expectedKeyValuePair, actualKeyValuePair)` on each pair of expected and actual key-value pairs.
|`PAIRS_EQUAL(expectedPair, actualPair, messages...)`|Asserts `ARE_EQUAL(expectedPair.first, actualPair.first)` then asserts `ARE_EQUAL(expectedPair.second, actualPair.second)`.|
|`ARRAYS_EQUAL(expectedArray, actualArray, numberOfElementsToCompare, messages...)`|Asserts `ARE_EQUAL` on each expected and actual array element up to numberOfElementsToCompare elements.|
|`STD_ARRAYS_EQUAL(expectedStdArray, actualStdArray, messages...)`|Asserts `ARE_EQUAL` on each expected and actual `std::array` element.|
|`CONTAINS_ELEMENT(expectedElement, dataStructure, messages...)`|Asserts that `dataStructure.find(expectedElement) != dataStructure.end()`.|
|`IS_EMPTY(dataStructure, messages...)`|Asserts that `dataStructure.empty()` equals true.|
|`IS_NOT_EMPTY(dataStructure, messages...)`|Asserts that `dataStructure.empty()` equals false.|

#### Floating Point Assertions
|Assertion|Behavior|
|---------|--------|
|`ARE_WITHIN(expectedFloatingPointValue, actualFloatingPointValue, expectedAbsoluteMaxDifference, messages...)`|Asserts that `std::abs(expectedFloatingPointValue - actualFloatingPointValue) <= expectedAbsoluteMaxDifference`.|

#### Exception Assertions
|Assertion|Behavior|
|---------|--------|
|`THROWS_EXCEPTION(expression, expectedExactExceptionType, expectedExactWhatMessage, messages...)`|Asserts that `expression` throws \*exactly\* (not a derived class of) `expectedExactExceptionType` with \*exactly\* a what() message equal to `expectedWhatMessage`.|
|`DOES_NOT_THROW(expression, messages...)`|If `expression` throws, throws a `ZenUnit::Anomaly`, otherwise does nothing. Useful assertion for emphasis to the reader of a unit test.|

#### Function Assertions
|Assertion|Behavior|
|---------|--------|
|`STD_FUNCTION_TARGETS(expectedStaticOrFreeFunction, stdFunction, messages...)`|First asserts `IS_TRUE(stdFunction)`, which asserts that stdFunction points to a function, then asserts `ARE_EQUAL(expectedStaticOrFreeFunction, *stdFunction.target<decltype(expectedStaticOrFreeFunction)*>())`. This is a key assertion to call prior to overwriting a `std::function` with a ZenMock mock object.|
|`STD_FUNCTION_TARGETS_OVERLOAD(expectedOverloadTypeInTheFormOfAUsing, expectedStaticOrFreeFunction, stdFunction, messages...)`|Same as above but with `static_cast<expectedOverloadTypeInTheFormOfAUsing>(expectedStaticOrFreeFunction)`.|

### Memory Allocation Assertions
|Assertion|Behavior|
|---------|--------|
|`DELETE_TO_ASSERT_NEWED(smartOrRawPointer, messages...)`|Asserts `smartOrRawPointer != nullptr` then calls `reset()` or `operator delete` on `smartOrRawPointer` to confirm the pointer was allocated using `make_unique`, `make_shared`, or `operator new`. This is a key assertion for robustness against the swap-new-with-null code mutation.|
|`DELETE_TO_ASSERT_ARRAY_NEWED(smartOrRawArrayPointer, messages...)`|Asserts `smartOrRawArrayPointer != nullptr` then calls `reset()` or `operator delete[]` to confirm the pointer was allocated using `make_unique` or `operator new[]`. This is a key assertion for robustness against the swap-new-with-null code mutation.|

#### The FAIL_TEST Assertion
|Assertion|Behavior|
|---------|--------|
|`FAIL_TEST(testFailureReason, messages...)`|Throws a `ZenUnit::Anomaly` which is caught by ZenUnit to end the current test and begin the next test.|

### Macros For Defining And Running ZenUnit Unit Tests

|Test Classes|Behavior|
|------------|--------|
|`TESTS(HighQualityTestClassName)`|Defines a non-templatized test class.|
|`TEMPLATE_TESTS(HighQualityTestClassName, TemplateParameterNames...)`|Defines a templatized test class. Precede with template\<parameter-list\>.|
|`AFACT(HighQualityTestName)`|Declares a non-value-parameterized test.|
|`FACTS(HighQualityTestName)`|Declares an N-by-N value-parameterized test.|
|`SKIPAFACT(HighQualityTestName, Reason)`|Skips a non-value-parameterized test.|
|`SKIPFACTS(HighQualityTestName, Reason)`|Skips an N-by-N value-parameterized test.|
|`EVIDENCE`|Concludes the declaration of FACTS section and begins the presentation of EVIDENCE section, also known as the test class body.|
|`STARTUP`|Defines a function to be run before each test.|
|`CLEANUP`|Defines a function to be run after each test.|
|`TEST(HighQualityTestName)`|Defines a non-value-parameterized test.|
|`TEST1X1(HighQualityTestName, Arg1Type, 1By1CommaSeparatedTestCaseValueLiterals...)`|Defines a 1-by-1 value-parameterized test.|
|`TEST2X2(HighQualityTestName, Arg1Type, Arg2Type, 2By2CommaSeparatedTestCaseValueLiterals...)`|Defines a 2-by-2 value-parameterized test.|
|`TEST3X3(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, 3By3CommaSeparatedTestCaseValueLiterals...)`|Defines a 3-by-3 value-parameterized test.|
|`TEST4X4(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, 4By4CommaSeparatedTestCaseValueLiterals...)`|Defines a 4-by-4 value-parameterized test.|
|`TEST5X5(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, 5By5CommaSeparatedTestCaseValueLiterals...)`|Defines a 5-by-5 value-parameterized test.|
|`TEST6X6(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, 6By6CommaSeparatedTestCaseValueLiterals...)`|Defines a 6-by-6 value-parameterized test.|
|`TEST7X7(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, 7By7CommaSeparatedTestCaseValueLiterals...)`|Defines a 7-by-7 value-parameterized test.|
|`TEST8X8(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, 8By8CommaSeparatedTestCaseValueLiterals...)`|Defines an 8-by-8 value-parameterized test.|
|`TEST9X9(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, 9By9CommaSeparatedTestCaseValueLiterals...)`|Defines a 9-by-9 value-parameterized test.|
|`TEST10X10(HighQualityTestName, Arg1Type, Arg2Type, Arg3Type, Arg4Type, Arg5Type, Arg6Type, Arg7Type, Arg8Type, Arg9Type, Arg10Type, 10By10CommaSeparatedTestCaseValueLiterals...)`|Defines a 10-by-10 value-parameterized test.|
|`RUN_TESTS(HighQualityTestClassName)`|Registers a `TEST_CLASS` to be run when `ZenUnit::RunTests(argc, argv)` is called.|
|`SKIP_TESTS(HighQualityTestClassName, Reason)`|Prevents a `TEST_CLASS` from running when `ZenUnit::RunTests(argc, argv)` is called.|
|`RUN_TEMPLATE_TESTS(HighQualityTestClassName, TemplateArguments...)`|Registers a `TEMPLATE_TEST_CLASS` templatized with `TemplateArguments...` to be run when `ZenUnit::RunTests(argc, argv)` is called.|
|`THEN_RUN_TEMPLATE_TESTS(HighQualityTestClassName, TemplateArguments...)`|Registers a `TEMPLATE_TEST_CLASS` templatized with `TemplateArguments...` to be run when `ZenUnit::RunTests(argc, argv)` is called. For use after `RUN_TEMPLATE_TESTS`.|
|`SKIP_TEMPLATE_TESTS(HighQualityTestClassName, Reason, TemplateArguments...)`|Prevents a `TEMPLATE_TEST_CLASS` from running when `ZenUnit::RunTests(argc, argv)` is called.|
|`THEN_SKIP_TEMPLATE_TESTS(HighQualityTestClassName, Reason, TemplateArguments...)`|Prevents a `TEMPLATE_TEST_CLASS` from running when `ZenUnit::RunTests(argc, argv)` is called. For use after `SKIP_TEMPLATE_TESTS`.|

### Maximize Mutation Coverage By Testing With Random Values

ZenUnit provides the following random-value-generating functions for maximizing [mutation coverage](https://en.wikipedia.org/wiki/Mutation_testing), the next frontier in software quality metrics beyond code coverage. Testing using random values instead of constant values renders test code immune to the `swap-variable-with-constant` code mutation, which is a straightforward code mutation to induce manually today during code review time or automatically in the 2020s during CI/CD time by running an LLVM-powered mutation testing framework such as [Mull](https://github.com/mull-project/mull).

|Random Value Generating Function|Behavior|
|--------------------------------|--------|
|`ZenUnit::Random<T>()`|By default returns a random integer of type T between `std::numeric_limits<T>::min()` and `std::numeric_limits<T>::max()` selected from a uniform distribution. If `UserType ZenUnit::Random<UserType>()` is defined, returns the result from calling that function.|
|`ZenUnit::RandomNon0<T>()`|Returns a random non-0 integer of type T between `std::numeric_limits<T>::min()` and `std::numeric_limits<T>::max()` selected from a uniform distribution.|
|`ZenUnit::RandomBetween<T>(long long inclusiveMinValue, unsigned long long inclusiveMaxValue)`|Returns a random integer of type T between inclusiveMinValue and inclusiveMaxValue selected from a uniform distribution.|
|`ZenUnit::RandomEnum<EnumType>()`|Returns a random EnumType value between 0 and EnumType::MaxValue - 1, selected from a uniform distribution.|
|`ZenUnit::Random<float>()`|Returns a random float between `std::numeric_limits<float>::min()` and `std::numeric_limits<float>::max()` selected from a `std::uniform_real_distribution<float>`.|
|`ZenUnit::Random<double>()`|Returns a random double between `std::numeric_limits<double>::min()` and `std::numeric_limits<double>::max()` from a `std::uniform_real_distribution<double>`.|
|`ZenUnit::Random<std::string>()`|Returns `"RS" + std::to_string(ZenUnit::RandomBetween<int>(0, 100000))`.|
|`ZenUnit::RandomVector<T>()`|Returns a `std::vector<T>` with size between 0 and 3 with each element a `ZenUnit::Random<T>()` value.|
|`ZenUnit::RandomMap<KeyType, ValueType>()`|Returns a `std::map<KeyType, ValueType>` with size between 0 and 3 with each key a `ZenUnit::Random<KeyType>()` value and each value a `ZenUnit::Random<ValueType>()` value.|
|`ZenUnit::RandomUnorderedMap<T>()`|Returns a `std::unordered_map<KeyType, ValueType>` with size between 0 and 3 with each key a `ZenUnit::Random<KeyType>()` value and each value a `ZenUnit::Random<ValueType>()` value.|
|`ZenUnit::RandomSet<T>()`|Returns a `std::set<T>` with size between 0 and 3 with each element a `ZenUnit::Random<T>()` value.|
|`ZenUnit::RandomUnorderedSet<T>()`|Returns a `std::unordered_set<T>` with size between 0 and 3 with each element a `ZenUnit::Random<T>()` value.|

### Linux Jenkins Jobs That Build, Unit Test, clang-tidy, AddressSanitize, UndefinedBehaviorSanitize, And ThreadSanitize ZenUnit And ZenMock

![Linux Jenkins Jobs That Compile, clang-tidy, AddressSanitize, UndefinedBehaviorSanitize, and ThreadSanitize ZenUnit And ZenMock](Screenshots/LinuxJenkinsJobsForZenUnitAndZenMock.png)

### Windows Jenkins Jobs That Build And Unit Test ZenUnit And ZenMock

![Windows Jenkins Jobs That Compile ZenUnit And ZenMock](Screenshots/WindowsJenkinsJobsForZenUnitAndZenMock.png)

### How To Build, Unit Test, And Install ZenUnit.h And ZenMock.h On Linux

```
git clone https://github.com/NeilJustice/ZenUnitAndZenMock

cd ZenUnitAndZenMock && mkdir Debug && cd Debug

CXX=clang++ cmake .. -GNinja -DCMAKE_BUILD_TYPE=Debug

# Builds ZenUnit and ZenMock Debug unit test binaries
# then copies ZenUnit.h and ZenMock.h:
# ZenUnit.h to /usr/local/include/ZenUnit/ZenUnit.h and
# ZenMock.h to /usr/local/include/ZenMock/ZenMock.h
sudo cmake --build . --target install

cd ..

# Runs all ZenUnit and ZenMock Debug test binaries:
# Debug/ZenMockTests/ZenMockTests
# Debug/ZenMockExamples/ZenMockExamples
# Debug/ZenUnitLibraryTests/ZenUnitLibraryTests
# Debug/ZenUnitUtilsAndAssertionTests/ZenUnitUtilsAndAssertionTests
# Debug/ZenUnitExamples/ZenUnitExamples
./TestScripts/RunAllDebugTests.sh
```

### How To Build, Unit Test, And Install ZenUnit.h And ZenMock.h On Windows

```
git clone https://github.com/NeilJustice/ZenUnitAndZenMock

cd ZenUnitAndZenMock

cmake . -G"Visual Studio 16 2019" -A x64 -DCMAKE_INSTALL_PREFIX=C:\

# Builds and runs during post-build events all
# ZenUnit and ZenMock Debug test binaries:
# ZenMockTests\Debug\ZenMockTests.exe
# ZenMockExamples\Debug\ZenMockExamples.exe
# ZenUnitLibraryTests\Debug\ZenUnitLibraryTests.exe
# ZenUnitUtilsAndAssertionTests\Debug\ZenUnitUtilsAndAssertionTests.exe
# ZenUnitExamples\Debug\ZenUnitExamples.exe

# Then copies ZenUnit.h and ZenMock.h:
# ZenUnit.h to C:\include\ZenUnit\ZenUnit.h
# ZenMock.h to C:\include\ZenMock\ZenMock.h

cmake --build . --target install
```
