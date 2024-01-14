#include "tf_msg.hh"
#include "tf_locale.hh"
#include <assert.h>
#include <iostream>

using namespace std;

int
main ()
{
  using namespace std;

  assert (can_decor ());

  cerr << "picked locale: " << setlocale (LC_ALL, nullptr) << endl;
  cerr << "picked host land: " << HOST_LANG << endl;

  // ascii + nonascii
  {
    string s = R"([ CHAT ] michael2 | TG-Focusing
[ SENDER ] michael2 | TG-Focusing
[ CONTENT ] 好好好好好好好好好好好好好好好。
[ DATE ] 2023-10-25 21:18:13 +0800 HKT
[ ID ] 0)";

    vector<tuple<int, int>> pos_info = get_decor_pos (s);

    cout << pos_info.size () << endl;
    assert (pos_info.size () == 5);

    assert ((pos_info[0] == make_tuple<int, int> (0, 8)));
    assert ((pos_info[1] == make_tuple<int, int> (32, 10)));
    assert ((pos_info[2] == make_tuple<int, int> (66, 11)));
    assert ((pos_info[3] == make_tuple<int, int> (95, 8)));
    assert ((pos_info[4] == make_tuple<int, int> (134, 6)));
  }

  // ascii + nonascii
  {
    string s = R"([ CHAT ] michael2 | TG-Focusing
[ SENDER ] michael2 | TG-Focusing
[ CONTENT ] ののののののののAA...
[ DATE ] 2023-10-25 21:20:13 +0800 HKT
[ ID ] 0)";

    vector<tuple<int, int>> pos_info = get_decor_pos (s);

    cout << pos_info.size () << endl;
    assert (pos_info.size () == 5);

    assert ((pos_info[0] == make_tuple<int, int> (0, 8)));
    assert ((pos_info[1] == make_tuple<int, int> (32, 10)));
    assert ((pos_info[2] == make_tuple<int, int> (66, 11)));
    assert ((pos_info[3] == make_tuple<int, int> (92, 8)));
    assert ((pos_info[4] == make_tuple<int, int> (131, 6)));
  }

  // ascii + emoji
  {
    string s = R"([ CHAT ] michael2 | TG-Focusing
[ SENDER ] michael2 | TG-Focusing
[ CONTENT ] 🤣🤣🤣🤣🤣🤣🤣🤣AA...
[ DATE ] 2023-10-25 21:32:48 +0800 HKT
[ ID ] 0)";

    vector<tuple<int, int>> pos_info = get_decor_pos (s);

    cout << pos_info.size () << endl;
    assert (pos_info.size () == 5);

    // <0,8>,<32,10>,<66,11>,<100,8>,<139,6>
    assert ((pos_info[0] == make_tuple<int, int> (0, 8)));
    assert ((pos_info[1] == make_tuple<int, int> (32, 10)));
    assert ((pos_info[2] == make_tuple<int, int> (66, 11)));
    assert ((pos_info[3] == make_tuple<int, int> (100, 8)));
    assert ((pos_info[4] == make_tuple<int, int> (139, 6)));
  }

  // ascii + nonascii + emoji
  {
    string s
      = R"([ CHAT ] michael2🐰🐭🐹🐻🐶🐱🌼🏵️💮🌸🪷🌺 | TG-Focusing
[ SENDER ] michael2🐰🐭🐹🐻🐶🐱🌼🏵️💮🌸🪷🌺 | TG-Focusing
[ CONTENT ] 🤣🤣🤣🤣🤣のののののAAAAA好好好好好
[ DATE ] 2023-10-25 21:28:50 +0800 HKT
[ ID ] 0)";

    vector<tuple<int, int>> pos_info = get_decor_pos (s);

    cout << pos_info.size () << endl;
    assert (pos_info.size () == 5);

    // <0,8>,<57,10>,<116,11>,<154,8>,<193,6>
    assert ((pos_info[0] == make_tuple<int, int> (0, 8)));
    assert ((pos_info[1] == make_tuple<int, int> (57, 10)));
    assert ((pos_info[2] == make_tuple<int, int> (116, 11)));
    assert ((pos_info[3] == make_tuple<int, int> (154, 8)));
    assert ((pos_info[4] == make_tuple<int, int> (193, 6)));
  }

  // ascii + emoji(sometimes rendered as 1 emoji, sometimes 2)
  {
    string s = R"([ CHAT ] michael2 | TG-Focusing
[ SENDER ] michael2 | TG-Focusing
[ CONTENT ] aaa😮‍💨😮‍💨😮‍💨aaa
[ DATE ] 2023-10-25 21:34:13 +0800 HKT
[ ID ] 0)";

    vector<tuple<int, int>> pos_info = get_decor_pos (s);

    cout << pos_info.size () << endl;
    assert (pos_info.size () == 5);

    // :<0,8>,<32,10>,<66,11>,<100,8>,<139,6>,
    assert ((pos_info[0] == make_tuple<int, int> (0, 8)));
    assert ((pos_info[1] == make_tuple<int, int> (32, 10)));
    assert ((pos_info[2] == make_tuple<int, int> (66, 11)));
    assert ((pos_info[3] == make_tuple<int, int> (100, 8)));
    assert ((pos_info[4] == make_tuple<int, int> (139, 6)));
  }

  return 0;
}
