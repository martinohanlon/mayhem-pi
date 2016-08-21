#ifndef TICKTIMER_H
#define TICKTIMER_H

class TickTimer {
public:
  void start(double secs, int ticks_per_sec);
  void reset();
  void tick();
  bool is_done();
  bool is_running();

private:
  int ticks_left = 0;
  bool running = false;
};

#endif // TICKTIMER_H
