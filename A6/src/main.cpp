#include "global_stuff.hpp"

#include "system.hpp"

void proccess_line(string &line, System* sys){
    stringstream inp(line);
    string command;
    inp >> command;
    int driver_id, mission_id, reward, distance, target, st_time, ed_time;
    switch(COMMAND[command]){
        case(TIME_MSN):
            inp >> mission_id >> st_time >> ed_time >> target >> reward;
            sys->add_time_mission(mission_id, st_time, ed_time, target, reward);
            break;
        case(DIST_MSN):
            inp >> mission_id >> st_time >> ed_time >> target >> reward;
            sys->add_dist_mission(mission_id, st_time, ed_time, target, reward);
            break;
        case(CNT_MSN):
            inp >> mission_id >> st_time >> ed_time >> target >> reward;
            sys->add_count_mission(mission_id, st_time, ed_time, target, reward);
            break;
        case(ASSIGN):
            inp >> mission_id >> driver_id;
            sys->assign_mission(mission_id, driver_id);
            break;
        case(RIDE):
            inp >> st_time >> ed_time >> driver_id >> distance;
            sys->record_ride(st_time, ed_time, driver_id, distance);
            break;
        case(SHOW):
            inp >> driver_id;
            sys->show_status(driver_id);
            break;
        default:
            throw runtime_error(INPUT_ERR);
    }
}

void proccess_input(System* sys){
    string line;
    while(getline(cin, line)){
        try{
            proccess_line(line, sys);
        }
        catch(exception &e){
            cout << INPUT_ERR << endl;
        }
    }
}

int32_t main(){
    string line;
    System* sys = new System;
    proccess_input(sys);
    return 0;
}