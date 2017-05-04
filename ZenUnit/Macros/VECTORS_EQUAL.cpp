#include "pch.h"
#include "ZenUnit/Macros/VECTORS_EQUAL.h"

namespace ZenUnit
{
   size_t ULongLongToChars(unsigned long long value, char* outChars)
   {
	   char* ptrA = outChars;
	   unsigned long long tempValue = 0;
	   size_t numberOfCharsAppended = 0;
	   do
	   {
		   tempValue = value;
		   value /= 10;
		   size_t index = 35 + (tempValue - value * 10);
		   *ptrA++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[index];
		   ++numberOfCharsAppended;
	   } while (value != 0);
	   char valueBeforeOverwrittenWithZero = *ptrA;
	   char* pointerToZero = ptrA;
	   *ptrA-- = '\0';
      char* ptrB = outChars;
	   while (ptrB < ptrA)
	   {
         char tempChar = *ptrA;
		   *ptrA-- = *ptrB;
		   *ptrB++ = tempChar;
	   }
	   *pointerToZero = valueBeforeOverwrittenWithZero;
	   return numberOfCharsAppended;
   }
}