#include <thread>
#include <fmt/core.h>

#include "state.hh"
#include "worker.hh"

int
main ()
{
  using namespace std;

  while (!tf_data.get_auth_hint ())
    {
      log ("Waiting for authorization");
      std::this_thread::sleep_for (std::chrono::seconds (3));
    }

  if (!tf_data.get_auth_hint ())
    {
      log ("Not authorized");
      return 1;
    }

  // tf_data.init()

  collector.init ();

  std::thread producer (focusd_producer);
  std::thread switcher (focusd_switcher);
  std::thread consumer (focusd_consumer);
  producer.join ();
  switcher.join ();
  consumer.join ();

  return 0;
}
