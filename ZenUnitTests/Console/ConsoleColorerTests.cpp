#include "pch.h"
#include "ZenUnit/Console/ConsoleColorer.h"
#ifdef __linux__
#include <unistd.h>
#elif _WIN32
#include <io.h>
#include "ZenUnit/Enums/WindowsColor.h"
// fileno() and isatty() are Linux and Windows wheras _fileno() and _isatty() are Windows only
#pragma warning(disable: 4996) // 'fileno': The POSIX name for this item is deprecated
#endif

namespace ZenUnit
{
   TESTS(ConsoleColorerTests)
   SPEC(Constructor_SetsFunctionPointers_SetsSupportsColorAndSupportsColorSetToFalse)
   SPECX(SetSupportsColorIfUnset)
   SPECX(SetColor_CallsSupportsColorAndSetTextColorIfColorNotWhite)
   SPECX(UnsetColor_CallsSetTextColorWhiteIfDidSetTextColorTrue)
   SPECX(SupportsColor_ReturnsTrueIfStdoutIsATTY)
#ifdef _WIN32
   SPECX(SetTextColor_WIN32_CallsWin32ApiToSetColorTextColor)
#endif
   SPECEND

   struct ConsoleColorer_SupportsColorMocked : public Zen::Mock<ConsoleColorer>
   {
      ZENMOCK_NONVOID0_CONST(bool, SupportsColor)
   };

   struct ConsoleColorer_SetCallsMocked : public Zen::Mock<ConsoleColorer>
   {
      ZENMOCK_VOID0(SetSupportsColorIfUnset)
      ZENMOCK_VOID1_CONST(SetTextColor, Color)
   };

   ConsoleColorer _consoleColorer;
   ConsoleColorer_SupportsColorMocked _consoleColorer_SupportsColorMocked;
   ConsoleColorer_SetCallsMocked _consoleColorer_SetCallsMocked;

   TEST(Constructor_SetsFunctionPointers_SetsSupportsColorAndSupportsColorSetToFalse)
   {
      const ConsoleColorer consoleColorer;
      FUNCTION_TARGETS(::fileno, consoleColorer.fileno_ZenMockable);
      FUNCTION_TARGETS(::isatty, consoleColorer.isatty_ZenMockable);
#ifdef _WIN32
      FUNCTION_TARGETS(::GetStdHandle, consoleColorer.GetStdHandle_ZenMockable);
      FUNCTION_TARGETS(::SetConsoleTextAttribute, consoleColorer.SetConsoleTextAttribute_ZenMockable);
#endif
      IS_FALSE(consoleColorer._supportsColor);
      IS_FALSE(consoleColorer._supportsColorSet);
   }

   TEST2X2(SetSupportsColorIfUnset,
      bool supportsColorSet, bool expectSetOfSupportsColor,
      false, true,
      true, false)
   {
      _consoleColorer_SupportsColorMocked._supportsColorSet = supportsColorSet;
      if (expectSetOfSupportsColor)
      {
         _consoleColorer_SupportsColorMocked.SupportsColorMock.Expect();
      }
      //
      _consoleColorer_SupportsColorMocked.SetSupportsColorIfUnset();
      //
      if (expectSetOfSupportsColor)
      {
         ZEN(_consoleColorer_SupportsColorMocked.SupportsColorMock.AssertCalledOnce());
      }
      IS_TRUE(_consoleColorer_SupportsColorMocked._supportsColorSet);
   }

   TEST3X3(SetColor_CallsSupportsColorAndSetTextColorIfColorNotWhite,
      Color color, 
      bool supportsColor,
      bool expectSetTextColorCallAndExpectedReturnValue,
      Color::White, false, false,
      Color::White, true, false,
      Color::Green, false, false,
      Color::Green, true, true,
      Color::Red, false, false,
      Color::Red, true, true)
   {
      _consoleColorer_SetCallsMocked._supportsColor = supportsColor;
      _consoleColorer_SetCallsMocked.SetSupportsColorIfUnsetMock.Expect();
      if (expectSetTextColorCallAndExpectedReturnValue)
      {
         _consoleColorer_SetCallsMocked.SetTextColorMock.Expect();
      }
      //
      bool didSetColor = _consoleColorer_SetCallsMocked.SetColor(color);
      //
      ZEN(_consoleColorer_SetCallsMocked.SetSupportsColorIfUnsetMock.AssertCalledOnce());
      if (expectSetTextColorCallAndExpectedReturnValue)
      {
         ZEN(_consoleColorer_SetCallsMocked.SetTextColorMock.AssertCalledOnceWith(color));
      }
      ARE_EQUAL(expectSetTextColorCallAndExpectedReturnValue, didSetColor);
   }

   TEST2X2(UnsetColor_CallsSetTextColorWhiteIfDidSetTextColorTrue,
      bool didSetTextColor, bool expectSetTextColorWhite,
      false, false,
      true, true)
   {
      if (expectSetTextColorWhite)
      {
         _consoleColorer_SetCallsMocked.SetTextColorMock.Expect();
      }
      //
      _consoleColorer_SetCallsMocked.UnsetColor(didSetTextColor);
      //
      if (expectSetTextColorWhite)
      {
         _consoleColorer_SetCallsMocked.SetTextColorMock.AssertCalledOnceWith(Color::White);
      }
   }

   TEST2X2(SupportsColor_ReturnsTrueIfStdoutIsATTY,
      int isattyReturnValue, bool expectedReturnValue,
      -1, true,
      0, false,
      1, true)
   {
      ZENMOCK_NONVOID1_FREE(int, fileno, FILE*);
      ZENMOCK_NONVOID1_FREE(int, isatty, int);
      const int StdoutFileHandle = 1;
      fileno_ZenMock.ExpectAndReturn(StdoutFileHandle);
      isatty_ZenMock.ExpectAndReturn(isattyReturnValue);
      _consoleColorer.fileno_ZenMockable = ZENBIND1(fileno_ZenMock);
      _consoleColorer.isatty_ZenMockable = ZENBIND1(isatty_ZenMock);
      //
      const bool consoleSupportsColor = _consoleColorer.SupportsColor();
      //
      ZEN(fileno_ZenMock.AssertCalledOnceWith(stdout));
      ZEN(isatty_ZenMock.AssertCalledOnceWith(StdoutFileHandle));
      ARE_EQUAL(expectedReturnValue, consoleSupportsColor);
   }

#ifdef _WIN32
   TEST2X2(SetTextColor_WIN32_CallsWin32ApiToSetColorTextColor,
      Color color, WindowsColor expectedWindowsColor,
      Color::White, WindowsColor::White,
      Color::Green, WindowsColor::Green,
      Color::Red, WindowsColor::Red)
   {
      ZENMOCK_NONVOID1_FREE(HANDLE, GetStdHandle, DWORD);
      ZENMOCK_NONVOID2_FREE(BOOL, SetConsoleTextAttribute, HANDLE, WORD);
      _consoleColorer.GetStdHandle_ZenMockable = ZENBIND1(GetStdHandle_ZenMock);
      _consoleColorer.SetConsoleTextAttribute_ZenMockable = ZENBIND2(SetConsoleTextAttribute_ZenMock);

      const HANDLE GetStdHandleReturnValue = HANDLE(1);
      GetStdHandle_ZenMock.ExpectAndReturn(GetStdHandleReturnValue);

      SetConsoleTextAttribute_ZenMock.ExpectAndReturn(TRUE);
      //
      _consoleColorer.SetTextColor(color);
      //
      GetStdHandle_ZenMock.AssertCalledOnceWith(STD_OUTPUT_HANDLE);
      SetConsoleTextAttribute_ZenMock.AssertCalledOnceWith(
         GetStdHandleReturnValue, static_cast<WORD>(expectedWindowsColor));
   }
#endif

   }; RUN(ConsoleColorerTests)
}
