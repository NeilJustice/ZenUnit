#pragma once
#include "ZenUnit/Console/Console.h"
#include "ZenUnit/Tests/Test.h"

namespace ZenUnit
{
   template<typename TestClassType, size_t N, typename... TestCaseArgTypes>
   class TestNXN : public Test
   {
      friend class TestNXNTests;
   private:
      static const size_t NumberOfTestCaseArgs = sizeof...(TestCaseArgTypes);
      static const size_t NumberOfTestCasesValue = NumberOfTestCaseArgs / N;
      std::unique_ptr<const Console> _console;
      std::unique_ptr<TestClassType> _testClass;
      size_t _testCaseArgsIndex;
      std::vector<std::string> _commaSplitTestCaseArgs;
   protected:
      const std::tuple<typename std::decay<TestCaseArgTypes>::type...> _testCaseArgs;
   public:
      TestNXN(
         const char* testClassName,
         const char* testName,
         const char* testCaseArgsText,
         TestCaseArgTypes&&... testCaseArgs)
         : Test(testClassName, testName, N)
         , _console(new Console)
         , _testCaseArgsIndex(0)
         , _commaSplitTestCaseArgs(String::CommaSplitExceptQuotedCommas(testCaseArgsText))
         , _testCaseArgs(std::forward<TestCaseArgTypes>(testCaseArgs)...)
      {
      }

      size_t NumberOfTestCases() const override
      {
         return NumberOfTestCasesValue;
      }

      void NewTestClass() override
      {
         _testClass = std::make_unique<TestClassType>();
      }

      void Startup() override
      {
         _testClass->Startup();
      }

      void TestBody() override
      {
         RunNXNTestCase(_testClass.get(), _testCaseArgsIndex);
      }
      
      virtual void RunNXNTestCase(TestClassType*, size_t) 
      { 
      }

      std::vector<TestResult> Run() override
      {
         std::vector<TestResult> testResults;
         const size_t numberOfTestCases = NumberOfTestCases();
         testResults.reserve(numberOfTestCases);
         assert_true(_testCaseArgsIndex == 0);
         for (unsigned short testCaseIndex = 0;
              _testCaseArgsIndex < NumberOfTestCaseArgs;
              _testCaseArgsIndex += N, ++testCaseIndex)
         {
            PrintTestCaseNumberArgsThenArrow(testCaseIndex);
            TestResult testResult = MockableCallBaseRunTestCase();
            testResult.testCaseIndex = testCaseIndex;
            testResults.push_back(testResult);
            PrintOKIfTestPassed(testResult);
         }
         _testCaseArgsIndex = 0;
         return testResults;
      }

      void Cleanup() override
      {
         _testClass->Cleanup();
      }

      void DeleteTestClass() override
      {
         _testClass.reset();
      }
   private:
      virtual TestResult MockableCallBaseRunTestCase()
      {
         const TestResult testResult = RunTestCase();
         return testResult;
      }

      virtual void PrintTestCaseNumberArgsThenArrow(unsigned short testCaseIndex) const
      {
         assert_true(testCaseIndex >= 0);
         _console->WriteColor(" [", Color::Green);
         const std::string testCaseNumber = std::to_string(testCaseIndex + 1);
         _console->Write(testCaseNumber);
         _console->WriteColor("]", Color::Green);
         _console->Write(" (");
         const size_t testCaseArgsPrintingStartIndex = static_cast<size_t>(testCaseIndex) * N;
         _console->PrintStringsCommaSeparated(_commaSplitTestCaseArgs, testCaseArgsPrintingStartIndex, N);
         _console->Write(") -> ");
      }

      virtual void PrintOKIfTestPassed(const TestResult& testResult) const
      {
         testResult.PrintOKIfTestPassed(_console.get());
      }
   };
}
