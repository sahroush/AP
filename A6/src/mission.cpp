#include "mission.hpp"

Mission::Mission(int id_, int st_, int ed_, int target_, int reward_)
    : range(st_, ed_) {
  id = id_;
  reward = reward_;
  target = target_;
  if (reward < 0 or target < 0)
    throw runtime_error(INPUT_ERR);
}

int Mission::get_id() { return id; }

int Mission::get_start() { return range.l; }

int Mission::get_reward() { return reward; }

TimeRange Mission::get_range() { return range; }