#include <tuple>
#include <string>
#include <vector>

#include "tf_locale.hh"

enum Lang HOST_LANG = unknown;

enum Lang PREFER_LANG = unknown;

std::ostream &
operator<< (std::ostream &os, const Lang l)
{
  switch (l)
    {
    case aa_DJ:
      os << "aa_DJ";
      break;
    case af_ZA:
      os << "af_ZA";
      break;
    case an_ES:
      os << "an_ES";
      break;
    case ar_AE:
      os << "ar_AE";
      break;
    case ar_BH:
      os << "ar_BH";
      break;
    case ar_DZ:
      os << "ar_DZ";
      break;
    case ar_EG:
      os << "ar_EG";
      break;
    case ar_IQ:
      os << "ar_IQ";
      break;
    case ar_JO:
      os << "ar_JO";
      break;
    case ar_KW:
      os << "ar_KW";
      break;
    case ar_LB:
      os << "ar_LB";
      break;
    case ar_LY:
      os << "ar_LY";
      break;
    case ar_MA:
      os << "ar_MA";
      break;
    case ar_OM:
      os << "ar_OM";
      break;
    case ar_QA:
      os << "ar_QA";
      break;
    case ar_SA:
      os << "ar_SA";
      break;
    case ar_SD:
      os << "ar_SD";
      break;
    case ar_SY:
      os << "ar_SY";
      break;
    case ar_TN:
      os << "ar_TN";
      break;
    case ar_YE:
      os << "ar_YE";
      break;
    case ast_ES:
      os << "ast_ES";
      break;
    case be_BY:
      os << "be_BY";
      break;
    case bg_BG:
      os << "bg_BG";
      break;
    case bhb_IN:
      os << "bhb_IN";
      break;
    case br_FR:
      os << "br_FR";
      break;
    case bs_BA:
      os << "bs_BA";
      break;
    case ca_AD:
      os << "ca_AD";
      break;
    case ca_ES:
      os << "ca_ES";
      break;
    case ca_FR:
      os << "ca_FR";
      break;
    case ca_IT:
      os << "ca_IT";
      break;
    case cs_CZ:
      os << "cs_CZ";
      break;
    case cy_GB:
      os << "cy_GB";
      break;
    case da_DK:
      os << "da_DK";
      break;
    case de_AT:
      os << "de_AT";
      break;
    case de_BE:
      os << "de_BE";
      break;
    case de_CH:
      os << "de_CH";
      break;
    case de_DE:
      os << "de_DE";
      break;
    case de_IT:
      os << "de_IT";
      break;
    case de_LI:
      os << "de_LI";
      break;
    case de_LU:
      os << "de_LU";
      break;
    case el_CY:
      os << "el_CY";
      break;
    case el_GR:
      os << "el_GR";
      break;
    case en_AU:
      os << "en_AU";
      break;
    case en_BW:
      os << "en_BW";
      break;
    case en_CA:
      os << "en_CA";
      break;
    case en_DK:
      os << "en_DK";
      break;
    case en_GB:
      os << "en_GB";
      break;
    case en_HK:
      os << "en_HK";
      break;
    case en_IE:
      os << "en_IE";
      break;
    case en_NZ:
      os << "en_NZ";
      break;
    case en_PH:
      os << "en_PH";
      break;
    case en_SC:
      os << "en_SC";
      break;
    case en_SG:
      os << "en_SG";
      break;
    case en_US:
      os << "en_US";
      break;
    case en_ZA:
      os << "en_ZA";
      break;
    case en_ZW:
      os << "en_ZW";
      break;
    case es_AR:
      os << "es_AR";
      break;
    case es_BO:
      os << "es_BO";
      break;
    case es_CL:
      os << "es_CL";
      break;
    case es_CO:
      os << "es_CO";
      break;
    case es_CR:
      os << "es_CR";
      break;
    case es_DO:
      os << "es_DO";
      break;
    case es_EC:
      os << "es_EC";
      break;
    case es_ES:
      os << "es_ES";
      break;
    case es_GT:
      os << "es_GT";
      break;
    case es_HN:
      os << "es_HN";
      break;
    case es_MX:
      os << "es_MX";
      break;
    case es_NI:
      os << "es_NI";
      break;
    case es_PA:
      os << "es_PA";
      break;
    case es_PE:
      os << "es_PE";
      break;
    case es_PR:
      os << "es_PR";
      break;
    case es_PY:
      os << "es_PY";
      break;
    case es_SV:
      os << "es_SV";
      break;
    case es_US:
      os << "es_US";
      break;
    case es_UY:
      os << "es_UY";
      break;
    case es_VE:
      os << "es_VE";
      break;
    case et_EE:
      os << "et_EE";
      break;
    case eu_ES:
      os << "eu_ES";
      break;
    case eu_FR:
      os << "eu_FR";
      break;
    case fi_FI:
      os << "fi_FI";
      break;
    case fo_FO:
      os << "fo_FO";
      break;
    case fr_BE:
      os << "fr_BE";
      break;
    case fr_CA:
      os << "fr_CA";
      break;
    case fr_CH:
      os << "fr_CH";
      break;
    case fr_FR:
      os << "fr_FR";
      break;
    case fr_LU:
      os << "fr_LU";
      break;
    case ga_IE:
      os << "ga_IE";
      break;
    case gd_GB:
      os << "gd_GB";
      break;
    case gl_ES:
      os << "gl_ES";
      break;
    case gv_GB:
      os << "gv_GB";
      break;
    case he_IL:
      os << "he_IL";
      break;
    case hr_HR:
      os << "hr_HR";
      break;
    case hsb_DE:
      os << "hsb_DE";
      break;
    case hu_HU:
      os << "hu_HU";
      break;
    case id_ID:
      os << "id_ID";
      break;
    case is_IS:
      os << "is_IS";
      break;
    case it_CH:
      os << "it_CH";
      break;
    case it_IT:
      os << "it_IT";
      break;
    case ja_JP:
      os << "ja_JP";
      break;
    case ka_GE:
      os << "ka_GE";
      break;
    case kk_KZ:
      os << "kk_KZ";
      break;
    case kl_GL:
      os << "kl_GL";
      break;
    case ko_KR:
      os << "ko_KR";
      break;
    case ku_TR:
      os << "ku_TR";
      break;
    case kw_GB:
      os << "kw_GB";
      break;
    case lg_UG:
      os << "lg_UG";
      break;
    case lt_LT:
      os << "lt_LT";
      break;
    case lv_LV:
      os << "lv_LV";
      break;
    case mg_MG:
      os << "mg_MG";
      break;
    case mi_NZ:
      os << "mi_NZ";
      break;
    case mk_MK:
      os << "mk_MK";
      break;
    case ms_MY:
      os << "ms_MY";
      break;
    case mt_MT:
      os << "mt_MT";
      break;
    case nb_NO:
      os << "nb_NO";
      break;
    case nl_BE:
      os << "nl_BE";
      break;
    case nl_NL:
      os << "nl_NL";
      break;
    case nn_NO:
      os << "nn_NO";
      break;
    case oc_FR:
      os << "os";
      break;
    case om_KE:
      os << "os";
      break;
    case pl_PL:
      os << "pl_PL";
      break;
    case pt_BR:
      os << "pt_BR";
      break;
    case pt_PT:
      os << "pt_PT";
      break;
    case ro_RO:
      os << "ro_RO";
      break;
    case ru_RU:
      os << "ru_RU";
      break;
    case ru_UA:
      os << "ru_UA";
      break;
    case sk_SK:
      os << "sk_SK";
      break;
    case sl_SI:
      os << "sl_SI";
      break;
    case so_DJ:
      os << "so_DJ";
      break;
    case so_KE:
      os << "so_KE";
      break;
    case so_SO:
      os << "so_SO";
      break;
    case sq_AL:
      os << "sq_AL";
      break;
    case st_ZA:
      os << "st_ZA";
      break;
    case sv_FI:
      os << "sv_FI";
      break;
    case sv_SE:
      os << "sv_SE";
      break;
    case tcy_IN:
      os << "tcy_IN";
      break;
    case tg_TJ:
      os << "tg_TJ";
      break;
    case th_TH:
      os << "th_TH";
      break;
    case tl_PH:
      os << "tl_PH";
      break;
    case tr_CY:
      os << "tr_CY";
      break;
    case tr_TR:
      os << "tr_TR";
      break;
    case uk_UA:
      os << "uk_UA";
      break;
    case uz_UZ:
      os << "uz_UZ";
      break;
    case wa_BE:
      os << "wa_BE";
      break;
    case xh_ZA:
      os << "xh_ZA";
      break;
    case yi_US:
      os << "yi_US";
      break;
    case zh_CN:
      os << "zh_CN";
      break;
    case zh_HK:
      os << "zh_HK";
      break;
    case zh_SG:
      os << "zh_SG";
      break;
    case zh_TW:
      os << "zh_TW";
      break;
    case zu_ZA:
      os << "zu_ZA";
      break;

    default:
      os << "???_???";
      break;
    }

  return os;
}

bool
try_ensure_locale ()
{
  using namespace std;

  // if (HOST_LANG != unknown)
  // return true;

  vector<tuple<string, Lang>> lclist = {
    // {"C.UTF-8", unknown}, // we dont need this
    {"aa_DJ.UTF-8", aa_DJ},   {"af_ZA.UTF-8", af_ZA}, {"an_ES.UTF-8", an_ES},
    {"ar_AE.UTF-8", ar_AE},   {"ar_BH.UTF-8", ar_BH}, {"ar_DZ.UTF-8", ar_DZ},
    {"ar_EG.UTF-8", ar_EG},   {"ar_IQ.UTF-8", ar_IQ}, {"ar_JO.UTF-8", ar_JO},
    {"ar_KW.UTF-8", ar_KW},   {"ar_LB.UTF-8", ar_LB}, {"ar_LY.UTF-8", ar_LY},
    {"ar_MA.UTF-8", ar_MA},   {"ar_OM.UTF-8", ar_OM}, {"ar_QA.UTF-8", ar_QA},
    {"ar_SA.UTF-8", ar_SA},   {"ar_SD.UTF-8", ar_SD}, {"ar_SY.UTF-8", ar_SY},
    {"ar_TN.UTF-8", ar_TN},   {"ar_YE.UTF-8", ar_YE}, {"ast_ES.UTF-8", ast_ES},
    {"be_BY.UTF-8", be_BY},   {"bg_BG.UTF-8", bg_BG}, {"bhb_IN.UTF-8", bhb_IN},
    {"br_FR.UTF-8", br_FR},   {"bs_BA.UTF-8", bs_BA}, {"ca_AD.UTF-8", ca_AD},
    {"ca_ES.UTF-8", ca_ES},   {"ca_FR.UTF-8", ca_FR}, {"ca_IT.UTF-8", ca_IT},
    {"cs_CZ.UTF-8", cs_CZ},   {"cy_GB.UTF-8", cy_GB}, {"da_DK.UTF-8", da_DK},
    {"de_AT.UTF-8", de_AT},   {"de_BE.UTF-8", de_BE}, {"de_CH.UTF-8", de_CH},
    {"de_DE.UTF-8", de_DE},   {"de_IT.UTF-8", de_IT}, {"de_LI.UTF-8", de_LI},
    {"de_LU.UTF-8", de_LU},   {"el_CY.UTF-8", el_CY}, {"el_GR.UTF-8", el_GR},
    {"en_HK.UTF-8", en_HK},   {"en_AU.UTF-8", en_AU}, {"en_BW.UTF-8", en_BW},
    {"en_CA.UTF-8", en_CA},   {"en_DK.UTF-8", en_DK}, {"en_GB.UTF-8", en_GB},
    {"en_HK.UTF-8", en_HK},   {"en_IE.UTF-8", en_IE}, {"en_NZ.UTF-8", en_NZ},
    {"en_PH.UTF-8", en_PH},   {"en_SC.UTF-8", en_SC}, {"en_SG.UTF-8", en_SG},
    {"en_US.UTF-8", en_US},   {"en_ZA.UTF-8", en_ZA}, {"en_ZW.UTF-8", en_ZW},
    {"es_AR.UTF-8", es_AR},   {"es_BO.UTF-8", es_BO}, {"es_CL.UTF-8", es_CL},
    {"es_CO.UTF-8", es_CO},   {"es_CR.UTF-8", es_CR}, {"es_DO.UTF-8", es_DO},
    {"es_EC.UTF-8", es_EC},   {"es_ES.UTF-8", es_ES}, {"es_GT.UTF-8", es_GT},
    {"es_HN.UTF-8", es_HN},   {"es_MX.UTF-8", es_MX}, {"es_NI.UTF-8", es_NI},
    {"es_PA.UTF-8", es_PA},   {"es_PE.UTF-8", es_PE}, {"es_PR.UTF-8", es_PR},
    {"es_PY.UTF-8", es_PY},   {"es_SV.UTF-8", es_SV}, {"es_US.UTF-8", es_US},
    {"es_UY.UTF-8", es_UY},   {"es_VE.UTF-8", es_VE}, {"et_EE.UTF-8", et_EE},
    {"eu_ES.UTF-8", eu_ES},   {"eu_FR.UTF-8", eu_FR}, {"fi_FI.UTF-8", fi_FI},
    {"fo_FO.UTF-8", eu_FR},   {"fr_BE.UTF-8", fr_BE}, {"fr_CA.UTF-8", fr_CA},
    {"fr_CH.UTF-8", fr_CH},   {"fr_FR.UTF-8", fr_FR}, {"fr_LU.UTF-8", fr_LU},
    {"ga_IE.UTF-8", ga_IE},   {"gd_GB.UTF-8", gd_GB}, {"gl_ES.UTF-8", gl_ES},
    {"gv_GB.UTF-8", gv_GB},   {"he_IL.UTF-8", he_IL}, {"hr_HR.UTF-8", hr_HR},
    {"hsb_DE.UTF-8", hsb_DE}, {"hu_HU.UTF-8", hu_HU}, {"id_ID.UTF-8", id_ID},
    {"is_IS.UTF-8", is_IS},   {"it_CH.UTF-8", it_CH}, {"it_IT.UTF-8", it_IT},
    {"ja_JP.UTF-8", ja_JP},   {"ka_GE.UTF-8", ka_GE}, {"kk_KZ.UTF-8", kk_KZ},
    {"kl_GL.UTF-8", kl_GL},   {"ko_KR.UTF-8", ko_KR}, {"ku_TR.UTF-8", ku_TR},
    {"kw_GB.UTF-8", kw_GB},   {"lg_UG.UTF-8", lg_UG}, {"lt_LT.UTF-8", lt_LT},
    {"lv_LV.UTF-8", lv_LV},   {"mg_MG.UTF-8", mg_MG}, {"mi_NZ.UTF-8", mi_NZ},
    {"mk_MK.UTF-8", mk_MK},   {"ms_MY.UTF-8", ms_MY}, {"mt_MT.UTF-8", mt_MT},
    {"nb_NO.UTF-8", nb_NO},   {"nl_BE.UTF-8", nl_BE}, {"nl_NL.UTF-8", nl_NL},
    {"nn_NO.UTF-8", nn_NO},   {"oc_FR.UTF-8", oc_FR}, {"om_KE.UTF-8", om_KE},
    {"pl_PL.UTF-8", pl_PL},   {"pt_BR.UTF-8", pt_BR}, {"pt_PT.UTF-8", pt_PT},
    {"ro_RO.UTF-8", ro_RO},   {"ru_RU.UTF-8", ru_RU}, {"ru_UA.UTF-8", ru_UA},
    {"sk_SK.UTF-8", sk_SK},   {"sl_SI.UTF-8", sl_SI}, {"so_DJ.UTF-8", so_DJ},
    {"so_KE.UTF-8", so_KE},   {"so_SO.UTF-8", so_SO}, {"sq_AL.UTF-8", sq_AL},
    {"st_ZA.UTF-8", st_ZA},   {"sv_FI.UTF-8", sv_FI}, {"sv_SE.UTF-8", sv_SE},
    {"tcy_IN.UTF-8", tcy_IN}, {"tg_TJ.UTF-8", tg_TJ}, {"th_TH.UTF-8", th_TH},
    {"tl_PH.UTF-8", tl_PH},   {"tr_CY.UTF-8", tr_CY}, {"tr_TR.UTF-8", tr_TR},
    {"uk_UA.UTF-8", uk_UA},   {"uz_UZ.UTF-8", uz_UZ}, {"wa_BE.UTF-8", wa_BE},
    {"xh_ZA.UTF-8", xh_ZA},   {"yi_US.UTF-8", yi_US}, {"zh_CN.UTF-8", zh_CN},
    {"zh_HK.UTF-8", zh_HK},   {"zh_SG.UTF-8", zh_SG}, {"zh_TW.UTF-8", zh_TW},
    {"zu_ZA.UTF-8", zu_ZA},
  };

  vector<Lang> supported = {};

  for (const tuple<string, Lang> &t : lclist)
    if (setlocale (LC_ALL, get<0> (t).c_str ()) != nullptr)
      {
	auto lc = get<1> (t);

	if (lc == PREFER_LANG)
	  {
	    HOST_LANG = lc;
	    return true;
	  }
	else
	  {
	    supported.push_back (lc);
	  }
      }

  if (supported.size () > 0)
    {
      HOST_LANG = supported[0];
      return true;
    }

  return false;
}
