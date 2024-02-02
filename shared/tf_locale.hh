#ifndef _TF_LOCALE_H
#define _TF_LOCALE_H

#include <iostream>
#include "stdint.h"

namespace tgf {

enum Lang : uint8_t
// enum Lang
{
  unknown = 0,
  aa_DJ,
  af_ZA,
  an_ES,
  ar_AE,
  ar_BH,
  ar_DZ,
  ar_EG,
  ar_IQ,
  ar_JO,
  ar_KW,
  ar_LB,
  ar_LY,
  ar_MA,
  ar_OM,
  ar_QA,
  ar_SA,
  ar_SD,
  ar_SY,
  ar_TN,
  ar_YE,
  ast_ES,
  be_BY,
  bg_BG,
  bhb_IN,
  br_FR,
  bs_BA,
  ca_AD,
  ca_ES,
  ca_FR,
  ca_IT,
  cs_CZ,
  cy_GB,
  da_DK,
  de_AT,
  de_BE,
  de_CH,
  de_DE,
  de_IT,
  de_LI,
  de_LU,
  el_CY,
  el_GR,
  en_AU,
  en_BW,
  en_CA,
  en_DK,
  en_GB,
  en_HK,
  en_IE,
  en_NZ,
  en_PH,
  en_SC,
  en_SG,
  en_US,
  en_ZA,
  en_ZW,
  es_AR,
  es_BO,
  es_CL,
  es_CO,
  es_CR,
  es_DO,
  es_EC,
  es_ES,
  es_GT,
  es_HN,
  es_MX,
  es_NI,
  es_PA,
  es_PE,
  es_PR,
  es_PY,
  es_SV,
  es_US,
  es_UY,
  es_VE,
  et_EE,
  eu_ES,
  eu_FR,
  fi_FI,
  fo_FO,
  fr_BE,
  fr_CA,
  fr_CH,
  fr_FR,
  fr_LU,
  ga_IE,
  gd_GB,
  gl_ES,
  gv_GB,
  he_IL,
  hr_HR,
  hsb_DE,
  hu_HU,
  id_ID,
  is_IS,
  it_CH,
  it_IT,
  ja_JP,
  ka_GE,
  kk_KZ,
  kl_GL,
  ko_KR,
  ku_TR,
  kw_GB,
  lg_UG,
  lt_LT,
  lv_LV,
  mg_MG,
  mi_NZ,
  mk_MK,
  ms_MY,
  mt_MT,
  nb_NO,
  nl_BE,
  nl_NL,
  nn_NO,
  oc_FR,
  om_KE,
  pl_PL,
  pt_BR,
  pt_PT,
  ro_RO,
  ru_RU,
  ru_UA,
  sk_SK,
  sl_SI,
  so_DJ,
  so_KE,
  so_SO,
  sq_AL,
  st_ZA,
  sv_FI,
  sv_SE,
  tcy_IN,
  tg_TJ,
  th_TH,
  tl_PH,
  tr_CY,
  tr_TR,
  uk_UA,
  uz_UZ,
  wa_BE,
  xh_ZA,
  yi_US,
  zh_CN,
  zh_HK,
  zh_SG,
  zh_TW,
  zu_ZA,
};

extern Lang
lang_from_cstr (const char *cstr);

const char *
lang_to_cstr (Lang l);

// process's locale setting.
extern enum Lang HOST_LANG;

// user's prefer locale setting.
extern enum Lang PREFER_LANG;

//
// Try to ensure there is any suitable locale (including language and character
// set) ,if so, return true, with one additional side effect is that process's
// locale and HOST_LANG will be initialized. If not, return false. Note that
// this exists for internationalization and decoration.
//
bool
try_ensure_locale ();

std::ostream &
operator<< (std::ostream &os, const Lang l);

} // namespace tgf

#endif
