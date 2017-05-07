#include "pch.h"
#include "ZenUnit/Macros/ARE_EQUAL.h"
#include "ZenUnit/Macros/POINTEES_EQUAL.h"
#include "ZenUnit/Results/AnomalyOrException.h"

namespace ZenUnit
{
   AnomalyOrException::AnomalyOrException(const Anomaly& anomaly)
      : anomaly(make_shared<Anomaly>(anomaly))
      , exceptionTypeName(nullptr)
   {
   }

   AnomalyOrException::AnomalyOrException(const std::string* exceptionTypeName, const char* exceptionWhat)
      : exceptionTypeName(exceptionTypeName)
      , exceptionWhat(make_shared<string>(exceptionWhat))
   {
   }
}

void ZenUnitEqualizer<ZenUnit::AnomalyOrException>::AssertEqual(
   const ZenUnit::AnomalyOrException& expectedAnomalyOrException,
   const ZenUnit::AnomalyOrException& actualAnomalyOrException)
{
   POINTEES_EQUAL(expectedAnomalyOrException.anomaly, actualAnomalyOrException.anomaly);
   ARE_EQUAL(expectedAnomalyOrException.exceptionTypeName, actualAnomalyOrException.exceptionTypeName);
   POINTEES_EQUAL(expectedAnomalyOrException.exceptionWhat, actualAnomalyOrException.exceptionWhat);
}
