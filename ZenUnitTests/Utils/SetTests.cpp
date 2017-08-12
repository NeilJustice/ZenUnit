#include "pch.h"
#include "ZenUnit/Utils/Set.h"

namespace ZenUnit
{
   template<
      template<typename...>
      class SetType, typename T>
   TEMPLATETESTS(SetTests, SetType, T)
   FACT(Contains_ReturnsTrueIfSetContainsElement)
   BEGINPROOF

   TEST(Contains_ReturnsTrueIfSetContainsElement)
   {
      SetType<T> s;
      const T element10 = 10;
      const T element20 = 20;

      IS_FALSE(Set::Contains(s, element10));
      IS_FALSE(Set::Contains(s, element20));

      s.insert(element10);
      IS_TRUE(Set::Contains(s, element10));
      IS_FALSE(Set::Contains(s, element20));

      s.insert(element20);
      IS_TRUE(Set::Contains(s, element10));
      IS_TRUE(Set::Contains(s, element20));
   }

   };
   RUNTEMPLATE(SetTests, set, int)
   RUNTEMPLATE(SetTests, set, unsigned long long)
   RUNTEMPLATE(SetTests, unordered_set, int)
   RUNTEMPLATE(SetTests, unordered_set, unsigned long long)
}
