#include <assert.h>
#include <iostream>
#include <locale.h>

#include "tf_locale.hh"

using namespace std;

void
locales_must_have ()
{
  if (setlocale (LC_ALL, "en_HK.UTF-8") == nullptr
      || setlocale (LC_ALL, "en_US.UTF-8") == nullptr
      || setlocale (LC_ALL, "en_ZW.UTF-8") == nullptr)
    assert (false);

  if (setlocale (LC_ALL, "C") == nullptr)
    assert (false);
}

void
init_and_prefer (const char *init_lc_all, Lang prefer1, Lang prefer2)
{
  setlocale (LC_ALL, init_lc_all);
  PREFER_LANG = prefer1;
  try_ensure_locale ();
  cout << "prefer:" << PREFER_LANG << " actual:" << HOST_LANG << endl;
  assert (HOST_LANG == prefer1);
  PREFER_LANG = prefer2;
  try_ensure_locale ();
  cout << "prefer:" << PREFER_LANG << " actual:" << HOST_LANG << endl;
  assert (HOST_LANG == prefer2);
}

int
main ()
{
  assert (HOST_LANG == unknown);
  assert (PREFER_LANG == unknown);

  locales_must_have ();

  // init: en_HK
  init_and_prefer ("en_HK.UTF-8", en_US, en_ZW);
  init_and_prefer ("en_HK.UTF-8", en_ZW, en_US);

  // init: en_US
  init_and_prefer ("en_US.UTF-8", en_ZW, en_HK);
  init_and_prefer ("en_US.UTF-8", en_HK, en_ZW);

  // init: en_ZW
  init_and_prefer ("en_ZW.UTF-8", en_US, en_HK);
  init_and_prefer ("en_ZW.UTF-8", en_HK, en_US);

  return 0;
}
