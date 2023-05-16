#pragma once

#include "global_stuff.hpp"
#include "mission.hpp"

class CountMission : public Mission{
public:
    CountMission(int id_, int st_, int ed_, int target_, int reward_);
    bool check_completion(int count, int dist, int time);
private:
    
};
