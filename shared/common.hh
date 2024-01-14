#ifndef _COMMON_H
#define _COMMON_H 1

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <optional>
#include <string>
#include <vector>

#include <fmt/core.h>

constexpr auto TF_DEV = "TG-FOCUS";
constexpr auto TF_VER = "1.5";
constexpr auto TF_COLL_CHAT_TITLE = "TG-FOCUS";
constexpr auto TDLIB_VER = "1.8.23";
constexpr auto TDLIB_SRC = "d963044eb9b8bb075e3f63b8bfd8da735c4c37d9";

class FileReader
{
public:
  bool has_error{false};

  FileReader () = delete;

  FileReader (const char *filename)
  {
    auto open_mode = "r";
    auto filestream = fopen (filename, open_mode);
    if (filestream != nullptr)
      {
	fseek (filestream, 0L, SEEK_END);
	size_t fsize = ftell (filestream);

	if (fsize > this->MAX_SMALL)
	  this->large_rbuf
	    = reinterpret_cast<char *> (malloc (this->MAX_LARGE));

	this->fstrm_ = filestream;
      }
    else
      {
	this->has_error = true;
      }
  }

  ~FileReader ()
  {
    if (this->fstrm_ != nullptr)
      fclose (this->fstrm_);
    if (this->large_rbuf != nullptr)
      free (this->large_rbuf);
  }

  std::optional<std::string> read_to_string ()
  {
    if (this->large_rbuf == nullptr)
      return this->read_small_to_string ();
    else
      return this->read_large_to_string ();
  }

private:
  static constexpr size_t MAX_SMALL{4096};
  static constexpr size_t MAX_LARGE{1 << 20};
  FILE *fstrm_{nullptr};
  char *large_rbuf{nullptr};

  std::optional<std::string> read_small_to_string ()
  {
    fseek (this->fstrm_, 0L, SEEK_SET);

    char rbuf[this->MAX_SMALL];
    auto nread = fread (rbuf, 1, this->MAX_SMALL, this->fstrm_);

    if (ferror (this->fstrm_) != 0 || feof (this->fstrm_) == 0)
      return std::nullopt;

    return std::string{rbuf, nread};
  }

  std::optional<std::string> read_large_to_string ()
  {
    fseek (this->fstrm_, 0L, SEEK_SET);
    auto nread = fread (this->large_rbuf, 1, this->MAX_LARGE, this->fstrm_);

    if (ferror (this->fstrm_) != 0 || feof (this->fstrm_) == 0)
      return std::nullopt;

    return std::string{this->large_rbuf, nread};
  }
};

// trim from start (in place)
static inline void
ltrim (std::string &s)
{
  s.erase (s.begin (),
	   std::find_if (s.begin (), s.end (),
			 [] (unsigned char ch) { return !std::isspace (ch); }));
}

// trim from end (in place)
static inline void
rtrim (std::string &s)
{
  s.erase (std::find_if (s.rbegin (), s.rend (),
			 [] (unsigned char ch) { return !std::isspace (ch); })
	     .base (),
	   s.end ());
}

// trim from both ends (in place)
static inline void
trim (std::string &s)
{
  rtrim (s);
  ltrim (s);
}

inline bool
is_valid_int32 (const std::string &in)
{
  long as_num = std::strtol (in.c_str (), nullptr, 10);

  if (as_num < INT_MIN || as_num > INT_MAX)
    return false;
  if (fmt::format ("{}", as_num) != in)
    return false;

  return true;
}

inline int32_t
sstr_to_int32 (const std::string &in)
{
  return static_cast<int32_t> (strtol (in.c_str (), nullptr, 10));
}

inline bool
ensure_locale_utf8 ()
{
  using namespace std;

  vector<string> lclist = {
    "C.UTF-8",	    "aa_DJ.UTF-8",  "af_ZA.UTF-8", "an_ES.UTF-8",
    "ar_AE.UTF-8",  "ar_BH.UTF-8",  "ar_DZ.UTF-8", "ar_EG.UTF-8",
    "ar_IQ.UTF-8",  "ar_JO.UTF-8",  "ar_KW.UTF-8", "ar_LB.UTF-8",
    "ar_LY.UTF-8",  "ar_MA.UTF-8",  "ar_OM.UTF-8", "ar_QA.UTF-8",
    "ar_SA.UTF-8",  "ar_SD.UTF-8",  "ar_SY.UTF-8", "ar_TN.UTF-8",
    "ar_YE.UTF-8",  "ast_ES.UTF-8", "be_BY.UTF-8", "bg_BG.UTF-8",
    "bhb_IN.UTF-8", "br_FR.UTF-8",  "bs_BA.UTF-8", "ca_AD.UTF-8",
    "ca_ES.UTF-8",  "ca_FR.UTF-8",  "ca_IT.UTF-8", "cs_CZ.UTF-8",
    "cy_GB.UTF-8",  "da_DK.UTF-8",  "de_AT.UTF-8", "de_BE.UTF-8",
    "de_CH.UTF-8",  "de_DE.UTF-8",  "de_IT.UTF-8", "de_LI.UTF-8",
    "de_LU.UTF-8",  "el_CY.UTF-8",  "el_GR.UTF-8", "en_AU.UTF-8",
    "en_BW.UTF-8",  "en_CA.UTF-8",  "en_DK.UTF-8", "en_GB.UTF-8",
    "en_HK.UTF-8",  "en_IE.UTF-8",  "en_NZ.UTF-8", "en_PH.UTF-8",
    "en_SC.UTF-8",  "en_SG.UTF-8",  "en_US.UTF-8", "en_ZA.UTF-8",
    "en_ZW.UTF-8",  "es_AR.UTF-8",  "es_BO.UTF-8", "es_CL.UTF-8",
    "es_CO.UTF-8",  "es_CR.UTF-8",  "es_DO.UTF-8", "es_EC.UTF-8",
    "es_ES.UTF-8",  "es_GT.UTF-8",  "es_HN.UTF-8", "es_MX.UTF-8",
    "es_NI.UTF-8",  "es_PA.UTF-8",  "es_PE.UTF-8", "es_PR.UTF-8",
    "es_PY.UTF-8",  "es_SV.UTF-8",  "es_US.UTF-8", "es_UY.UTF-8",
    "es_VE.UTF-8",  "et_EE.UTF-8",  "eu_ES.UTF-8", "eu_FR.UTF-8",
    "fi_FI.UTF-8",  "fo_FO.UTF-8",  "fr_BE.UTF-8", "fr_CA.UTF-8",
    "fr_CH.UTF-8",  "fr_FR.UTF-8",  "fr_LU.UTF-8", "ga_IE.UTF-8",
    "gd_GB.UTF-8",  "gl_ES.UTF-8",  "gv_GB.UTF-8", "he_IL.UTF-8",
    "hr_HR.UTF-8",  "hsb_DE.UTF-8", "hu_HU.UTF-8", "id_ID.UTF-8",
    "is_IS.UTF-8",  "it_CH.UTF-8",  "it_IT.UTF-8", "ja_JP.UTF-8",
    "ka_GE.UTF-8",  "kk_KZ.UTF-8",  "kl_GL.UTF-8", "ko_KR.UTF-8",
    "ku_TR.UTF-8",  "kw_GB.UTF-8",  "lg_UG.UTF-8", "lt_LT.UTF-8",
    "lv_LV.UTF-8",  "mg_MG.UTF-8",  "mi_NZ.UTF-8", "mk_MK.UTF-8",
    "ms_MY.UTF-8",  "mt_MT.UTF-8",  "nb_NO.UTF-8", "nl_BE.UTF-8",
    "nl_NL.UTF-8",  "nn_NO.UTF-8",  "oc_FR.UTF-8", "om_KE.UTF-8",
    "pl_PL.UTF-8",  "pt_BR.UTF-8",  "pt_PT.UTF-8", "ro_RO.UTF-8",
    "ru_RU.UTF-8",  "ru_UA.UTF-8",  "sk_SK.UTF-8", "sl_SI.UTF-8",
    "so_DJ.UTF-8",  "so_KE.UTF-8",  "so_SO.UTF-8", "sq_AL.UTF-8",
    "st_ZA.UTF-8",  "sv_FI.UTF-8",  "sv_SE.UTF-8", "tcy_IN.UTF-8",
    "tg_TJ.UTF-8",  "th_TH.UTF-8",  "tl_PH.UTF-8", "tr_CY.UTF-8",
    "tr_TR.UTF-8",  "uk_UA.UTF-8",  "uz_UZ.UTF-8", "wa_BE.UTF-8",
    "xh_ZA.UTF-8",  "yi_US.UTF-8",  "zh_CN.UTF-8", "zh_HK.UTF-8",
    "zh_SG.UTF-8",  "zh_TW.UTF-8",  "zu_ZA.UTF-8", "en_HK.UTF-8",
  };

  for (const string &lc : lclist)
    if (setlocale (LC_ALL, lc.c_str ()) != nullptr)
      return true;

  return false;
}

#endif
