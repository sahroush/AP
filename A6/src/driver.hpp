#pragma once

#include "global_stuff.hpp"
#include "mission.hpp"
#include "errand.hpp"

class Driver{
public:
    Driver(int id_);
    ~Driver();
    void add_mission(Mission* m);
    void show_status();
    void add_ride(Ride ride);
private:
    map <int, Errand*> errands;
    int get_mission_count();
    int id;
};