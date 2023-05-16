#include "system.hpp"

System::System(){

}

System::~System(){
    for(auto x : drivers)
        delete x.second;
    for(auto x : missions)
        delete x.second;
}

void System::add_time_mission(int mission_id, int st_time, int ed_time, int target_time, int reward){
    if(missions.count(mission_id)){
        cout << DUP_M_ID << endl;
    }
    else{
        try{
            missions[mission_id] = new TimeMission(mission_id, st_time, ed_time, target_time, reward);
            cout << OK << endl;
        }
        catch(exception &e){
            cout << e.what() << endl;
        }
    }
}

void System::add_dist_mission(int mission_id, int st_time, int ed_time, int target_dist, int reward){
    if(missions.count(mission_id)){
        cout << DUP_M_ID << endl;
    }
    else{
        try{
            missions[mission_id] = new DistMission(mission_id, st_time, ed_time, target_dist, reward);
            cout << OK << endl;
        }
        catch(exception &e){
            cout << e.what() << endl;
        }
    }
}

void System::add_count_mission(int mission_id, int st_time, int ed_time, int target_cnt, int reward){
    if(missions.count(mission_id)){
        cout << DUP_M_ID << endl;
    }
    else{
        try{
            missions[mission_id] = new CountMission(mission_id, st_time, ed_time, target_cnt, reward);
            cout << OK << endl;
        }
        catch(exception &e){
            cout << e.what() << endl;
        }
    }
}

void System::assign_mission(int mission_id, int driver_id){
    try{
        if(!missions.count(mission_id))
            throw runtime_error(NO_MISSION);
        if(!drivers.count(driver_id))
            drivers[driver_id] = new Driver(driver_id);
        drivers[driver_id]->add_mission(missions[mission_id]);
        cout << OK << endl;
    }
    catch(exception &e){
        cout << e.what() << endl;
    }
}

void System::record_ride(int st_time, int ed_time, int driver_id, int distance){
    try{
        if(drivers.count(driver_id))
            drivers[driver_id]->add_ride(Ride(st_time, ed_time, distance));
    }
    catch(exception &e){
        cout << e.what() << endl;
    }
}

void System::show_status(int driver_id){
    try{
        if(!drivers.count(driver_id))
            throw runtime_error(NO_D_MISSION); 
        drivers[driver_id]->show_status();
    }
    catch(exception &e){
        cout << e.what() << endl;
    }
}