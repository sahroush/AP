#pragma once

#include "global_stuff.hpp"
#include "mission.hpp"

class DistMission : public Mission {
public:
  DistMission(int id_, int st_, int ed_, int target_, int reward_);
  bool check_completion(int count, int dist, int time);

private:
};
