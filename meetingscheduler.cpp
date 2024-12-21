#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class User;
class Meeeting;
class Room;

class Meeting{
    int meeting_id;
    int start_time;
    int end_time;
    int capacity;
    vector <User> invited;
    int room_id;
};

class User{
    int user_id;
    vector <Meeting> meetings;

public:
    User(int user_id){
        this->user_id = user_id;
    }

    bool add_meeeting(const Meeting &meeting){
        
    }
};

class Room{
    int room_id;
    int capacity;
    vector <bool> availability;
    vector <vector <int>> meetings;

public:
    Room(int room_id, int capacity){
        this->room_id = room_id;
        this->capacity = capacity;
        availability.resize(24, true);
    }

    bool check_availabilty(int start_time, int end_time){
        for(int i = start_time; i < end_time; i++){
            if (availability[i] == false)
            {
                return false;
            }
        }
        return true;
    }

    void book_room(int start_time, int end_time,int meeting_id){
        for(int i = start_time; i < end_time; i++){
            availability[i] = false;
        }
        meetings.push_back({start_time, end_time, meeting_id});
    }

};