#include <cassert>

#include "tf_locale.hh"

int
main ()
{
  // assume we have two locales installed

  assert (HOST_LANG == unknown);
  assert (USER_LANG == unknown);

  return 0;
}
