#include "pch.h"

namespace ZenUnit
{
   TESTS(ZenUnitArgsTests)
   AFACT(DefaultConstructor_SetsFieldsToDefaults)
   AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   EVIDENCE

   TEST(DefaultConstructor_SetsFieldsToDefaults)
   {
      ZenUnitArgs zenUnitArgs;
      ARE_EQUAL("", zenUnitArgs.commandLine);
      ARE_EQUAL(PrintMode::Normal, zenUnitArgs.printMode);
      IS_FALSE(zenUnitArgs.exit0);
      IS_FALSE(zenUnitArgs.failskips);
      ARE_EQUAL(1, zenUnitArgs.testruns);
      IS_FALSE(zenUnitArgs.random);
      ARE_EQUAL(0, zenUnitArgs.randomseed);
      IS_FALSE(zenUnitArgs.randomseedsetbyuser);
      IS_ZERO(zenUnitArgs.maxtestmilliseconds);
      IS_ZERO(zenUnitArgs.maxtotalseconds);
   }

   TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
   {
      EQUALIZER_THROWS_INIT(ZenUnitArgs);
      EQUALIZER_THROWS(ZenUnitArgs, commandLine, "ZenUnitTests.exe");
      EQUALIZER_THROWS(ZenUnitArgs, printMode, PrintMode::Minimalist);
      EQUALIZER_THROWS(ZenUnitArgs, exit0, true);
      EQUALIZER_THROWS(ZenUnitArgs, failskips, true);
      EQUALIZER_THROWS(ZenUnitArgs, testruns, 2u);
      EQUALIZER_THROWS(ZenUnitArgs, random, true);
      EQUALIZER_THROWS(ZenUnitArgs, randomseed, static_cast<unsigned short>(3));
      EQUALIZER_THROWS(ZenUnitArgs, randomseedsetbyuser, true);
      EQUALIZER_THROWS(ZenUnitArgs, maxtestmilliseconds, 4u);
      EQUALIZER_THROWS(ZenUnitArgs, maxtotalseconds, 5u);
   }

   }; RUNTESTS(ZenUnitArgsTests)
}
