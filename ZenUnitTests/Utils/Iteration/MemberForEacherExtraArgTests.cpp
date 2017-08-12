#include "pch.h"
#include "ZenUnit/Utils/Iteration/MemberForEacherExtraArg.h"

namespace ZenUnit
{
   template<typename ElementType, typename ExtraArgType>
   TEMPLATETESTS(MemberForEacherExtraArgTests, ElementType, ExtraArgType)
   FACT(ForEach_EmptyIterable_DoesNotCallFunc)
   FACT(ForEach_OneItemIterable_CallsThisPointerBoundFuncOnce)
   FACT(ForEach_TwoItemIterable_CallsThisPointerBoundFuncTwice)
   FACT(RandomForEach_EmptyIterable_DoesNotCallFunc)
   FACT(RandomForEach_OneItemIterable_CallsThisPointerBoundFuncOnce)
   FACT(RandomForEach_TwoItemIterable_CallsThisPointerBoundFuncTwiceInRandomOrder)
   FACT(CodeCoverage_ClassTypeTwoArgFunction)
   BEGINPROOF

   class ClassType
   {
   public:
      virtual void TwoArgFunction(ElementType, ExtraArgType) const {}
      virtual ~ClassType() = default;
   };

   class ClassTypeMock : public Zen::Mock<ClassType>
   {
   public:
      vector<ElementType> vec;
      ZENMOCK_VOID2_CONST(TwoArgFunction, ElementType, ExtraArgType)
   };

   using MemberForEacherExtraArgType = MemberForEacherExtraArg<
      ElementType, ClassType, void (ClassType::*)(ElementType, ExtraArgType) const, ExtraArgType>;

   MemberForEacherExtraArgType _memberForEacherExtraArg;

   TEST(ForEach_EmptyIterable_DoesNotCallFunc)
   {
      const ClassTypeMock classInstance{};
      _memberForEacherExtraArg.ForEach(
         &classInstance.vec, &classInstance, &ClassType::TwoArgFunction, 0);
   }

   TEST(ForEach_OneItemIterable_CallsThisPointerBoundFuncOnce)
   {
      ClassTypeMock classInstance;
      classInstance.vec = { 1 };
      classInstance.TwoArgFunctionMock.Expect();
      //
      _memberForEacherExtraArg.ForEach(
         &classInstance.vec, &classInstance, &ClassType::TwoArgFunction, 10);
      //
      classInstance.TwoArgFunctionMock.AssertCalledOnceWith(1, 10);
   }

   TEST(ForEach_TwoItemIterable_CallsThisPointerBoundFuncTwice)
   {
      ClassTypeMock classInstance;
      classInstance.vec = { 1, 2 };
      classInstance.TwoArgFunctionMock.Expect();
      //
      _memberForEacherExtraArg.ForEach(
         &classInstance.vec, &classInstance, &ClassType::TwoArgFunction, 20);
      //
      classInstance.TwoArgFunctionMock.AssertCalls(
      {
         { 1, 20 },
         { 2, 20 }
      });
   }

   TEST(RandomForEach_EmptyIterable_DoesNotCallFunc)
   {
      ClassTypeMock classInstance{};
      _memberForEacherExtraArg.RandomForEach(
         &classInstance.vec, &classInstance, &ClassType::TwoArgFunction, 0, 0);
   }

   TEST(RandomForEach_OneItemIterable_CallsThisPointerBoundFuncOnce)
   {
      ClassTypeMock classInstance;
      classInstance.vec = { 1 };
      classInstance.TwoArgFunctionMock.Expect();
      //
      _memberForEacherExtraArg.RandomForEach(
         &classInstance.vec, &classInstance, &ClassType::TwoArgFunction, 10, 0);
      //
      classInstance.TwoArgFunctionMock.AssertCalledOnceWith(1, 10);
   }

   TEST(RandomForEach_TwoItemIterable_CallsThisPointerBoundFuncTwiceInRandomOrder)
   {
      ClassTypeMock classInstance;
      classInstance.vec = { 1, 2 };
      classInstance.TwoArgFunctionMock.Expect();
      //
      _memberForEacherExtraArg.RandomForEach(
         &classInstance.vec, &classInstance, &ClassType::TwoArgFunction, 20,
         static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count()));
      //
      try
      {
         classInstance.TwoArgFunctionMock.AssertCalls(
         {
            { 1, 20 },
            { 2, 20 }
         });
      }
      catch (const exception&)
      {
         classInstance.TwoArgFunctionMock.AssertCalls(
         {
            { 2, 20 },
            { 1, 20 }
         });
      }
   }

   TEST(CodeCoverage_ClassTypeTwoArgFunction)
   {
      ClassType classType;
      classType.TwoArgFunction(ElementType{}, ExtraArgType{});
   };

   };
   RUNTEMPLATE(MemberForEacherExtraArgTests, int, int)
   RUNTEMPLATE(MemberForEacherExtraArgTests, double, char)
}
