#ifndef _TF_MSG_H
#define _TF_MSG_H

#include <stdint.h>
#include <string>

class TgMsg
{
public:
  TgMsg () = default;

  TgMsg (const std::string &chat_title, const std::string &sender,
	 const std::string &text_content, int32_t tstamp = 0);

  TgMsg (std::string &&chat_title, std::string &&sender,
	 std::string &&text_content, int32_t tstamp = 0);

  inline const std::string &get_chat_title () const { return this->title_; }

  inline bool is_from_tgfocus () const
  {
    return this->title_.find ("TG-FOCUS") != std::string::npos;
  }

  inline const std::string &get_sender () const { return this->sender_; }

  inline const std::string &get_text_content () const { return this->txt_; }

  inline const std::string &get_timestamp () const { return this->tstamp_; }

  friend std::ostream &operator<< (std::ostream &os, const TgMsg &msg);

private:
  std::string title_;
  std::string sender_;
  std::string txt_;
  std::string tstamp_;
};

#endif
