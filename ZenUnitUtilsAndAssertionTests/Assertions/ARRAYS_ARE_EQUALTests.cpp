#include "pch.h"

namespace ZenUnit
{
   template<typename T>
   TEMPLATE_TESTS(ARRAYS_ARE_EQUALTests, T)
   AFACT(LengthToCompareIs0_DoesNotThrowException)
   AFACT(LengthToCompareIs1_FirstElementsAreEqual_DoesNotThrowException)
   AFACT(LengthToCompareIs1_FirstElementsAreNotEqual_ThrowsAnomaly)
   AFACT(LengthToCompareIs2_FirstElementsAreEqual_SecondElementsAreEqual_DoesNotThrowException)
   AFACT(LengthToCompareIs2_FirstElementsAreEqual_SecondElementsAreNotEqual_ThrowsAnomaly)
   EVIDENCE

   TEST(LengthToCompareIs0_DoesNotThrowException)
   {
      const T expectedArray[1] { ZenUnit::Random<T>() };
      const T actualArray[1] { ZenUnit::Random<T>() };
      //
      ARRAYS_ARE_EQUAL(expectedArray, actualArray, 0);
   }

   TEST(LengthToCompareIs1_FirstElementsAreEqual_DoesNotThrowException)
   {
      const T expectedArray[1] { ZenUnit::Random<T>() };
      const T actualArray[1] { expectedArray[0] };
      //
      ARRAYS_ARE_EQUAL(expectedArray, actualArray, 1);
   }

   TEST(LengthToCompareIs1_FirstElementsAreNotEqual_ThrowsAnomaly)
   {
      const string typeName = *Type::GetName<T>();
      const T randomElement = ZenUnit::Random<T>();
      const T expectedArray[1] { randomElement };
      const T actualArray[1] { randomElement + T{1} };
      //
      THROWS_EXCEPTION(ARRAYS_ARE_EQUAL(expectedArray, actualArray, 1), Anomaly, TestUtil::NewlineConcat("",
         "  Failed: ARRAYS_ARE_EQUAL(expectedArray, actualArray, 1)",
         "Expected: " + typeName + " [1]",
         "  Actual: " + typeName + " [1]",
         " Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
         "Expected: " + ToStringer::ToString(expectedArray[0]),
         "  Actual: " + ToStringer::ToString(actualArray[0]),
         " Message: \"i=0\"",
         "File.cpp(1)",
         "File.cpp(1)"));
   }

   TEST(LengthToCompareIs2_FirstElementsAreEqual_SecondElementsAreEqual_DoesNotThrowException)
   {
      const T expectedArray[2] { ZenUnit::Random<T>(), ZenUnit::Random<T>() };
      const T actualArray[2] { expectedArray[0], expectedArray[1] };
      //
      ARRAYS_ARE_EQUAL(expectedArray, actualArray, 2);
   }

   TEST(LengthToCompareIs2_FirstElementsAreEqual_SecondElementsAreNotEqual_ThrowsAnomaly)
   {
      const string typeName = *Type::GetName<T>();
      const T randomElement0 = ZenUnit::Random<T>();
      const T randomElement1 = ZenUnit::Random<T>();
      const T expectedArray[2] { randomElement0, randomElement1 };
      const T actualArray[2] { expectedArray[0], expectedArray[1] + 1 };
      //
      THROWS_EXCEPTION(ARRAYS_ARE_EQUAL(expectedArray, actualArray, 2), Anomaly, TestUtil::NewlineConcat("",
         "  Failed: ARRAYS_ARE_EQUAL(expectedArray, actualArray, 2)",
         "Expected: " + typeName + " [2]",
         "  Actual: " + typeName + " [2]",
         " Because: ARE_EQUAL(ithExpectedElement, ithActualElement, indexMessage) failed",
         "Expected: " + ToStringer::ToString(expectedArray[1]),
         "  Actual: " + ToStringer::ToString(actualArray[1]),
         " Message: \"i=1\"",
         "File.cpp(1)",
         "File.cpp(1)"));
   }

   RUN_TEMPLATE_TESTS(ARRAYS_ARE_EQUALTests, int)
   THEN_RUN_TEMPLATE_TESTS(ARRAYS_ARE_EQUALTests, unsigned)
   THEN_RUN_TEMPLATE_TESTS(ARRAYS_ARE_EQUALTests, unsigned long long)
}
