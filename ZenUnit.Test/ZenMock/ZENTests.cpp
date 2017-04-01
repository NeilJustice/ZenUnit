#include "pch.h"
#include "ZenUnit.Test/Console/Mock/ConsoleMock.h"
#include "ZenUnit/ZenMock/ZEN.h"

namespace ZenMock
{
   TESTS(ZENTests)
   SPEC(ZENWrappedAssertionDoesNotThrow_NothingHappens)
   SPEC(ZENWrappedAssertionThrows_RethrowsZENWrappedAnomaly)
   SPECEND

   TEST(ZENWrappedAssertionDoesNotThrow_NothingHappens)
   {
      ConsoleMock consoleMock;
      consoleMock.WriteLineMock.Expect();
      consoleMock.WriteLine("message");
      ZEN(consoleMock.WriteLineMock.AssertCalledOnceWith("message"));
   }

   TEST(ZENWrappedAssertionThrows_RethrowsZENWrappedAnomaly)
   {
      ConsoleMock consoleMock;
      consoleMock.WriteLineMock.Expect();
      consoleMock.WriteLine("message");
      string expectedMessage = "Message";
      THROWS(ZEN(consoleMock.WriteLineMock.AssertCalledOnceWith(expectedMessage)), Anomaly, R"(
  Failed: ZEN(consoleMock.WriteLineMock.AssertCalledOnceWith(expectedMessage))
 Because: ARE_EQUAL(expectedArg, _oneArgCalls[0].arg, this->ZenMockedFunctionSignature) failed
Expected: "Message"
  Actual: "message"
 Message: "virtual void ZenUnit::Console::WriteLine(const string&) const"
File.cpp(1))");
   }

   }; RUN(ZENTests)
}
