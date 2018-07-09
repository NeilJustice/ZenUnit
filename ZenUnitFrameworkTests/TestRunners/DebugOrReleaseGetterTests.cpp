#include "pch.h"

namespace ZenUnit
{
   TESTS(DebugOrReleaseGetterTests)
   AFACT(GetDebugOrRelease_ReturnsDebugInIf_DEBUGDefined_OtherwiseReturnsRelease)
   EVIDENCE

   TEST(GetDebugOrRelease_ReturnsDebugInIf_DEBUGDefined_OtherwiseReturnsRelease)
   {
      DebugOrReleaseGetter debugOrReleaseGetter;
      const string debugOrRelease = debugOrReleaseGetter.GetDebugOrRelease();
#ifdef NDEBUG
      ARE_EQUAL("Release", debugOrRelease);
#else
      ARE_EQUAL("Debug", debugOrRelease);
#endif
   }

   RUN_TESTS(DebugOrReleaseGetterTests)
}
