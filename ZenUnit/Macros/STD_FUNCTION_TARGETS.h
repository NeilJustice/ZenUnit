#pragma once
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/Macros/IS_NOT_NULL.h"
#include "ZenUnit/Macros/IS_TRUE.h"

#define STD_FUNCTION_TARGETS(expectedStdFunctionTarget, stdFunction, ...) \
   ZenUnit::STD_FUNCTION_TARGETS_Defined<decltype(expectedStdFunctionTarget)>( \
      expectedStdFunctionTarget, #expectedStdFunctionTarget, VRT(stdFunction), \
      FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename ExpectedStdFunctionTargetType, typename StdFunctionType, typename... MessageTypes>
   void STD_FUNCTION_TARGETS_Defined(
      const ExpectedStdFunctionTargetType* expectedStdFunctionTargetValue,
      const char* expectedStdFunctionTargetText,
      VRText<StdFunctionType> stdFunctionVRT,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const StdFunctionType stdFunction = stdFunctionVRT.value;
      try
      {
         IS_TRUE(stdFunction);
         IS_NOT_NULL(stdFunction.template target<ExpectedStdFunctionTargetType*>());
         typename std::add_pointer<ExpectedStdFunctionTargetType>::type
            expectedStdFunctionTarget(expectedStdFunctionTargetValue);
         ARE_EQUAL(expectedStdFunctionTarget, *stdFunction.template target<ExpectedStdFunctionTargetType*>());
      }
      catch (const Anomaly& becauseAnomaly)
      {
         const std::string expectedField = ToStringer::ToString(expectedStdFunctionTargetValue);
         const std::string actualField = ToStringer::ToString(stdFunctionVRT.value);
         throw Anomaly("STD_FUNCTION_TARGETS", expectedStdFunctionTargetText, stdFunctionVRT.text, "", messagesText,
            becauseAnomaly,
            expectedField,
            actualField,
            ExpectedActualFormat::Fields, fileLine, std::forward<MessageTypes>(messages)...);
      }
   }
}