#pragma once

#include "global_stuff.hpp"
#include "mission.hpp"

class Errand {
public:
  ~Errand();
  Errand(Mission *m);
  int get_start();
  int get_end();
  int get_reward();
  string get_status();
  bool operator<(const Errand &other) const;
  void show(bool show_status = true);
  void add_ride(Ride ride);

private:
  Mission *mission;
  bool is_done;
  int end_time;
  void update(Ride ride);
  int ride_count;
  int total_time;
  int total_dist;
};