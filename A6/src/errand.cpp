#include "errand.hpp"

Errand::Errand(Mission* m){
    mission = m;
    is_done = false;
    end_time = -1;
    ride_count = total_dist = total_time = 0;
}

Errand::~Errand(){}

int Errand::get_start(){
    return mission->get_start();
}

int Errand::get_end(){
    return end_time;
}

int Errand::get_reward(){
    return mission->get_reward();
}

string Errand::get_status(){
    return (is_done ? "completed" : "ongoing");
}

bool Errand::operator< (const Errand &other) const{
    return mission->get_start() < other.mission->get_start();
}

void Errand::show(bool show_status){
    cout << "mission " << mission->get_id() << DELIM << endl;
    cout << "start timestamp: " << get_start() << endl; 
    cout << "end timestamp: " << get_end() << endl; 
    cout << "reward: " << get_reward() << endl;
    if(show_status)
        cout << "status: " << get_status() << endl;
}

void Errand::update(Ride ride){
    ride_count++;
    total_dist += ride.dist;
    total_time += ride.tr.len();
    if(mission->check_completion(ride_count, total_dist, total_time)){
        is_done = true;
        end_time = ride.tr.r;
    }
}

void Errand::add_ride(Ride ride){
    if(is_done)
        return;
    if(!mission->get_range().contains(ride.tr))
        return;
    update(ride);
    if(is_done)
        show(false);
}