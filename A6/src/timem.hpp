#pragma once

#include "global_stuff.hpp"
#include "mission.hpp"

class TimeMission : public Mission{
public:
    TimeMission(int id_, int st_, int ed_, int target_, int reward_);
    bool check_completion(int count, int dist, int time);
private:
    
};
