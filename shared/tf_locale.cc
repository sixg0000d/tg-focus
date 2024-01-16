#include <tuple>
#include <string>
#include <vector>

#include "tf_locale.hh"

enum Lang HOST_LANG = unknown;

enum Lang USER_LANG = unknown;

bool
try_ensure_locale ()
{
  using namespace std;

  if (HOST_LANG != unknown)
    return true;

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

  for (const tuple<string, Lang> &lc : lclist)
    if (setlocale (LC_ALL, get<0> (lc).c_str ()) != nullptr)
      {
	HOST_LANG = get<1> (lc);
	return true;
      }

  return false;
}