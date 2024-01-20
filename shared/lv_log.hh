#ifndef _LV_LOG_H
#define _LV_LOG_H

#include <iostream>
#include "fmt/core.h"

enum LogLv
{
  ERROR = 1,
  WARNING = 2,
  INFO = 3,
  DEBUG = 4,
};

std::ostream &
operator<< (std::ostream &os, LogLv lv);

extern LogLv g_log_lv;

template <class... Args>
void
lv_log (LogLv lv, fmt::format_string<Args...> fmt, Args &&...args);

template <class... Args>
void
log_flush (fmt::format_string<Args...> fmt, Args &&...args);

template <class... Args>
void
lv_log (LogLv lv, fmt::format_string<Args...> fmt, Args &&...args)
{
  if (g_log_lv >= lv)
    {
      constexpr std::string_view header{"[tf-focusd] "};
      std::cout << header << fmt::format (fmt, std::forward<Args> (args)...)
		<< std::endl;
    }
}

template <class... Args>
void
lvlog (LogLv lv, Args &&...args)
{
  if (g_log_lv >= lv)
    {
      std::cout << "[tgf ";
      std::cout << lv;
      std::cout << "] ";
      for (const auto arg : {args...})
	{
	  std::cout << arg;
	}
    }
  std::cout << std::endl;
  std::cout << std::flush;
}

template <class... Args>
void
log_flush (fmt::format_string<Args...> fmt, Args &&...args)
{
  constexpr std::string_view header{"[tf-focusd] "};
  std::cout << header << fmt::format (fmt, args...) << std::flush;
}

#endif
