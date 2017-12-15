#include "pch.h"
#include "ZenUnitTests/Testing/UserType.h"

TESTS(UserTypeTests)
AFACT(DefaultConstructor_SetsValueTo0)
AFACT(OneArgConstructor_SetsValue)
AFACT(OperatorLessThan_ReturnsTrueIfLeftXLessThanRightX)
AFACT(OperatorEquals_ReturnsTrueIfLeftXEqualsRightX)
AFACT(ZenUnitPrint_WritesExpected_ReturnOStream)
AFACT(OperatorBool_ValueIs1_ReturnsTrue)
AFACT(OperatorBool_ValueIsNot1_ReturnsFalse)
AFACT(has_ostream_left_shift_False)
AFACT(has_ZenUnitPrinter_True)
EVIDENCE

TEST(DefaultConstructor_SetsValueTo0)
{
   const UserType userType;
   IS_ZERO(userType.value);
}

TEST(OneArgConstructor_SetsValue)
{
   const UserType userType(1);
   ARE_EQUAL(1, userType.value);
}

TEST(OperatorLessThan_ReturnsTrueIfLeftXLessThanRightX)
{
   const UserType userType1(1);
   const UserType userType2(2);
   IS_TRUE(userType1 < userType2);
   IS_FALSE(userType2 < userType1);
   IS_FALSE(userType1 < userType1);
}

TEST(OperatorEquals_ReturnsTrueIfLeftXEqualsRightX)
{
   const UserType userType1(1);
   const UserType userType2(2);
   IS_TRUE(userType1 == userType1);
   IS_FALSE(userType1 == userType2);
}

TEST(ZenUnitPrint_WritesExpected_ReturnOStream)
{
   const UserType userType1(1);
   const UserType userTypeNegative1(-1);
   ostringstream oss;
   //
   ZenUnit::Printer<UserType>::Print(oss, userType1);
   oss << " ";
   ZenUnit::Printer<UserType>::Print(oss, userTypeNegative1);
   //
   ARE_EQUAL("UserType@1 UserType@-1", oss.str());
}

TEST(OperatorBool_ValueIs1_ReturnsTrue)
{
   const UserType userType1(1);
   IS_TRUE(userType1);
   IS_TRUE(userType1);
}

TEST(OperatorBool_ValueIsNot1_ReturnsFalse)
{
   const UserType userTypeNegative1(-1);
   IS_FALSE(userTypeNegative1);
   IS_FALSE(userTypeNegative1);

   const UserType userType0(0);
   IS_FALSE(userType0);
   IS_FALSE(userType0);

   const UserType userType2(2);
   IS_FALSE(userType2);
   IS_FALSE(userType2);
}

TEST(has_ostream_left_shift_False)
{
   IS_FALSE(ZenUnit::has_ostream_left_shift<UserType>::value);
}

TEST(has_ZenUnitPrinter_True)
{
   IS_TRUE(ZenUnit::has_ZenUnitPrinter<UserType>::value);
}

}; RUNTESTS(UserTypeTests)
