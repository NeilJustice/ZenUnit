#pragma once
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/ToStringer/ToStringer.h"

namespace ZenMock
{
   template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
   struct ThreeArgCall
   {
      typename std::decay<Arg1Type>::type arg1;
      typename std::decay<Arg2Type>::type arg2;
      typename std::decay<Arg3Type>::type arg3;

      ThreeArgCall()
         : arg1()
         , arg2()
         , arg3()
      {
      }

      ThreeArgCall(const Arg1Type& arg1, const Arg2Type& arg2, const Arg3Type& arg3)
         : arg1(arg1)
         , arg2(arg2)
         , arg3(arg3)
      {
      }
   };
}

template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
struct ZenUnitEqualizer<ZenMock::ThreeArgCall<Arg1Type, Arg2Type, Arg3Type>>
{
   static void AssertEqual(
      const ZenMock::ThreeArgCall<Arg1Type, Arg2Type, Arg3Type>& expectedThreeArgCall,
      const ZenMock::ThreeArgCall<Arg1Type, Arg2Type, Arg3Type>& actualThreeArgCall)
   {
      ARE_EQUAL(expectedThreeArgCall.arg1, actualThreeArgCall.arg1);
      ARE_EQUAL(expectedThreeArgCall.arg2, actualThreeArgCall.arg2);
      ARE_EQUAL(expectedThreeArgCall.arg3, actualThreeArgCall.arg3);
   }
};
