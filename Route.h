#include <iostream>
#include <cmath>

#include "Connectable.h"
#include "Message.h"

#pragma once

// Route class to represent a transport route between 2 settlements

using namespace std;

class Route
{

    private:
        MailBox *m;
        Connectable *sender;
        Connectable *receiver;
        bool repeating;
        bool backwards;
        bool active;
        int route_time;
        int time_to_arrive;
        int carriage_speed = 2;
        int carraige_max_load = 50;

        pair<string, int> desired_payload;
        pair<string, int> actual_payload;

    public:
        Route(MailBox *m, Connectable *sender, Connectable *receiver, string resource_name, int amount, bool repeating);
        ~Route() {};
        int calculate_route_time();

        void route_end();
        void step();
        void load_resources();
        void unload_resources();
        void stop_repeating();

        bool is_active();
        bool is_repeating();
        bool is_backwards();
        pair<string, int> get_desired_payload();
        pair<string, int> get_actual_payload();
        string sender_name();
        pair<int, int> get_sender_coordinates();
        string receiver_name();
        pair<int, int> get_receiver_coordinates();
        int remaining_time();
        int get_route_time();

};
