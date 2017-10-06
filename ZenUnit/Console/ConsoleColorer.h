#pragma once

namespace ZenUnit
{
   enum class Color : unsigned char;

   class ConsoleColorer
   {
      friend class ConsoleColorerTests;
   private:
      std::function<int(FILE*)> call_fileno;
      std::function<int(int)> call_isatty;
#ifdef _WIN32
      std::function<HANDLE(DWORD)> call_GetStdHandle;
      std::function<BOOL(HANDLE, WORD)> call_SetConsoleTextAttribute;
#endif
      bool _supportsColor;
      bool _supportsColorSet;
   public:
      ConsoleColorer();
      virtual ~ConsoleColorer() = default;
      virtual bool SetColor(Color color);
      virtual void UnsetColor(bool didPreviouslySetTextColor) const;
   private:
      virtual void SetSupportsColorIfUnset();
      virtual bool SupportsColor() const;
      virtual void SetTextColor(Color color) const;
   };
}
