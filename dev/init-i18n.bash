echo 'TGF_LANG,FWDED_HDR_CHAT,FWDED_HDR_SENDER,FWDED_HDR_MSG,FWDED_HDR_DATE,FWDED_HDR_ID,-' > dev/i18n.csv.tmp; sed -n '11,160p' shared/tf_locale.hh | sed 's/ //g' | sed 's/,//'  | sed 's/.*/\0,-,-,-,-,-,-/' >> dev/i18n.csv.tmp
