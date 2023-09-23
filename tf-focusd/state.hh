#ifndef _FOCUSD_STATE_H
#define _FOCUSD_STATE_H

#include <optional>
#include <vector>
#include <mutex>
#include <atomic>

#include "collector.hh"
#include "tf_data.hh"
#include "tf_msg.hh"

extern std::atomic<std::uint32_t> it_cnt_switcher;
extern std::atomic<std::uint32_t> it_cnt_producer;
extern std::atomic<std::uint32_t> it_cnt_consumer;

extern std::vector<TgMsg> mq;
extern std::mutex mq_lock;
extern std::atomic<bool> is_csm_mq;
extern std::atomic<bool> is_tdlib_auth;
extern std::atomic<bool> need_phone;
extern TdCollector collector;
extern TgFocusData tf_data;
extern std::atomic<int> producer_hang_period;

template <class... Args>
void
log (fmt::format_string<Args...> fmt, Args &&...args)
{
  constexpr std::string_view header{"[tf-focusd] "};
  std::cout << header << fmt::format (fmt, args...) << std::endl;
}

#endif // _TGFOCUS_STATE_H
