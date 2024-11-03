#include <iostream>
#include <vector>

#include "Message.h"
#include "Stockpile.h"

#pragma once

using namespace std;

// An object that is connectable by a trade route, e.g. has location and resource stock

class Connectable{

    private:
        /*
        vector<pair<string, int>> resources_stock = {
            {"Wood", 0},
            {"Stone", 0},
            {"Clay", 0},
            {"Sand", 0},
            {"Food", 0}
        };
        */

        Stockpile Stockpile;

        struct {
            int x;
            int y;
        } coordinates;

        int max_resources = 150;
        MailBox *p_mailbox;

    public:
        Connectable(){};
        Connectable(int x, int y, int max_res); // x and y position, maximum resources for given connectable
        ~Connectable(){};

        void set_mailbox(MailBox *mailbox);
        MailBox* mailbox();

        // Coordinate functions
        void set_coordinates(int x, int y);
        pair<int, int> get_coordinates();

        // Resources stock fucntions
        int add_stock(string resource_name, int value);
        int take_stock(string resource_name, int value);
        vector<pair<string, int>> list_resources();
        int get_resource(string resource_name);
        bool has_any_stock();

        virtual string get_name() = 0;
};
