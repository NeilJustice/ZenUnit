#include "pch.h"
#include "ZenMockTests/1Arg/ZenMock1Tester.h"

void Void1Function(int) {}

namespace ZenMock
{
   struct Void1Functions
   {
      virtual void VirtualFunction(int) {}
      virtual void VirtualConstFunction(int) const {}
      void NonVirtualFunction(int) {}
      void NonVirtualConstFunction(int) const {}
      virtual ~Void1Functions() = default;
   };

   struct Void1FunctionsMock : public Zen::Mock<Void1Functions>
   {
      ZENMOCK_VOID1(VirtualFunction, int)
      ZENMOCK_VOID1_CONST(VirtualConstFunction, int)
      ZENMOCK_VOID1_NONVIRTUAL(NonVirtualFunction, int)
      ZENMOCK_VOID1_NONVIRTUAL_CONST(NonVirtualConstFunction, int)
   };

   void Void1Function(int) {}

   struct Void1StaticFunctions
   {
      static void StaticVoid1Function(int) {}
      static void OverloadedStaticVoid1Function(float) {}
      static void OverloadedStaticVoid1Function(double) {}
   };

   TESTS(ZenMockVoid1Tests_CodeCoverage)
   AFACT(CodeCoverage)
   EVIDENCE

   TEST(CodeCoverage)
   {
      ::Void1Function(0);
      ZenMock::Void1Function(0);

      ZenMock::Void1Functions void1Functions;
      void1Functions.VirtualFunction(0);
      void1Functions.VirtualConstFunction(0);
      void1Functions.NonVirtualFunction(0);
      void1Functions.NonVirtualConstFunction(0);

      ZenMock::Void1Function(0);

      ZenMock::Void1StaticFunctions::StaticVoid1Function(0);
      ZenMock::Void1StaticFunctions::OverloadedStaticVoid1Function(0.0f);
      ZenMock::Void1StaticFunctions::OverloadedStaticVoid1Function(0.0);
   }

   RUN_TESTS(ZenMockVoid1Tests_CodeCoverage)

   TESTS(ZenMockVoid1Tests)
   AFACT(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   EVIDENCE

   const string ExpectedVirtualFunctionSignature =
      "virtual void ZenMock::Void1Functions::VirtualFunction(int)";
   const string ExpectedVirtualConstFunctionSignature =
      "virtual void ZenMock::Void1Functions::VirtualConstFunction(int) const";
   const string ExpectedNonVirtualFunctionSignature =
      "void ZenMock::Void1Functions::NonVirtualFunction(int)";
   const string ExpectedNonVirtualConstFunctionSignature =
      "void ZenMock::Void1Functions::NonVirtualConstFunction(int) const";
   const string FreeFunctionSignature =
      "void ::Void1Function(int)";
   const string ExpectedNamespacedFunctionSignature =
      "void ZenMock::Void1Function(int)";
   const string StaticFunctionSignature =
      "void ZenMock::Void1StaticFunctions::StaticFunction(int)";
   const string ExpectedOverloadedStaticFunctionSignatureA =
      "void ZenMock::Void1StaticFunctions::OverloadedStaticFunction(float)";
   const string ExpectedOverloadedStaticFunctionSignatureB =
      "void ZenMock::Void1StaticFunctions::OverloadedStaticFunction(double)";

   Void1FunctionsMock _mock;
   ZENMOCK_VOID1_FREE(Void1Function, int)
   // ZENMOCK_VOID1_NAMESPACED_FREE
   ZENMOCK_VOID1_STATIC(ZenMock, Void1Function, int, _namespace)
   ZENMOCK_VOID1_STATIC(ZenMock::Void1StaticFunctions, StaticVoid1Function, int)
   ZENMOCK_VOID1_STATIC(ZenMock::Void1StaticFunctions, OverloadedStaticVoid1Function, float, _float)
   ZENMOCK_VOID1_STATIC(ZenMock::Void1StaticFunctions, OverloadedStaticVoid1Function, double, _double)

   unique_ptr<ZenMock1Tester<
      Void1FunctionsMock,
      decltype(Void1FunctionMock),
      decltype(Void1FunctionMock_namespace),
      decltype(StaticVoid1FunctionMock),
      decltype(OverloadedStaticVoid1FunctionMock_float)>> _zenMock1Tester;

   STARTUP
   {
      _zenMock1Tester = make_unique<ZenMock1Tester<
         Void1FunctionsMock,
         decltype(Void1FunctionMock),
         decltype(Void1FunctionMock_namespace),
         decltype(StaticVoid1FunctionMock),
         decltype(OverloadedStaticVoid1FunctionMock_float)>>(
         _mock,
         ExpectedVirtualFunctionSignature,
         ExpectedVirtualConstFunctionSignature,
         ExpectedNonVirtualFunctionSignature,
         ExpectedNonVirtualConstFunctionSignature,

         Void1FunctionMock,
         FreeFunctionSignature,

         Void1FunctionMock_namespace,
         ExpectedNamespacedFunctionSignature,

         StaticVoid1FunctionMock,
         StaticFunctionSignature,

         OverloadedStaticVoid1FunctionMock_float,
         ExpectedOverloadedStaticFunctionSignatureA);
   }

   TEST(Expect_MakesFunctionNotThrowWhenCalled_ExpectDoesNotThrowWhenCalledTwice)
   {
      const auto test = [](auto& zenMockObject)
      {
         zenMockObject.Expect();
         zenMockObject.ZenMockIt(0);
         zenMockObject.Expect();
         zenMockObject.CalledOnceWith(0);
      };
      test(_mock.VirtualFunctionMock);
      test(_mock.VirtualConstFunctionMock);
      test(_mock.NonVirtualFunctionMock);
      test(_mock.NonVirtualConstFunctionMock);

      test(Void1FunctionMock);
      test(Void1FunctionMock_namespace);
      test(StaticVoid1FunctionMock);
      test(OverloadedStaticVoid1FunctionMock_float);
   }

   RUN_TESTS(ZenMockVoid1Tests)
}
