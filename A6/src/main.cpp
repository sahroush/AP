#include "global_stuff.hpp"

#include "system.hpp"

void get_int(stringstream &ss, int &x){
    string str;
    ss >> str;
    x = stoi(str);
}

void proccess_line(string &line, System* sys){
    if(line.back() == WINDOWS_CRAP)
        line.pop_back();
    stringstream inp(line);
    string command;
    inp >> command;
    int driver_id, mission_id, reward, distance, target, st_time, ed_time;
    switch(COMMAND[command]){
        case(TIME_MSN):
            get_int(inp, mission_id), get_int(inp, st_time), get_int(inp, ed_time), get_int(inp, target), get_int(inp, reward);
            inp >> mission_id >> st_time >> ed_time >> target >> reward;
            sys->add_time_mission(mission_id, st_time, ed_time, target, reward);
            break;
        case(DIST_MSN):
            get_int(inp, mission_id), get_int(inp, st_time), get_int(inp, ed_time), get_int(inp, target), get_int(inp, reward);
            sys->add_dist_mission(mission_id, st_time, ed_time, target, reward);
            break;
        case(CNT_MSN):
            get_int(inp, mission_id), get_int(inp, st_time), get_int(inp, ed_time), get_int(inp, target), get_int(inp, reward);
            sys->add_count_mission(mission_id, st_time, ed_time, target, reward);
            break;
        case(ASSIGN):
            get_int(inp, mission_id), get_int(inp, driver_id);
            sys->assign_mission(mission_id, driver_id);
            break;
        case(RIDE):
            get_int(inp, st_time), get_int(inp, ed_time), get_int(inp, driver_id), get_int(inp, distance);
            sys->record_ride(st_time, ed_time, driver_id, distance);
            break;
        case(SHOW):
            get_int(inp, driver_id);
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