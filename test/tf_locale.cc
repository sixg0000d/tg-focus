#include <cassert>
#include <iostream>

#include "tf_locale.hh"

using namespace std;

int
main ()
{
  // assume we have two locales installed

  assert (HOST_LANG == unknown);
  assert (PREFER_LANG == unknown);

  // PREFER_LANG = Lang::zh_CN;

  try_ensure_locale ();

  if (HOST_LANG == en_HK)
    {
      PREFER_LANG = zh_CN;
      cout << PREFER_LANG << "," << HOST_LANG << endl;
      try_ensure_locale ();
      cout << PREFER_LANG << ",,," << HOST_LANG << endl;
      assert (HOST_LANG == zh_CN);
    }

  // assert (PREFER_LANG == unknown);

  return 0;
}
