#include "tf_locale.hh"
#include "tf_msg.hh"
#include "common.hh"

std::string
make_timestamp_readable (uint32_t tstamp)
{
  time_t tt = static_cast<time_t> (tstamp);
  struct tm *bd_time = localtime (&tt);
  char buf[64];
  size_t nbytes = strftime (buf, sizeof (buf), "%Y-%m-%d %T %z %Z", bd_time);
  if (nbytes > 0)
    return std::string (buf, nbytes);
  return std::string ("unknown timestamp");
}

TgMsg::TgMsg (std::string &&chat_title, std::string &&sender,
	      std::string &&text_content, int32_t tstamp)
{
  this->title_ = std::move (chat_title);
  this->sender_ = std::move (sender);
  this->txt_ = std::move (text_content);
  this->tstamp_ = make_timestamp_readable (tstamp);
}

TgMsg::TgMsg (std::string &chat_title, std::string &sender,
	      std::string &text_content, int32_t tstamp)
{
  this->title_ = (chat_title);
  this->sender_ = (sender);
  this->txt_ = (text_content);
  this->tstamp_ = make_timestamp_readable (tstamp);
}

std::ostream &
operator<< (std::ostream &os, const TgMsg &msg)
{
  os << "Telegram Message-"
     << "<title," << msg.title_ << ">"
     << "<sender," << msg.sender_ << ">"
     << "<txt," << msg.txt_ << ">"
     << "<tstamp," << msg.tstamp_ << ">";
  return os;
}

bool
can_decor ()
{
  return ensure_locale_utf8 ();
}

std::string
decor_pos_to_str (const std::vector<std::tuple<int, int>> &pos)
{
  std::string ret;
  for (auto ele : pos)
    {
      ret += fmt::format ("<{},{}>,", std::get<0> (ele), std::get<1> (ele));
    }
  return ret;
}

namespace lang_en {
std::optional<size_t>
get_end_chat_seq (std::vector<char16_t> &cuseq, size_t begi)
{
  if (cuseq[begi] == 0x5b && begi + 7 < cuseq.size ())
    if (cuseq[begi + 1] == ' ' && cuseq[begi + 2] == 'C'
	&& cuseq[begi + 3] == 'H' && cuseq[begi + 4] == 'A'
	&& cuseq[begi + 5] == 'T' && cuseq[begi + 6] == ' '
	&& cuseq[begi + 7] == ']')
      return std::make_optional<size_t> (7);

  return {};
}

std::optional<size_t>
get_end_sender_seq (std::vector<char16_t> &cuseq, size_t begi)
{
  if (cuseq[begi] == 0x5b && begi + 9 < cuseq.size ())
    if (cuseq[begi + 1] == 0x20 && cuseq[begi + 2] == 0x53
	&& cuseq[begi + 3] == 0x45 && cuseq[begi + 4] == 0x4e
	&& cuseq[begi + 5] == 0x44 && cuseq[begi + 6] == 0x45
	&& cuseq[begi + 7] == 0x52 && cuseq[begi + 8] == 0x20
	&& cuseq[begi + 9] == 0x5d)
      return std::make_optional<size_t> (9);

  return {};
}

std::optional<size_t>
get_end_content_seq (std::vector<char16_t> &cuseq, size_t begi)
{
  if (cuseq[begi] == 0x5b && begi + 10 < cuseq.size ())
    if (cuseq[begi + 1] == 0x20 && cuseq[begi + 2] == 0x43
	&& cuseq[begi + 3] == 0x4f && cuseq[begi + 4] == 0x4e
	&& cuseq[begi + 5] == 0x54 && cuseq[begi + 6] == 0x45
	&& cuseq[begi + 7] == 0x4e && cuseq[begi + 8] == 0x54
	&& cuseq[begi + 9] == 0x20 && cuseq[begi + 10] == 0x5d)
      return std::make_optional<size_t> (10);

  return {};
}

std::optional<size_t>
get_end_date_seq (std::vector<char16_t> &cuseq, size_t begi)
{
  if (cuseq[begi] == 0x5b && begi + 7 < cuseq.size ())
    if (cuseq[begi + 1] == 0x20 && cuseq[begi + 2] == 0x44
	&& cuseq[begi + 3] == 0x41 && cuseq[begi + 4] == 0x54
	&& cuseq[begi + 5] == 0x45 && cuseq[begi + 6] == 0x20
	&& cuseq[begi + 7] == 0x5d)
      return std::make_optional<size_t> (7);

  return {};
}

std::optional<size_t>
get_end_id_seq (std::vector<char16_t> &cuseq, size_t begi)
{
  if (cuseq[begi] == 0x5b && begi + 5 < cuseq.size ())
    if (cuseq[begi + 1] == 0x20 && cuseq[begi + 2] == 0x49
	&& cuseq[begi + 3] == 0x44 && cuseq[begi + 4] == 0x20
	&& cuseq[begi + 5] == 0x5d)
      return std::make_optional<size_t> (5);

  return {};
}
} // namespace lang_en

std::optional<size_t>
get_end_chat_seq (std::vector<char16_t> &cuseq, size_t begi)
{
  switch (HOST_LANG)
    {
    case en_AU:
    case en_HK:
    case en_GB:
    case en_US:
    case ja_JP:
      return lang_en::get_end_chat_seq (cuseq, begi);
    default:
      return {};
    }
}

std::optional<size_t>
get_end_sender_seq (std::vector<char16_t> &cuseq, size_t begi)
{
  switch (HOST_LANG)
    {
    case en_AU:
    case en_HK:
    case en_GB:
    case en_US:
    case ja_JP:
      return lang_en::get_end_sender_seq (cuseq, begi);
    default:
      return {};
    }
}

std::optional<size_t>
get_end_content_seq (std::vector<char16_t> &cuseq, size_t begi)
{
  switch (HOST_LANG)
    {
    case en_AU:
    case en_HK:
    case en_GB:
    case en_US:
    case ja_JP:
      return lang_en::get_end_content_seq (cuseq, begi);
    default:
      return {};
    }
}

std::optional<size_t>
get_end_date_seq (std::vector<char16_t> &cuseq, size_t begi)
{
  switch (HOST_LANG)
    {
    case en_AU:
    case en_HK:
    case en_GB:
    case en_US:
    case ja_JP:
      return lang_en::get_end_date_seq (cuseq, begi);
    default:
      return {};
    }
}

std::optional<size_t>
get_end_id_seq (std::vector<char16_t> &cuseq, size_t begi)
{
  switch (HOST_LANG)
    {
    case en_AU:
    case en_HK:
    case en_GB:
    case en_US:
    case ja_JP:
      return lang_en::get_end_id_seq (cuseq, begi);
    default:
      return {};
    }
}

std::vector<std::tuple<int, int>>
get_decor_pos (const std::string &str)
{
  // if (!ensure_locale_utf8 ())
  // return std::vector<std::tuple<int, int>>{};

  std::vector<char16_t> cuseq{};
  std::mbstate_t state{};
  char16_t c16;

  const char *ptr = &str[0], *end = &str[0] + str.size ();

  while (size_t rc = mbrtoc16 (&c16, ptr, end - ptr + 1, &state))
    {
      if (rc == (size_t) -3)
	{
	  std::cout << "mbrtoc16 -3" << std::endl;
	  cuseq.push_back (c16);
	}
      else if (rc == (size_t) -2)
	{
	  std::cout << "mbrtoc16 -2" << std::endl;
	  return std::vector<std::tuple<int, int>>{};
	}
      else if (rc == (size_t) -1)
	{
	  std::cout << "mbrtoc16 -1" << std::endl;
	  return std::vector<std::tuple<int, int>>{};
	}
      else
	{
	  cuseq.push_back (c16);
	  ptr += rc;
	}
    }

  std::vector<std::tuple<int, int>> ret;
  for (size_t i = 0; i < cuseq.size (); i++)
    {
      if (auto endi = get_end_chat_seq (cuseq, i))
	{
	  ret.emplace_back (std::make_tuple (i, *endi + 1));
	}
      if (auto endi = get_end_sender_seq (cuseq, i))
	{
	  ret.emplace_back (std::make_tuple (i, *endi + 1));
	}
      if (auto endi = get_end_content_seq (cuseq, i))
	{
	  ret.emplace_back (std::make_tuple (i, *endi + 1));
	}
      if (auto endi = get_end_date_seq (cuseq, i))
	{
	  ret.emplace_back (std::make_tuple (i, *endi + 1));
	}
      if (auto endi = get_end_id_seq (cuseq, i))
	{
	  ret.emplace_back (std::make_tuple (i, *endi + 1));
	}
    }

  return ret;
}
