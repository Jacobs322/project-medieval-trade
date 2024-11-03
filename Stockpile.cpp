#include <iostream>

#include "Stockpile.h"

using namespace std;

Stockpile::Stockpile(){

    for(int x = 0; x < this->available_resources.size(); x++){

        this->resources.push_back(make_pair(this->available_resources.at(x), 0));

    }

}

void Stockpile::set_capacity(int new_capacity){

    this->maximum_capacity = new_capacity;

}

int Stockpile::add_resource(string name, int amount){

    int overflowing = 0;
    for(auto &x : this->resources)
    {
        if(x.first == name)
        {
            if(x.second + amount > this->maximum_capacity){
                overflowing = x.second + amount - this->maximum_capacity;
                x.second = this->maximum_capacity;
                return overflowing;
            }
            x.second += amount;
            return overflowing;
        }
    }

}

int Stockpile::remove_resource(string name, int amount){

    int taken = 0;
    for(auto &x : this->resources)
    {
        if(x.first == name)
        {
            if(x.second - amount < 0){
                taken = x.second;
                x.second = 0;
                return taken;
            }
            x.second -= amount;
            return amount;
        }
    }

}

int Stockpile::get_resource(string name){

    for(int i = 0; i < this->resources.size(); i++)
    {
        if(this->resources[i].first == name) return this->resources[i].second;
    }

    return 0;

}

bool Stockpile::has_any_stock(){

    for(auto x : this->resources)
    {
        if(x.second > 0) return true;
    }

    return false;

}

vector<pair<string, int>> Stockpile::list_resources(){

    return this->resources;

}
