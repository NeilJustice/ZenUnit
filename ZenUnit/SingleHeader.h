#pragma once

#include "Anomaly/Anomaly.h"
#include "Anomaly/Anomaly.cpp"
#include "Anomaly/EqualizerException.h"

#include "Args/ArgsParser.h"
#include "Args/ArgsParser.cpp"
#include "Args/ZenUnitArgs.h"
#include "Args/ZenUnitArgs.cpp"

#include "Console/Console.h"
#include "Console/Console.cpp"
#include "Console/ConsoleColorer.h"
#include "Console/ConsoleColorer.cpp"

#include "Enums/Color.h"
#include "Enums/ExpectedActualFormat.h"
#include "Enums/LinuxColor.h"
#include "Enums/LinuxColor.cpp"
#include "Enums/PrintMode.h"
#include "Enums/TestOutcome.h"
#include "Enums/TestPhase.h"
#include "Enums/WindowsColor.h"
#include "Enums/WindowsColor.cpp"

#include "Equalizers/MapEqualizer.h"
#include "Equalizers/VectorEqualizer.h"
#include "Equalizers/ZenUnitEqualizer.h"
#include "Equalizers/ZenUnitEqualizer.cpp"

#include "Macros/ARE_COPIES.h"
#include "Macros/ARE_EQUAL.h"
#include "Macros/ARE_NOT_SAME.h"
#include "Macros/ARE_SAME.h"
#include "Macros/ARRAY_WAS_NEWED.h"
#include "Macros/DOES_CONTAIN.h"
#include "Macros/EQUALIZER_THROWS.h"
#include "Macros/EQUALIZER_THROWS.cpp"
#include "Macros/FAIL.h"
#include "Macros/IS_EMPTY.h"
#include "Macros/IS_FALSE.h"
#include "Macros/IS_NOT_NULL.h"
#include "Macros/IS_NULL.h"
#include "Macros/IS_TRUE.h"
#include "Macros/IS_ZERO.h"
#include "Macros/MacroUtils.h"
#include "Macros/MAPS_EQUAL.h"
#include "Macros/MAPS_EQUAL.cpp"
#include "Macros/NOTHROWS.h"
#include "Macros/PAIRS_EQUAL.h"
#include "Macros/POINTEES_EQUAL.h"
#include "Macros/POINTEES_EQUAL.cpp"
#include "Macros/POINTER_WAS_NEWED.h"
#include "Macros/REGEX_MATCHES.h"
#include "Macros/SETS_EQUAL.h"
#include "Macros/STD_FUNCTION_TARGETS.h"
#include "Macros/TestClassMacros.h"
#include "Macros/THROWS.h"
#include "Macros/VECTORS_EQUAL.h"
#include "Macros/VECTORS_EQUAL.cpp"

#include "Results/AnomalyOrException.h"
#include "Results/AnomalyOrException.cpp"
#include "Results/CallResult.h"
#include "Results/CallResult.cpp"
#include "Results/TestClassResult.h"
#include "Results/TestClassResult.cpp"
#include "Results/TestFailureNumberer.h"
#include "Results/TestFailureNumberer.cpp"
#include "Results/TestPhaseSuffixer.h"
#include "Results/TestPhaseSuffixer.cpp"
#include "Results/TestResult.h"
#include "Results/TestResult.cpp"
#include "Results/TestResultFactory.h"
#include "Results/TestResultFactory.cpp"
#include "Results/TestRunResult.h"
#include "Results/TestRunResult.cpp"

#include "TestRunners/MachineNameGetter.h"
#include "TestRunners/MachineNameGetter.cpp"
#include "TestRunners/MultiTestClassRunner.h"
#include "TestRunners/MultiTestClassRunner.cpp"
#include "TestRunners/PreamblePrinter.h"
#include "TestRunners/PreamblePrinter.cpp"
#include "TestRunners/RunTests.h"
#include "TestRunners/RunTests.cpp"
#include "TestRunners/SpecificTestClassRunner.h"
#include "TestRunners/TestClassRunner.h"
#include "TestRunners/TestClassRunner.cpp"
#include "TestRunners/TestRunner.h"
#include "TestRunners/TestRunner.cpp"
#include "TestRunners/TryCatchCaller.h"
#include "TestRunners/TryCatchCaller.cpp"

#include "Tests/FullTestName.h"
#include "Tests/FullTestName.cpp"
#include "Tests/NewDeleteTest.h"
#include "Tests/NormalTest.h"
#include "Tests/SpecSectionTestNXN.h"
#include "Tests/Test.h"
#include "Tests/Test.cpp"
#include "Tests/Test1X1ThroughTest10X10.h"
#include "Tests/TestClass.h"
#include "Tests/TestNXN.h"

#include "ToStringer/SFINAE/has_ostream_left_shift.h"
#include "ToStringer/SFINAE/has_to_string.h"
#include "ToStringer/SFINAE/has_ZenUnitPrinter.h"
#include "ToStringer/ZenUnitPrinter/MapZenUnitPrinter.h"
#include "ToStringer/ZenUnitPrinter/SetZenUnitPrinter.h"
#include "ToStringer/ZenUnitPrinter/VectorZenUnitPrinter.h"
#include "ToStringer/is_quoted_when_printed.h"
#include "ToStringer/ToStringer.h"
#include "ToStringer/ToStringer.cpp"

#include "Utils/Concurrency/Futurist.h"
#include "Utils/Concurrency/VoidFuture.h"
#include "Utils/Concurrency/VoidFuture.cpp"
#include "Utils/Iteration/ForEacherExtraArg.h"
#include "Utils/Iteration/ForEacherTwoExtraArgs.h"
#include "Utils/Iteration/MemberForEacher.h"
#include "Utils/Iteration/MemberForEacherExtraArg.h"
#include "Utils/Iteration/Transformer.h"
#include "Utils/Time/Stopwatch.h"
#include "Utils/Time/Stopwatch.cpp"
#include "Utils/Time/Watch.h"
#include "Utils/Time/Watch.cpp"
#include "Utils/AssertTrue.h"
#include "Utils/AssertTrue.cpp"
#include "Utils/FileLine.h"
#include "Utils/FileLine.cpp"
#include "Utils/FileLiner.h"
#include "Utils/FileLiner.cpp"
#include "Utils/IgnoredMSVCWallWarnings.h"
#include "Utils/Map.h"
#include "Utils/NA.h"
#include "Utils/PmfToken.h"
#include "Utils/Random.h"
#include "Utils/Random.cpp"
#include "Utils/Set.h"
#include "Utils/Sorter.h"
#include "Utils/StringUtil.h"
#include "Utils/StringUtil.cpp"
#include "Utils/Tuple.h"
#include "Utils/Type.h"
#include "Utils/Type.cpp"
#include "Utils/Vector.h"
#include "Utils/Vector.cpp"
#include "Utils/VRText.h"

#include "ZenMock/0/ZENMOCK_NONVOID0.h"
#include "ZenMock/0/ZENMOCK_VOID0.h"
#include "ZenMock/0/ZeroArgumentMocker.h"

#include "ZenMock/1/OneArgumentCall.h"
#include "ZenMock/1/OneArgumentCallRef.h"
#include "ZenMock/1/OneArgumentMocker.h"
#include "ZenMock/1/ZENMOCK_NONVOID1.h"
#include "ZenMock/1/ZENMOCK_VOID1.h"

#include "ZenMock/2/TwoArgumentCall.h"
#include "ZenMock/2/TwoArgumentCallRef.h"
#include "ZenMock/2/TwoArgumentMocker.h"
#include "ZenMock/2/ZENMOCK_NONVOID2.h"
#include "ZenMock/2/ZENMOCK_VOID2.h"

#include "ZenMock/3/ThreeArgumentCall.h"
#include "ZenMock/3/ThreeArgumentCallRef.h"
#include "ZenMock/3/ThreeArgumentMocker.h"
#include "ZenMock/3/ZENMOCK_NONVOID3.h"
#include "ZenMock/3/ZENMOCK_VOID3.h"

#include "ZenMock/4/FourArgumentCall.h"
#include "ZenMock/4/FourArgumentCallRef.h"
#include "ZenMock/4/FourArgumentMocker.h"
#include "ZenMock/4/ZENMOCK_NONVOID4.h"
#include "ZenMock/4/ZENMOCK_VOID4.h"

#include "ZenMock/5/FiveArgumentCall.h"
#include "ZenMock/5/FiveArgumentCallRef.h"
#include "ZenMock/5/FiveArgumentMocker.h"
#include "ZenMock/5/ZENMOCK_NONVOID5.h"
#include "ZenMock/5/ZENMOCK_VOID5.h"

#include "ZenMock/6/SixArgumentCall.h"
#include "ZenMock/6/SixArgumentCallRef.h"
#include "ZenMock/6/SixArgumentMocker.h"
#include "ZenMock/6/ZENMOCK_NONVOID6.h"
#include "ZenMock/6/ZENMOCK_VOID6.h"

#include "ZenMock/7/SevenArgumentCall.h"
#include "ZenMock/7/SevenArgumentCallRef.h"
#include "ZenMock/7/SevenArgumentMocker.h"
#include "ZenMock/7/ZENMOCK_NONVOID7.h"
#include "ZenMock/7/ZENMOCK_VOID7.h"

#include "ZenMock/8/EightArgumentCall.h"
#include "ZenMock/8/EightArgumentCallRef.h"
#include "ZenMock/8/EightArgumentMocker.h"
#include "ZenMock/8/ZENMOCK_NONVOID8.h"
#include "ZenMock/8/ZENMOCK_VOID8.h"

#include "ZenMock/9/NineArgumentCall.h"
#include "ZenMock/9/NineArgumentCallRef.h"
#include "ZenMock/9/NineArgumentMocker.h"
#include "ZenMock/9/ZENMOCK_NONVOID9.h"
#include "ZenMock/9/ZENMOCK_VOID9.h"

#include "ZenMock/10/TenArgumentCall.h"
#include "ZenMock/10/TenArgumentCallRef.h"
#include "ZenMock/10/TenArgumentMocker.h"
#include "ZenMock/10/ZENMOCK_NONVOID10.h"
#include "ZenMock/10/ZENMOCK_VOID10.h"

#include "ZenMock/Exceptions/ExceptionThrower.h"
#include "ZenMock/Exceptions/FunctionAlreadyExpectedException.h"
#include "ZenMock/Exceptions/FunctionAlreadyExpectedException.cpp"
#include "ZenMock/Exceptions/ReturnValueMustBeSpecifiedException.h"
#include "ZenMock/Exceptions/ReturnValueMustBeSpecifiedException.cpp"
#include "ZenMock/Exceptions/TemplateThrowable.h"
#include "ZenMock/Exceptions/Throwable.h"
#include "ZenMock/Exceptions/UnexpectedCallException.h"
#include "ZenMock/Exceptions/UnsupportedAssertCalledZeroTimesException.h"
#include "ZenMock/Exceptions/UnsupportedAssertCalledZeroTimesException.cpp"
#include "ZenMock/Exceptions/ZenMockException.h"

#include "ZenMock/Mock.h"
#include "ZenMock/Signature.h"
#include "ZenMock/Signature.cpp"
#include "ZenMock/ValueReturner.h"
#include "ZenMock/ZEN.h"
#include "ZenMock/ZenMocker.h"
