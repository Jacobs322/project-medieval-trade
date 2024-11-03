#include <iostream>
#include <random>

#include "Connectable.h"

#pragma once

using namespace std;

// Settlement class to represent a settlement/establishment/city/etc..

class Settlement : public Connectable
{
    private:
        string name;
        string type;
        string description;
        int people;

        vector<pair<string, int>> resource_prices = {
            {"Wood", 2},
            {"Stone", 2},
            {"Clay", 2},
            {"Sand", 2},
            {"Food", 2}
        };

        vector<pair<string, int>> means_prices = {
            {"Carriages", 100},
            {"Workers", 20}
        };

    public:
        Settlement(int x, int y);
        ~Settlement() {};
        int sell_resources(string resource_name, int amount);
        int buy_means(string mean_name, int amount, int available_gold);
        string get_name();
        string get_type();
        string get_description();
        vector<pair<string, int>> get_resource_prices();
        int get_resource_price(string resource_name);
        vector<pair<string, int>> get_means_prices();
        int get_mean_price(string mean_name);
        int get_people();
        void step();
};
