#include "pch.h"
#include "ZenMockTests/Mock/ExceptionThrowerMock.h"

namespace ZenMock
{
   TESTS(TenArgumentMockerTests)
   AFACT(Constructor_SetsFields)
   AFACT(Throw_CallsExceptionThrowerThrow_SetsExpectedTrue)
   AFACT(ZenMockIt_ExpectedFalse_Throws)
   AFACT(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   EVIDENCE

   using MockerType = TenArgumentMocker<int, int, int, int, int, int, int, int, int, int, ExceptionThrowerMock>;
   unique_ptr<MockerType> _mocker;
   string _functionSignature;

   STARTUP
   {
      _functionSignature = ZenUnit::Random<string>();
      _mocker = make_unique<MockerType>(_functionSignature);
   }

   void SetAssertedTrueToNotFailDueToExpectedButNotAsserted()
   {
      _mocker->_asserted = true;
   }

   TEST(Constructor_SetsFields)
   {
      const MockerType mocker(_functionSignature);
      //
      ARE_EQUAL(_functionSignature, mocker.ZenMockedFunctionSignature);
      IS_FALSE(mocker._expected);
      IS_FALSE(mocker._asserted);
      IS_EMPTY(mocker.zenMockObjectCallHistory);
   }

   TEST(Throw_CallsExceptionThrowerThrow_SetsExpectedTrue)
   {
      IS_FALSE(_mocker->_expected);
      _mocker->_exceptionThrower.ExpectCallToExpectAndThrow();
      //
      _mocker->Throw<TestingException>("argument", 100);
      //
      _mocker->_exceptionThrower.
         AssertExpectAndThrowCalledOnceWith("ZenMock::TestingException", 2, "argument100");
      IS_TRUE(_mocker->_expected);
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   TEST(ZenMockIt_ExpectedFalse_Throws)
   {
      IS_FALSE(_mocker->_expected);
      THROWS(_mocker->ZenMockIt(1, 2, 3, 4, 5, 6, 7, 8, 9, 10), UnexpectedCallException,
         UnexpectedCallException::MakeWhat(_functionSignature, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
   }

   TEST(ZenMockIt_ExpectedTrue_IncrementsNumberOfCalls_CallsZenMockThrowIfExceptionSet)
   {
      _mocker->_expected = true;
      _mocker->_exceptionThrower.ExpectCallToZenMockThrowIfExceptionSet();
      IS_EMPTY(_mocker->zenMockObjectCallHistory);
      //
      _mocker->ZenMockIt(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
      //
      using CallType = TenArgumentCall<int, int, int, int, int, int, int, int, int, int>;
      const vector<CallType> expectedCalls
      {
         CallType(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
      };
      VECTORS_EQUAL(expectedCalls, _mocker->zenMockObjectCallHistory);
      ZENMOCK(_mocker->_exceptionThrower.AssertZenMockThrowIfExceptionSetCalledOnce());
      DOES_NOT_THROW(_mocker->CalledOnceWith(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
      SetAssertedTrueToNotFailDueToExpectedButNotAsserted();
   }

   RUN_TESTS(TenArgumentMockerTests)
}