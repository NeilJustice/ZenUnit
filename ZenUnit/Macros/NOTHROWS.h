#pragma once
#include "ZenUnit/Anomaly/Anomaly.h"
#include "ZenUnit/Utils/Type.h"

#define NOTHROWS(expression, ...) \
   NOTHROWS_Defined([&]{ expression; }, #expression, \
   FILELINE, VATEXT(__VA_ARGS__), ##__VA_ARGS__)

namespace ZenUnit
{
   template<typename... MessageTypes>
   NOINLINE void NOTHROWS_Throw(
      const std::exception& e,
      const char* expressionText,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      const std::string failedLinePrefix = String::Concat("  Failed: NOTHROWS(", expressionText);
      const std::string* const actualExceptionTypeName = Type::GetName(e);
      const std::string whyBody = String::Concat("Expected: No exception thrown\n",
         "  Actual: ", *actualExceptionTypeName, " thrown\n",
         "  what(): \"", e.what(), "\"");
      throw Anomaly(failedLinePrefix, whyBody, fileLine, " ", messagesText, std::forward<MessageTypes>(messages)...);
   }

   template<typename... MessageTypes>
   void NOTHROWS_Defined(
      const std::function<void()>& expression,
      const char* expressionText,
      FileLine fileLine, const char* messagesText, MessageTypes&&... messages)
   {
      try
      {
         expression();
      }
      catch (const std::exception& e)
      {
         NOTHROWS_Throw(e, expressionText, fileLine, messagesText, std::forward<MessageTypes>(messages)...);
      }
   }
}
