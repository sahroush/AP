#pragma once

#include "global_stuff.hpp"

class Mission {
public:
  virtual ~Mission(){};
  Mission(int id_, int st_, int ed_, int target_, int reward_);
  int get_id();
  int get_start();
  int get_reward();
  TimeRange get_range();
  virtual bool check_completion(int count, int dist, int time) = 0;

protected:
  TimeRange range;
  int target;

private:
  int reward, id;
};
