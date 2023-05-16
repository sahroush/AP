#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const string INPUT_ERR = "INVALID_ARGUMENTS";
const string DUP_M_ID = "DUPLICATE_MISSION_ID";
const string DUP_D_MS = "DUPLICATE_DRIVER_MISSION";
const string NO_MISSION = "MISSION_NOT_FOUND";
const string NO_D_MISSION  = "DRIVER_MISSION_NOT_FOUND";
const char DELIM = ':';
const string OK = "OK";
const int MIN_TO_SEC = 60;

enum Commands{
    TIME_MSN = 1,
    DIST_MSN = 2,
    CNT_MSN = 3,
    ASSIGN = 4,
    RIDE = 5,
    SHOW = 6
};

static map <string, Commands> COMMAND = {
    {"add_time_mission", TIME_MSN},
    {"add_distance_mission", DIST_MSN},
    {"add_count_mission", CNT_MSN},
    {"assign_mission", ASSIGN},
    {"record_ride", RIDE},
    {"show_missions_status", SHOW}};

struct TimeRange{
    int l, r;
    TimeRange(){
        l = r = 0;
    }
    TimeRange(int L, int R){
        l = L, r = R;
        if(R < L)
            throw runtime_error(INPUT_ERR);
    }
    int len(){
        return r - l;
    }
    bool contains(TimeRange &other){
        return l <= other.l and other.r <= r;
    }
};

struct Ride{
    TimeRange tr;
    int dist;
    Ride(int L, int R, int d){
        tr = TimeRange(L, R);
        dist = d;
    }
};
