#include "pch.h"
#include "ZenMock1Tester.h"

int NonVoid1(int) { return 0; }

namespace ZenMock
{
   int NonVoid1(int) { return 0; }

   struct NonVoid1StaticFunctions
   {
      static int NonVoid1(int) { return 0; }
      static int Static(int) { return 0; }
   };

   struct NonVoid1Functions
   {
      virtual int Virtual(int) { return 0; }
      virtual int VirtualConst(int) const { return 0; }
      int NonVirtual(int) { return 0; }
      int NonVirtualConst(int) const { return 0; }
      virtual ~NonVoid1Functions() = default;
   };

   struct NonVoid1FunctionsMock : public Zen::Mock<NonVoid1Functions>
   {
      ZENMOCK_NONVOID1(int, Virtual, int)
      ZENMOCK_NONVOID1_CONST(int, VirtualConst, int)
      ZENMOCK_NONVOID1_NONVIRTUAL(int, NonVirtual, int)
      ZENMOCK_NONVOID1_CONST_NONVIRTUAL(int, NonVirtualConst, int)
   };

   TESTS(ZenMock_NonVoid1Tests)
   // Expect Tests
   AFACT(MockedFunction_NotExpected_Throws)
   AFACT(MockedFunction_Expected_DoesNotThrow)
   AFACT(ExpectAndThrow_CalledTwice_Throws)
   AFACT(ExpectAndThrow_ThenFunction_ThrowsTheException)
   // Value Return Tests
   AFACT(ExpectAndReturn_CausesFunctionToReturnValueThereafter)
   AFACT(ExpectAndReturnValues_CausesFunctionToReturnValuesInSequenceThenLastValueThereafter)
   AFACT(ExpectAndReturnContainerValues_CausesFunctionToReturnValuesInSequenceThenLastValueThereafter)
   // Assertion Tests
   FACTS(AssertCalledOnceWith_ExpectedFunctionCalled0Or2OrMoreTimes_Throws)
   AFACT(AssertCalledOnceWith_ExpectedFunctionCalledOnceWithMistmatchingArg_Throws)
   AFACT(AssertCalledOnceWith_ExpectedFunctionCalledOnceWithMatchingArg_DoesNotThrow)
   AFACT(AssertCalledNTimesWith_N0_Throws)
   FACTS(AssertCalledNTimesWith_N1OrGreater_FunctionCalledNotNTimes_Throws)
   FACTS(AssertCalledNTimesWith_N1OrGreater_FunctionCalledNTimesWithOneOfTheCallsMismatching_Throws)
   FACTS(AssertCalledNTimesWith_N1OrGreater_FunctionCalledNTimesWithMatchingArg_DoesNotThrow)
   AFACT(AssertCalls_EmptyCalls_Throws)
   FACTS(AssertCalls_NonEmptyCalls_FunctionCalledNotCallsSizeTimes_Throws)
   FACTS(AssertCalls_NonEmptyCalls_FunctionCalledCallsSizeTimesWithOneOfTheCallsMismatching_Throws)
   FACTS(AssertCalls_NonEmptyCalls_FunctionCalledCallsSizeTimesWithMatchingArgs_DoesNotThrow)
   EVIDENCE

   const string VirtualSignature =
      "virtual int ZenMock::NonVoid1Functions::Virtual(int)";
   const string VirtualConstSignature =
      "virtual int ZenMock::NonVoid1Functions::VirtualConst(int) const";
   const string NonVirtualSignature =
      "int ZenMock::NonVoid1Functions::NonVirtual(int)";
   const string NonVirtualConstSignature =
      "int ZenMock::NonVoid1Functions::NonVirtualConst(int) const";
   const string FreeSignature =
      "int ::NonVoid1(int)";
   const string NamespaceSignature =
      "int ZenMock::NonVoid1(int)";
   const string StaticUniqueSignature =
      "int ZenMock::NonVoid1StaticFunctions::Static(int)";
   const string StaticNameClashSignature =
      "int ZenMock::NonVoid1StaticFunctions::NonVoid1(int)";

   NonVoid1FunctionsMock mock;
   ZENMOCK_NONVOID1_FREE(int, NonVoid1, int)
   ZENMOCK_NONVOID1_STATIC(int, ZenMock, NonVoid1, int, _namespace)
   ZENMOCK_NONVOID1_STATIC(int, ZenMock::NonVoid1StaticFunctions, NonVoid1, int, _static)
   ZENMOCK_NONVOID1_STATIC(int, ZenMock::NonVoid1StaticFunctions, Static, int)
   unique_ptr<ZenMock1Tester<
      NonVoid1FunctionsMock,
      decltype(NonVoid1_ZenMock),
      decltype(NonVoid1_ZenMock_namespace),
      decltype(Static_ZenMock),
      decltype(NonVoid1_ZenMock_static)>> _zenMock1Tester;

   STARTUP
   {
      _zenMock1Tester = make_unique<ZenMock1Tester<
         NonVoid1FunctionsMock,
         decltype(NonVoid1_ZenMock),
         decltype(NonVoid1_ZenMock_namespace),
         decltype(Static_ZenMock),
         decltype(NonVoid1_ZenMock_static)>>(
            mock,
            VirtualSignature,
            VirtualConstSignature,
            NonVirtualSignature,
            NonVirtualConstSignature,
            NonVoid1_ZenMock,
            FreeSignature,
            NonVoid1_ZenMock_namespace,
            NamespaceSignature,
            Static_ZenMock,
            StaticUniqueSignature,
            NonVoid1_ZenMock_static,
            StaticNameClashSignature);
   }

   // Expect Tests

   TEST(MockedFunction_NotExpected_Throws)
   {
      _zenMock1Tester->MockedFunction_NotExpected_Throws();
   }

   TEST(MockedFunction_Expected_DoesNotThrow)
   {
      _zenMock1Tester->MockedFunction_Expected_DoesNotThrow();
   }

   TEST(ExpectAndThrow_CalledTwice_Throws)
   {
      _zenMock1Tester->ExpectAndThrow_CalledTwice_Throws();
   }

   TEST(ExpectAndThrow_ThenFunction_ThrowsTheException)
   {
      _zenMock1Tester->ExpectAndThrow_ThenFunction_ThrowsTheException();
   }

   // Value Return Tests

   TEST(ExpectAndReturn_CausesFunctionToReturnValueThereafter)
   {
      const auto test = [&](auto& zenMockObject, auto zenMockedFunctionCall)
      {
         zenMockObject.ExpectAndReturn(1);
         ARE_EQUAL(1, zenMockedFunctionCall());
         ARE_EQUAL(1, zenMockedFunctionCall());
         zenMockObject.AssertCalledNTimesWith(2, 0);
      };
      test(mock.VirtualMock, [&]{ return mock.Virtual(0); });
      test(mock.VirtualConstMock, [&]{ return mock.VirtualConst(0); });
      test(mock.NonVirtualMock, [&]{ return mock.NonVirtual(0); });
      test(mock.NonVirtualConstMock, [&]{ return mock.NonVirtualConst(0); });

      test(NonVoid1_ZenMock, [&]{ return ZENMOCK_BIND1(NonVoid1_ZenMock)(0); });
      test(NonVoid1_ZenMock_namespace, [&]{ return ZENMOCK_BIND1(NonVoid1_ZenMock_namespace)(0); });
      test(NonVoid1_ZenMock_static, [&]{ return ZENMOCK_BIND1(NonVoid1_ZenMock_static)(0); });
      test(Static_ZenMock, [&]{ return ZENMOCK_BIND1(Static_ZenMock)(0); });
   }

   TEST(ExpectAndReturnValues_CausesFunctionToReturnValuesInSequenceThenLastValueThereafter)
   {
      const auto test = [&](auto& zenMockObject, auto zenMockedFunctionCall)
      {
         zenMockObject.ExpectAndReturnValues(1, 2);
         ARE_EQUAL(1, zenMockedFunctionCall());
         ARE_EQUAL(2, zenMockedFunctionCall());
         ARE_EQUAL(2, zenMockedFunctionCall());
         zenMockObject.AssertCalledNTimesWith(3, 0);
      };
      test(mock.VirtualMock, [&]{ return mock.Virtual(0); });
      test(mock.VirtualConstMock, [&]{ return mock.VirtualConst(0); });
      test(mock.NonVirtualMock, [&]{ return mock.NonVirtual(0); });
      test(mock.NonVirtualConstMock, [&]{ return mock.NonVirtualConst(0); });

      test(NonVoid1_ZenMock, [&]{ return ZENMOCK_BIND1(NonVoid1_ZenMock)(0); });
      test(NonVoid1_ZenMock_namespace, [&]{ return ZENMOCK_BIND1(NonVoid1_ZenMock_namespace)(0); });
      test(NonVoid1_ZenMock_static, [&]{ return ZENMOCK_BIND1(NonVoid1_ZenMock_static)(0); });
      test(Static_ZenMock, [&]{ return ZENMOCK_BIND1(Static_ZenMock)(0); });
   }

   TEST(ExpectAndReturnContainerValues_CausesFunctionToReturnValuesInSequenceThenLastValueThereafter)
   {
      const auto test = [&](auto& zenMockObject, auto zenMockedFunctionCall)
      {
         const vector<int> values { 1, 2 };
         zenMockObject.ExpectAndReturnValues(values);
         ARE_EQUAL(1, zenMockedFunctionCall());
         ARE_EQUAL(2, zenMockedFunctionCall());
         ARE_EQUAL(2, zenMockedFunctionCall());
         zenMockObject.AssertCalledNTimesWith(3, 0);
      };
      test(mock.VirtualMock, [&]{ return mock.Virtual(0); });
      test(mock.VirtualConstMock, [&]{ return mock.VirtualConst(0); });
      test(mock.NonVirtualMock, [&]{ return mock.NonVirtual(0); });
      test(mock.NonVirtualConstMock, [&]{ return mock.NonVirtualConst(0); });

      test(NonVoid1_ZenMock, [&]{ return ZENMOCK_BIND1(NonVoid1_ZenMock)(0); });
      test(NonVoid1_ZenMock_namespace, [&]{ return ZENMOCK_BIND1(NonVoid1_ZenMock_namespace)(0); });
      test(NonVoid1_ZenMock_static, [&]{ return ZENMOCK_BIND1(NonVoid1_ZenMock_static)(0); });
      test(Static_ZenMock, [&]{ return ZENMOCK_BIND1(Static_ZenMock)(0); });
   }

   // Assertion Tests

   TEST1X1(AssertCalledOnceWith_ExpectedFunctionCalled0Or2OrMoreTimes_Throws,
      size_t numberOfCalls,
      size_t(0),
      size_t(2),
      size_t(3))
   {
      _zenMock1Tester->AssertCalledOnceWith_ExpectedFunctionCalled0Or2OrMoreTimes_Throws(numberOfCalls);
   }

   TEST(AssertCalledOnceWith_ExpectedFunctionCalledOnceWithMistmatchingArg_Throws)
   {
      _zenMock1Tester->AssertCalledOnceWith_ExpectedFunctionCalledOnceWithMistmatchingArg_Throws();
   }

   TEST(AssertCalledOnceWith_ExpectedFunctionCalledOnceWithMatchingArg_DoesNotThrow)
   {
      _zenMock1Tester->AssertCalledOnceWith_ExpectedFunctionCalledOnceWithMatchingArg_DoesNotThrow();
   }

   TEST(AssertCalledNTimesWith_N0_Throws)
   {
      _zenMock1Tester->AssertCalledNTimesWith_N0_Throws();
   }

   TEST2X2(AssertCalledNTimesWith_N1OrGreater_FunctionCalledNotNTimes_Throws,
      size_t n, size_t numberOfCalls,
      size_t(1), size_t(0),
      size_t(1), size_t(2),
      size_t(2), size_t(0),
      size_t(2), size_t(1),
      size_t(2), size_t(3))
   {
      _zenMock1Tester->AssertCalledNTimesWith_N1OrGreater_FunctionCalledNotNTimes_Throws(n, numberOfCalls);
   }

   TEST2X2(AssertCalledNTimesWith_N1OrGreater_FunctionCalledNTimesWithOneOfTheCallsMismatching_Throws,
      size_t n, size_t mismatchingCallIndex,
      size_t(1), size_t(0),
      size_t(2), size_t(0),
      size_t(2), size_t(1))
   {
      _zenMock1Tester->AssertCalledNTimesWith_N1OrGreater_FunctionCalledNTimesWithOneOfTheCallsMismatching_Throws(
         n, mismatchingCallIndex);
   }

   TEST1X1(AssertCalledNTimesWith_N1OrGreater_FunctionCalledNTimesWithMatchingArg_DoesNotThrow,
      size_t n,
      size_t(1),
      size_t(2))
   {
      _zenMock1Tester->AssertCalledNTimesWith_N1OrGreater_FunctionCalledNTimesWithMatchingArg_DoesNotThrow(n);
   }

   TEST(AssertCalls_EmptyCalls_Throws)
   {
      _zenMock1Tester->AssertCalls_EmptyCalls_Throws();
   }

   TEST2X2(AssertCalls_NonEmptyCalls_FunctionCalledNotCallsSizeTimes_Throws,
      size_t expectedCallsSize, size_t numberOfCalls,
      size_t(1), size_t(0),
      size_t(1), size_t(2),
      size_t(2), size_t(0),
      size_t(2), size_t(1),
      size_t(2), size_t(3))
   {
      _zenMock1Tester->AssertCalls_NonEmptyCalls_FunctionCalledNotCallsSizeTimes_Throws(
         expectedCallsSize, numberOfCalls);
   }

   TEST2X2(AssertCalls_NonEmptyCalls_FunctionCalledCallsSizeTimesWithOneOfTheCallsMismatching_Throws,
      size_t expectedCallsSize, size_t mismatchingCallIndex,
      size_t(1), size_t(0),
      size_t(2), size_t(0),
      size_t(2), size_t(1))
   {
      _zenMock1Tester->AssertCalls_NonEmptyCalls_FunctionCalledCallsSizeTimesWithOneOfTheCallsMismatching_Throws(
         expectedCallsSize, mismatchingCallIndex);
   }

   TEST1X1(AssertCalls_NonEmptyCalls_FunctionCalledCallsSizeTimesWithMatchingArgs_DoesNotThrow,
      size_t expectedCallsSize,
      size_t(1),
      size_t(2))
   {
      _zenMock1Tester->AssertCalls_NonEmptyCalls_FunctionCalledCallsSizeTimesMatchingArgs_DoesNotThrow(expectedCallsSize);
   }

   }; RUNTESTS(ZenMock_NonVoid1Tests)
}
