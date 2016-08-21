#include "ticktimer.h"

#include <algorithm>
#include <cassert>

void TickTimer::start(double secs, int ticks_per_sec) {
  running = true;
  ticks_left = secs * static_cast<double>(ticks_per_sec);
}

void TickTimer::reset() {
  assert(running);
  running = false;
  ticks_left = 0;
}

void TickTimer::tick() {
  assert(running);
  ticks_left = std::max(0, ticks_left - 1);
}

bool TickTimer::is_done() { return ticks_left == 0; }

bool TickTimer::is_running() { return running; }
