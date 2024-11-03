#include "Building.h"

using namespace std;

// Generic building

Building::Building(string name, int time_to_build, int workers_needed, int x, int y) : Connectable(x, y, 50)
{
    this->name = name;
    this->time_to_build = time_to_build;
    this->workers_needed = workers_needed;
}

void Building::step()
{

    this->update_worker_status();

    if(this->construction_status != "Built")
    {

        this->update_construction_status();

    }else{

        float modifier = this->workers_assigned/this->workers_needed;
        this->produce(modifier);

    }

}

string Building::get_name(){
    return this->name;
}

pair<string, int> Building::get_construction_status(){
    return make_pair(this->construction_status, this->time_to_build);
}

// Returns number of unassigned workers from amount
int Building::assign_workers(int amount){

    int unassigned;
    if(this->workers_assigned + amount <= this->workers_needed)
    {
        this->workers_assigned += amount;
        unassigned = 0;
    }else{
        unassigned = this->workers_assigned+amount-this->workers_needed;
        this->workers_assigned = this->workers_needed;
    }

    this->update_worker_status();
    return unassigned;

}

// Returns number of freed workers
int Building::free_workers(int amount){

    int freed;
    if(this->workers_assigned - amount >= 0)
    {
        this->workers_assigned -= amount;
        freed = amount;
    }else{
        freed = this->workers_assigned;
        this->workers_assigned = 0;
    }

    this->update_worker_status();
    return freed;
}

std::string Building::get_worker_status(){
    return this->worker_status;
}

std::pair<int, int> Building::get_workers()
{
    return make_pair(this->workers_assigned, this->workers_needed);
}

bool Building::is_ready_to_be_built(){

    for(auto x : this->cost())
    {
        if(this->get_resource(x.first) < x.second) return false;
    }

    return true;
}

void Building::update_construction_status(){

    if(this->construction_status != "Under construction")
    {
        if(this->is_ready_to_be_built())
        {
            // Subtract cost of building from stock
            for(auto x : this->cost())
            {
                this->take_stock(x.first, x.second);
            }
            this->construction_status = "Under construction";
            this->time_to_build--;
        }

    }else{
        if(--this->time_to_build == 0)
        {
            this->construction_status = "Built";
            string message = this->get_name() + " was built.";
            this->mailbox()->create_message(message);
        }

    }

}

void Building::update_worker_status(){

    if(this->workers_assigned == 0) this->worker_status = "Vacant";
    else if(this->workers_assigned == this->workers_needed) this->worker_status = "Fully occupied";
    else this->worker_status = "Partially occupied";

}

// Woodcutter's Lodge

void Woodcutter::produce(float modifier) {

    int value = 5;

    value = ceil(value * modifier);
    this->add_stock("Wood", value);

}

map<string, int> Woodcutter::cost() {

    return {
        {"Wood", 50}
    };

}

bool Woodcutter::check_build_requirements(int terrain){

    return terrain == 3 ? true : false; // 3 = Forest

}

// Quarry

void Quarry::produce(float modifier) {

    int value = 5;

    value = ceil(value * modifier);
    this->add_stock("Stone", value);

}

map<string, int> Quarry::cost() {

    return {
        {"Wood", 50}
    };

}

bool Quarry::check_build_requirements(int terrain){

    return terrain == 2 ? true : false; // 2 = Mountain

}

// Clay pit

void ClayPit::produce(float modifier) {

    int value = 5;

    value = ceil(value * modifier);
    this->add_stock("Clay", value);

}

map<string, int> ClayPit::cost() {

    return {
        {"Wood", 50}
    };

}

bool ClayPit::check_build_requirements(int terrain){

    return terrain == 1 ? true : false; // 1 = Marsh

}

// Sand Quarry

void SandQuarry::produce(float modifier) {

    int value = 5;

    value = ceil(value * modifier);
    this->add_stock("Sand", value);

}

map<string, int> SandQuarry::cost() {

    return {
        {"Wood", 50}
    };

}

bool SandQuarry::check_build_requirements(int terrain){

    return terrain == 1 ? true : false; // 1 = Marsh

}

// Farm

void Farm::produce(float modifier) {

    int value = 5;

    value = ceil(value * modifier);
    this->add_stock("Food", value);

}

map<string, int> Farm::cost() {

    return {
        {"Wood", 50}
    };

}

bool Farm::check_build_requirements(int terrain){

    return terrain == 0 ? true : false; // 0 = Flatlands

}
