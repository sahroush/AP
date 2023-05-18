#pragma once

#include "cntm.hpp"
#include "distm.hpp"
#include "driver.hpp"
#include "global_stuff.hpp"
#include "mission.hpp"
#include "timem.hpp"

class System {
public:
  System();
  ~System();
  void add_time_mission(int mission_id, int st_time, int ed_time,
                        int target_time, int reward);
  void add_dist_mission(int mission_id, int st_time, int ed_time,
                        int target_dist, int reward);
  void add_count_mission(int mission_id, int st_time, int ed_time,
                         int target_cnt, int reward);
  void assign_mission(int mission_id, int driver_id);
  void record_ride(int st_time, int ed_time, int driver_id, int distance);
  void show_status(int driver_id);

private:
  map<int, Driver *> drivers;
  map<int, Mission *> missions;
};