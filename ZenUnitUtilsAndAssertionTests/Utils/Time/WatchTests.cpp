#include "pch.h"

namespace ZenUnit
{
   template<>
   struct Equalizer<tm>
   {
      static void AssertEqual(const tm& expectedTm, const tm& actualTm)
      {
         ARE_EQUAL(expectedTm.tm_sec, actualTm.tm_sec);
         ARE_EQUAL(expectedTm.tm_min, actualTm.tm_min);
         ARE_EQUAL(expectedTm.tm_hour, actualTm.tm_hour);
         ARE_EQUAL(expectedTm.tm_mday, actualTm.tm_mday);
         ARE_EQUAL(expectedTm.tm_mon, actualTm.tm_mon);
         ARE_EQUAL(expectedTm.tm_year, actualTm.tm_year);
         ARE_EQUAL(expectedTm.tm_wday, actualTm.tm_wday);
         ARE_EQUAL(expectedTm.tm_yday, actualTm.tm_yday);
         ARE_EQUAL(expectedTm.tm_isdst, actualTm.tm_isdst);
      }
   };

   TESTS(WatchTests)
   FACTS(DateTimeNow_ReturnsLocalDateTimeNow)
   FACTS(MicrosecondsToTwoDecimalPlaceMillisecondsString_ReturnsMicrosecondsAsMillisecondsRoundedToThreePlaces)
   EVIDENCE

   struct WatchSelfMocked : public Zen::Mock<ZenUnit::Watch>
   {
      ZENMOCK_NONVOID0_CONST(tm, TMNow)
   };
   unique_ptr<WatchSelfMocked> _watchSelfMocked;

   STARTUP
   {
      _watchSelfMocked = make_unique<WatchSelfMocked>();
   }

   TEST2X2(DateTimeNow_ReturnsLocalDateTimeNow,
      tm tmNow, const char* expectedDateTimeNow,
      Tm(0, 1, 0, 0, 0, 0), "1900-01-01 00:00:00",
      Tm(1, 2, 1, 1, 1, 1), "1901-02-02 01:01:01",
      Tm(2, 3, 2, 11, 11, 11), "1902-03-03 11:11:11",
      Tm(11, 31, 99, 23, 59, 59), "1999-12-31 23:59:59",
      Tm(0, 1, 100, 0, 0, 0), "2000-01-01 00:00:00",
      Tm(1, 3, 101, 4, 5, 6), "2001-02-03 04:05:06")
   {
      _watchSelfMocked->TMNowMock.Return(tmNow);
      //
      const string dateTimeNow = _watchSelfMocked->DateTimeNow();
      //
      ZEN(_watchSelfMocked->TMNowMock.CalledOnce());
      ARE_EQUAL(expectedDateTimeNow, dateTimeNow);
   }

   static constexpr tm Tm(int tmMonth, int tmMonthDay, int tmYear, int tmHour, int tmMin, int tmSec)
   {
      tm tmNow{};
      tmNow.tm_sec = tmSec;
      tmNow.tm_min = tmMin;
      tmNow.tm_hour = tmHour;
      tmNow.tm_mday = tmMonthDay;
      tmNow.tm_mon = tmMonth;
      tmNow.tm_year = tmYear;
      tmNow.tm_wday = 0;
      tmNow.tm_yday = 0;
      tmNow.tm_isdst = 0;
      return tmNow;
   }

   TEST2X2(MicrosecondsToTwoDecimalPlaceMillisecondsString_ReturnsMicrosecondsAsMillisecondsRoundedToThreePlaces,
      unsigned microseconds, const char* expectedReturnValue,
      0, "(0.00ms)",
      1, "(0.00ms)",
      2, "(0.00ms)",
      10, "(0.01ms)",
      12, "(0.01ms)",
      100, "(0.10ms)",
      120, "(0.12ms)",
      123, "(0.12ms)",
      1000, "(1.00ms)",
      1234, "(1.23ms)",
      12345, "(12.35ms)",
      123456, "(123.46ms)",
      1234567, "(1234.57ms)",
      12345678, "(12345.68ms)",
      123456789, "(123456.79ms)",
      1234567890, "(1234567.89ms)")
   {
      const string twoDecimalPlaceMilliseconds =
         Watch::MicrosecondsToTwoDecimalPlaceMillisecondsString(microseconds);
      ARE_EQUAL(expectedReturnValue, twoDecimalPlaceMilliseconds);
   }

   RUN_TESTS(WatchTests)
}