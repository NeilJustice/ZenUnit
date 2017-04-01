#pragma once
#include "ZenUnit/Anomaly/Anomaly.h"
#include "ZenUnit/Utils/FileLine.h"

#define IS_TRUE(value, ...) \
   ZenUnit::IS_TRUE_Defined(value, #value, \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename... MessageTypes>
   NOINLINE void IS_TRUE_Throw(
      const char* valueText, FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      throw Anomaly("IS_TRUE", valueText, "", "", messagesText,
         Anomaly::Default,
         "true",
         "false",
         ExpectedActualFormat::Fields, fileLine, messages...);
   }

   template<typename ConvertibleToBoolType, typename... MessageTypes>
   void IS_TRUE_Defined(
      const ConvertibleToBoolType& value, const char* valueText,
      FileLine fileLine, const char* messagesText, const MessageTypes&... messages)
   {
      if (!value)
      {
         IS_TRUE_Throw(valueText, fileLine, messagesText, messages...);
      }
   }
}
