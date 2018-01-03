#include "pch.h"
#include "ZenUnitTests/Console/Mock/ConsoleMock.h"
#include "ZenUnitTests/Tests/Mock/TestMock.h"

class TestingTestClass_SpecSectionTestNXNTests
{
public:
   static bool didCallTestNXNPmfToTest;
   static unique_ptr<Test> TestNXNPmfToTestReturnValue;

   static const unique_ptr<Test>* TestNXNPmfToTest(const ZenUnit::PmfToken*)
   {
      didCallTestNXNPmfToTest = true;
      return &TestNXNPmfToTestReturnValue;
   }

   void TestFunction(int) {}
   virtual ~TestingTestClass_SpecSectionTestNXNTests() = default;
};

bool TestingTestClass_SpecSectionTestNXNTests::didCallTestNXNPmfToTest;
unique_ptr<Test> TestingTestClass_SpecSectionTestNXNTests::TestNXNPmfToTestReturnValue;

namespace ZenUnit
{
   TESTS(SpecSectionTestNXNTests)
   AFACT(ThreeArgConstructor_SetsTestName_SetsTestNXNPmf)
   FACTS(NumberOfTestCases_GetsTestFromAddress_ReturnsTestNumberOfTestCases)
   FACTS(NonMinimalWritePostTestNameMessage_WritesEllipsisIfPrintModeNotMinimal)
   AFACT(Run_GetsTestFromAddress_RunsTest_ReturnsTestResults)
   AFACT(PmfTokenToTest_ReturnsTestClassTypeTestNXNPmfToTestReturnValue);
   AFACT(TestFunction_CodeCoverage)
   EVIDENCE

   class SpecSectionTestNXNSelfMocked : public Zen::Mock<SpecSectionTestNXN<TestingTestClass_SpecSectionTestNXNTests>>
   {
   public:
      SpecSectionTestNXNSelfMocked()
         : Zen::Mock<SpecSectionTestNXN<TestingTestClass_SpecSectionTestNXNTests>>("", "", nullptr)
      {
      }
      ZENMOCK_NONVOID0_CONST(const unique_ptr<Test>*, PmfTokenToTest)
   };

   unique_ptr<SpecSectionTestNXN<TestingTestClass_SpecSectionTestNXNTests>> _specSectionTestNXN;
   unique_ptr<SpecSectionTestNXNSelfMocked> _specSectionTestNXNSelfMocked;

   STARTUP
   {
      _specSectionTestNXN = make_unique<SpecSectionTestNXN<TestingTestClass_SpecSectionTestNXNTests>>("", "", nullptr);
      _specSectionTestNXNSelfMocked = make_unique<SpecSectionTestNXNSelfMocked>();
   }

   TEST(ThreeArgConstructor_SetsTestName_SetsTestNXNPmf)
   {
      const string TestClassName = Random<string>();
      const string TestName = Random<string>();
      //
      const SpecSectionTestNXN<TestingTestClass_SpecSectionTestNXNTests> specifiedTestNXN(
         TestClassName.c_str(), TestName.c_str(), PmfToken::Instantiate<decltype(
            &TestingTestClass_SpecSectionTestNXNTests::TestFunction),
            &TestingTestClass_SpecSectionTestNXNTests::TestFunction>());
      //
      ARE_EQUAL(TestName, specifiedTestNXN.Name());
      ARE_EQUAL("TESTS(" + TestClassName + ")\nTEST(" + TestName + ")", specifiedTestNXN.FullTestNameValue());
      ARE_EQUAL("(0)", specifiedTestNXN.FileLineString());
      const PmfToken* const expectedTestNXNPmfToken = ZenUnit::PmfToken::Instantiate<
         decltype(&TestingTestClass_SpecSectionTestNXNTests::TestFunction),
         &TestingTestClass_SpecSectionTestNXNTests::TestFunction>();
      ARE_EQUAL(expectedTestNXNPmfToken, specifiedTestNXN._testNXNPmfToken);
   }

   TEST1X1(NumberOfTestCases_GetsTestFromAddress_ReturnsTestNumberOfTestCases,
      size_t testNumberOfTestCases,
      size_t(1),
      size_t(2))
   {
      TestMock* testMock = new TestMock;
      testMock->NumberOfTestCasesMock.ExpectAndReturn(testNumberOfTestCases);
      const unique_ptr<Test> testMockUniquePtr(testMock);
      _specSectionTestNXNSelfMocked->PmfTokenToTestMock.ExpectAndReturn(&testMockUniquePtr);
      //
      const size_t numberOfTestCases = _specSectionTestNXNSelfMocked->NumberOfTestCases();
      //
      ZEN(_specSectionTestNXNSelfMocked->PmfTokenToTestMock.CalledOnce());
      ZEN(testMock->NumberOfTestCasesMock.CalledOnce());
      ARE_EQUAL(testNumberOfTestCases, numberOfTestCases);
   }

   TEST2X2(NonMinimalWritePostTestNameMessage_WritesEllipsisIfPrintModeNotMinimal,
      PrintMode printMode, bool expectWriteLineCall,
      PrintMode::Minimalist, false,
      PrintMode::Normal, true,
      PrintMode::Detailed, true)
   {
      ConsoleMock consoleMock;
      if (expectWriteLineCall)
      {
         consoleMock.WriteLineMock.Expect();
      }
      //
      _specSectionTestNXN->NonMinimalWritePostTestNameMessage(&consoleMock, printMode);
      //
      if (expectWriteLineCall)
      {
         ZEN(consoleMock.WriteLineMock.CalledOnceWith("..."));
      }
   }

   TEST(Run_GetsTestFromAddress_RunsTest_ReturnsTestResults)
   {
      TestMock* const testMock = new TestMock;
      const vector<TestResult> testTestResults { TestResult::TestingNonDefault() };
      testMock->RunMock.ExpectAndReturn(testTestResults);
      const unique_ptr<Test> testMockUniquePtr(testMock);
      _specSectionTestNXNSelfMocked->PmfTokenToTestMock.ExpectAndReturn(&testMockUniquePtr);
      //
      const vector<TestResult> testResults = _specSectionTestNXNSelfMocked->Run();
      //
      ZEN(_specSectionTestNXNSelfMocked->PmfTokenToTestMock.CalledOnce());
      ZEN(testMock->RunMock.CalledOnce());
      VECTORS_EQUAL(testTestResults, testResults);
   }

   TEST(PmfTokenToTest_ReturnsTestClassTypeTestNXNPmfToTestReturnValue)
   {
      TestingTestClass_SpecSectionTestNXNTests::didCallTestNXNPmfToTest = false;
      //
      const unique_ptr<Test>* testNXN = _specSectionTestNXN->PmfTokenToTest();
      //
      IS_TRUE(TestingTestClass_SpecSectionTestNXNTests::didCallTestNXNPmfToTest);
      ARE_EQUAL(testNXN, &TestingTestClass_SpecSectionTestNXNTests::TestNXNPmfToTestReturnValue);
   }

   TEST(TestFunction_CodeCoverage)
   {
      TestingTestClass_SpecSectionTestNXNTests t;
      t.TestFunction(0);
   }

   }; RUNTESTS(SpecSectionTestNXNTests)
}
