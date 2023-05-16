#include "timem.hpp"

TimeMission::TimeMission(int id_, int st_, int ed_, int target_, int reward_):
    Mission(id_, st_, ed_, target_ * MIN_TO_SEC, reward_){}

bool TimeMission::check_completion(int count, int dist, int time){
    return time >= target;
}