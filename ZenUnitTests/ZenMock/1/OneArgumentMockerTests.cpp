#include "pch.h"
#include "ZenUnit/ZenMock/1/OneArgumentMocker.h"
#include "ZenUnitTests/ZenMock/Mock/ExceptionThrowerMock.h"

namespace ZenMock
{
   TESTS(OneArgumentMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(Expect_AlreadyExpected_Throws)
   AFACT(Expect_NotAlreadyExpected_SetsExpectedTrue)
   AFACT(ExpectAndThrow_ExpectedTrue_Throws)
   AFACT(ExpectAndThrow_ExpectedFalse_CallsExceptionThrowerExpectAndThrow_SetsExpectedTrue)
   AFACT(ZenMockIt_ExpectedFalse_Throws)
   AFACT(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)

   FACTS(AssertCalledOnceWith_SetsAssertedTrue_FunctionWasCalledOnceWithExpectedArg_DoesNotThrow)
   AFACT(AssertCalledNTimesWith_NIsZero_Throws)
   FACTS(AssertCalledNTimesWith_SetsAssertedTrue_NDiffersFromActualCallCount_Throws)
   FACTS(AssertCalledNTimesWith_SetsAssertedTrue_NEqualToNumberOfCalls_ThrowsIfArgsDoNotMatch)
   AFACT(AssertCalls_ExpectedCallsSize0_Throws_DoesNotSetAssertedTrue)
   AFACT(AssertCalls_SetsAssertedTrue_ExpectedCallsSizeNon0AndNotEqualToActualCallsSize_Throws_DoesNotCopyTheExpectedArg)
   AFACT(AssertCalls_SetsAssertedTrue_ExpectedCallsSizeNon0AndEqualToNumberOfCalls_ArgsNotEqual_Throws_DoesNotCopyTheExpectedArg)
   AFACT(AssertCalls_SetsAssertedTrue_ExpectedCallsSizeNon0AndEqualToNumberOfCalls_ArgsEqual_DoesNotThrow_DoesNotCopyTheExpectedArg)
   EVIDENCE

   using MockerType = OneArgumentMocker<int, ExceptionThrowerMock>;
   unique_ptr<MockerType> _mocker;
   string _signature;

   STARTUP
   {
      _signature = ZenUnit::Random<string>();
      _mocker = make_unique<MockerType>(_signature);
   }

   void SetAssertedTrueToNotFailDueToExpectedButNotAsserted()
   {
      _mocker->_asserted = true;
   }

   TEST(Constructor_SetsFields)
   {
      const MockerType mocker(_signature);
      //
      ARE_EQUAL(_signature, mocker.ZenMockedFunctionSignature);
      IS_FALSE(mocker._expected);
      IS_FALSE(mocker._asserted);
      IS_EMPTY(mocker.callHistory);
   }

   TEST(Expect_AlreadyExpected_Throws)
   {
      _mocker->_expected = true;
      THROWS(_mocker->Expect(), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(_signature));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(Expect_NotAlreadyExpected_SetsExpectedTrue)
   {
      IS_FALSE(_mocker->_expected);
      //
      _mocker->Expect();
      //
      IS_TRUE(_mocker->_expected);
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(ExpectAndThrow_ExpectedTrue_Throws)
   {
      _mocker->_expected = true;
      THROWS(_mocker->ExpectAndThrow<exception>(), FunctionAlreadyExpectedException,
         FunctionAlreadyExpectedException::MakeWhat(_signature));
   }

   TEST(ExpectAndThrow_ExpectedFalse_CallsExceptionThrowerExpectAndThrow_SetsExpectedTrue)
   {
      IS_FALSE(_mocker->_expected);
      _mocker->_exceptionThrower.ExpectCallToExpectAndThrow();
      //
      _mocker->ExpectAndThrow<TestingException>("argument", 100);
      //
      _mocker->_exceptionThrower.
         AssertExpectAndThrowCalledOnceWith("ZenMock::TestingException", 2, "argument100");
      IS_TRUE(_mocker->_expected);
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(ZenMockIt_ExpectedFalse_Throws)
   {
      IS_FALSE(_mocker->_expected);
      THROWS(_mocker->ZenMockIt(0), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(_signature, 0));
   }

   TEST(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   {
      _mocker->_expected = true;
      _mocker->_exceptionThrower.ExpectCallToZenMockThrowIfExceptionSet();
      IS_EMPTY(_mocker->callHistory);
      //
      _mocker->ZenMockIt(1);
      //
      using CallType = OneArgumentCall<int>;
      const vector<CallType> expectedCalls
      {
         CallType(1)
      };
      VECTORS_EQUAL(expectedCalls, _mocker->callHistory);
      ZEN(_mocker->_exceptionThrower.AssertZenMockThrowIfExceptionSetCalledOnce());
      NOTHROWS(_mocker->AssertCalledOnceWith(1));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST5X5(AssertCalledOnceWith_SetsAssertedTrue_FunctionWasCalledOnceWithExpectedArg_DoesNotThrow,
      size_t numberOfCalls, int expectedArgument, int actualArg, bool expectCallCountThrow, bool expectArgEqualityThrow,
      size_t(0), NA<int>(), NA<int>(), true, false,
      size_t(2), NA<int>(), NA<int>(), true, false,
      size_t(1), 1, 0, false, true,
      size_t(1), 0, 0, false, false,
      size_t(1), 1, 1, false, false)
   {
      IS_FALSE(_mocker->_asserted);
      _mocker->callHistory.resize(numberOfCalls);
      if (numberOfCalls == 1)
      {
         _mocker->callHistory = { OneArgumentCall<int>(actualArg) };
      }
      //
      if (expectCallCountThrow)
      {
         THROWS(_mocker->AssertCalledOnceWith(expectedArgument), Anomaly, R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature)
Expected: 1
  Actual: )" + to_string(numberOfCalls) + R"(
 Message: ")" + _signature + R"("
File.cpp(1))");
      }
      else
      {
         if (expectArgEqualityThrow)
         {
            THROWS(_mocker->AssertCalledOnceWith(expectedArgument), Anomaly, R"(
  Failed: ARE_EQUAL(expectedArgument, callHistory[0].argument, this->ZenMockedFunctionSignature)
Expected: )" + to_string(expectedArgument) + R"(
  Actual: )" + to_string(actualArg) + R"(
 Message: ")" + _signature + R"("
File.cpp(1))");
         }
         else
         {
            _mocker->AssertCalledOnceWith(expectedArgument);
         }
      }
      //
      IS_TRUE(_mocker->_asserted);
   }

   TEST(AssertCalledNTimesWith_NIsZero_Throws)
   {
      THROWS(_mocker->AssertCalledNTimesWith(0, 0), UnsupportedAssertCalledZeroTimesException,
         UnsupportedAssertCalledZeroTimesException::MakeWhat(_signature));
   }

   TEST3X3(AssertCalledNTimesWith_SetsAssertedTrue_NDiffersFromActualCallCount_Throws,
      size_t expectedNumberOfCalls, size_t numberOfCalls, bool expectThrow,
      size_t(1), size_t(0), true,
      size_t(1), size_t(1), false,
      size_t(1), size_t(2), true,
      size_t(2), size_t(0), true,
      size_t(2), size_t(1), true,
      size_t(2), size_t(2), false,
      size_t(2), size_t(3), true)
   {
      IS_FALSE(_mocker->_asserted);
      _mocker->callHistory.resize(numberOfCalls);
      //
      if (expectThrow)
      {
         const string expectedWhat = String::Concat(R"(
  Failed: ARE_EQUAL(expectedNumberOfCalls, callHistory.size(), this->ZenMockedFunctionSignature)
Expected: )", expectedNumberOfCalls, R"(
  Actual: )", numberOfCalls, R"(
 Message: ")", _signature, R"("
File.cpp(1))");
         THROWS(_mocker->AssertCalledNTimesWith(expectedNumberOfCalls, 0), Anomaly, expectedWhat);
      }
      else
      {
         _mocker->AssertCalledNTimesWith(expectedNumberOfCalls, 0);
      }
      //
      IS_TRUE(_mocker->_asserted);
   }

   TEST5X5(AssertCalledNTimesWith_SetsAssertedTrue_NEqualToNumberOfCalls_ThrowsIfArgsDoNotMatch,
      size_t expectedNumberOfCalls, int expectedArgument, const vector<OneArgumentCall<int>>& actualArgs,
      bool expectThrow, size_t expectedResponsibleCallIndex,
      size_t(1), 0, vector<OneArgumentCall<int>>{0}, false, NA<size_t>(),
      size_t(1), 0, vector<OneArgumentCall<int>>{1}, true, size_t(0),
      size_t(1), 1, vector<OneArgumentCall<int>>{2}, true, size_t(0),
      size_t(2), 1, vector<OneArgumentCall<int>>{1 Comma 1}, false, NA<size_t>(),
      size_t(2), 1, vector<OneArgumentCall<int>>{2 Comma 1}, true, size_t(0),
      size_t(2), 1, vector<OneArgumentCall<int>>{1 Comma 2}, true, size_t(1))
   {
      IS_FALSE(_mocker->_asserted);
      //
      _mocker->callHistory = actualArgs;
      if (expectThrow)
      {
         int actualArg = actualArgs[expectedResponsibleCallIndex].argument;
         string expectedSignatureAndCallIndex =
            _signature + " at i=" + to_string(expectedResponsibleCallIndex);
         THROWS(_mocker->AssertCalledNTimesWith(expectedNumberOfCalls, expectedArgument), Anomaly, R"(
  Failed: ARE_EQUAL(expectedArgument, callHistory[i].argument, zenMockedFunctionSignatureAndCallIndex)
Expected: )" + to_string(expectedArgument) + R"(
  Actual: )" + to_string(actualArg) + R"(
 Message: ")" + expectedSignatureAndCallIndex + R"("
File.cpp(1))");
      }
      else
      {
         _mocker->AssertCalledNTimesWith(expectedNumberOfCalls, expectedArgument);
      }
      //
      IS_TRUE(_mocker->_asserted);
   }

   TEST(AssertCalls_ExpectedCallsSize0_Throws_DoesNotSetAssertedTrue)
   {
      IS_FALSE(_mocker->_asserted);
      THROWS(_mocker->AssertCalls({}), UnsupportedAssertCalledZeroTimesException,
         UnsupportedAssertCalledZeroTimesException::MakeWhat(_signature));
      IS_FALSE(_mocker->_asserted);
   }

   TEST(AssertCalls_SetsAssertedTrue_ExpectedCallsSizeNon0AndNotEqualToActualCallsSize_Throws_DoesNotCopyTheExpectedArg)
   {
      IS_FALSE(_mocker->_asserted);
      const vector<OneArgumentCallRef<int>> expectedOneArgumentCalls { 0 };
      //
      THROWS(_mocker->AssertCalls(expectedOneArgumentCalls), Anomaly, R"(
  Failed: VECTORS_EQUAL(expectedOneArgumentCalls, actualOneArgumentCalls, this->ZenMockedFunctionSignature)
Expected: vector<T>
  Actual: vector<T>
 Because: ARE_EQUAL(expectedVector.size(), actualVector.size()) failed
Expected: 1
  Actual: 0
 Message: ")" + _signature + R"("
File.cpp(1)
File.cpp(1))");
      //
      IS_TRUE(_mocker->_asserted);
   }

   TEST(AssertCalls_SetsAssertedTrue_ExpectedCallsSizeNon0AndEqualToNumberOfCalls_ArgsNotEqual_Throws_DoesNotCopyTheExpectedArg)
   {
      IS_FALSE(_mocker->_asserted);
      const int x = 10, y = 10;
      const vector<OneArgumentCallRef<int>> expectedOneArgumentCalls { x, y };
      _mocker->callHistory = { 10, 20 };
      //
      THROWS(_mocker->AssertCalls(expectedOneArgumentCalls), Anomaly, R"(
  Failed: VECTORS_EQUAL(expectedOneArgumentCalls, actualOneArgumentCalls, this->ZenMockedFunctionSignature)
Expected: vector<T>
  Actual: vector<T>
 Because: ARE_EQUAL(ithExpectedElement, ithActualElement, iEqualsIndexMessage) failed
Expected: ZenMock::OneArgumentCall:
Argument: 10
  Actual: ZenMock::OneArgumentCall:
Argument: 20
 Message: "i=1"
 Message: ")" + _signature + R"("
File.cpp(1)
File.cpp(1))");
      //
      IS_TRUE(_mocker->_asserted);
   }

   TEST(AssertCalls_SetsAssertedTrue_ExpectedCallsSizeNon0AndEqualToNumberOfCalls_ArgsEqual_DoesNotThrow_DoesNotCopyTheExpectedArg)
   {
      IS_FALSE(_mocker->_asserted);
      int firstArgument = 10;
      int secondArgument = 10;
      const vector<OneArgumentCallRef<int>> expectedOneArgumentCalls
      {
         firstArgument, secondArgument
      };
      _mocker->callHistory = { 10, 10 };
      //
      _mocker->AssertCalls(expectedOneArgumentCalls);
      //
      IS_TRUE(_mocker->_asserted);
   }

   }; RUNTESTS(OneArgumentMockerTests)
}
