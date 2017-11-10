#ifdef __linux__
#include "ZenUnit/pch.h"
#elif defined(_WIN64)
#include "pch.h"
#endif
#include "ZenUnit/Macros/MAPS_EQUAL.h"

namespace ZenUnit
{
   INLINE std::string MAPS_EQUAL_MakeWhyBody_SizesNotEqual(
      size_t expectedMapSize, size_t actualMapSize)
   {
      const std::string whyBody = String::Concat(
         " Because: ARE_EQUAL(expectedMap.size(), actualMap.size()) failed\n",
         "Expected: ", expectedMapSize, '\n',
         "  Actual: ", actualMapSize);
      return whyBody;
   }
}