#include "pch.h"
#include "ZenUnit/Results/CallResult.h"

namespace ZenUnit
{
   TESTS(CallResultTests)
   SPEC(DefaultConstructor_SetsFieldsTo0)
   SPEC(TestPhaseConstructor_SetsTestPhase_SetsOtherFieldsTo0)
   SPEC(Assign_CopiesCallResultToSelf)
   SPEC(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   SPECEND

   TEST(DefaultConstructor_SetsFieldsTo0)
   {
      const CallResult defaultCallResult;
      CallResult expectedDefaultCallResult;
      expectedDefaultCallResult.testPhase = TestPhase::Unset;
      expectedDefaultCallResult.testOutcome = TestOutcome::Success;
      expectedDefaultCallResult.milliseconds = 0;
      expectedDefaultCallResult.anomaly = nullptr;
      expectedDefaultCallResult.exceptionTypeName = nullptr;
      expectedDefaultCallResult.exceptionWhat = "";
      ARE_EQUAL(expectedDefaultCallResult, defaultCallResult);
   }

   TEST(TestPhaseConstructor_SetsTestPhase_SetsOtherFieldsTo0)
   {
      const CallResult callResult(TestPhase::Constructor);
      CallResult expectedCallResult;
      expectedCallResult.testPhase = TestPhase::Constructor;
      expectedCallResult.testOutcome = TestOutcome::Success;
      expectedCallResult.milliseconds = 0;
      expectedCallResult.anomaly = nullptr;
      expectedCallResult.exceptionTypeName = nullptr;
      expectedCallResult.exceptionWhat = "";
      ARE_EQUAL(expectedCallResult, callResult);
   }

   TEST(Assign_CopiesCallResultToSelf)
   {
      CallResult callResult;
      CallResult callResultArg;
      callResultArg.testPhase = TestPhase::Constructor;
      callResultArg.testOutcome = TestOutcome::Exception;
      callResultArg.milliseconds = 1;
      callResultArg.anomaly = make_shared<Anomaly>();
      string exceptionTypeName;
      callResultArg.exceptionTypeName = &exceptionTypeName;
      callResultArg.exceptionWhat = "excepWhat";
      ARE_EQUAL(1, callResultArg.anomaly.use_count());
      //
      callResult.Assign(callResultArg);
      //
      ARE_EQUAL(2, callResult.anomaly.use_count());
      ARE_EQUAL(2, callResultArg.anomaly.use_count());
      ARE_EQUAL(callResultArg, callResult);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      EQUALIZER_THROWS_INIT(CallResult);
      EQUALIZER_THROWS(CallResult, testPhase, TestPhase::Constructor);
      EQUALIZER_THROWS(CallResult, testOutcome, TestOutcome::Exception);
      shared_ptr<Anomaly> nonDefaultAnomaly = make_shared<Anomaly>();
      nonDefaultAnomaly->why = "why";
      EQUALIZER_THROWS(CallResult, anomaly, nonDefaultAnomaly);
      const string exceptionTypeName = "exceptionTypeName";
      EQUALIZER_THROWS(CallResult, exceptionTypeName, &exceptionTypeName);
      EQUALIZER_THROWS(CallResult, exceptionWhat, "exceptionWhat");
      EQUALIZER_THROWS(CallResult, milliseconds, 1u);
   }

   }; RUN(CallResultTests)
}
