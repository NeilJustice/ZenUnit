#pragma once
#include "ZenUnit/Args/ZenUnitArgs.h"
#include <memory>

namespace ZenUnit
{
   class Console;
   class PreamblePrinter;
   class ArgsParser;
   class TestClassRunner;
   class MultiTestClassRunner;
   class TestRunResult;
   class Stopwatch;
   template<typename> class TestClass;
   //template<typename> class Futurist;

   class TestRunner
   {
      friend class TestRunnerTests;
   private:
      std::unique_ptr<const Console> _console;
      std::unique_ptr<const PreamblePrinter> _preamblePrinter;
      std::unique_ptr<const ArgsParser> _argsParser;
      //std::unique_ptr<const Futurist<TestRunner>> _futurist;
      std::unique_ptr<Stopwatch> _testRunStopwatch;
      std::unique_ptr<MultiTestClassRunner> _multiTestClassRunner;
      std::unique_ptr<TestRunResult> _testRunResult;
      ZenUnitArgs _zenUnitArgs;
      bool _havePaused;
   public:
      TestRunner();
      virtual ~TestRunner();
      static TestRunner& Instance();
      static const ZenUnitArgs& GetArgs();
      std::nullptr_t AddTestClassRunner(TestClassRunner* testClassRunner);
      std::nullptr_t SkipTest(const char* testClassName, const char* testName, const char* reason);
      std::nullptr_t SkipTestClass(const char* skippedTestClassName, const char* reason);
      int ParseArgsRunTestClassesPrintResults(const std::vector<std::string>& commandLineArgs);
   private:
      virtual bool WaitForEnterKeyIfPauseModeAndHaveNotPaused(bool pauseMode, bool havePaused) const;
      virtual int RunTestClassesAndPrintResults(const ZenUnitArgs& zenUnitArgs);
      virtual void RunTestClasses();
      virtual void RunTestClassesWithWaitableRunnerThread(unsigned maxtTotalSeconds);
   };
}
