#include "cntm.hpp"

CountMission::CountMission(int id_, int st_, int ed_, int target_, int reward_)
    : Mission(id_, st_, ed_, target_, reward_) {}

bool CountMission::check_completion(int count, int dist, int time) {
  return count >= target;
}