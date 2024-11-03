#include <iostream>
#include <vector>
#include <map>
#include <cmath>

#include "Message.h"
#include "Connectable.h"

#pragma once

using namespace std;

// Parent Building class and child specialized classes to represent buildings and their effects

class Building : public Connectable
{
    private:
        string name;

        int workers_assigned = 0;
        int time_to_build;
        int workers_needed;

        string construction_status = "Construction planned"; // "Under construction" - "Built"
        string worker_status = "Vacant"; // "Partially occupied" - "Fully occupied" - "Without workers"

    public:
        Building(string name, int time_to_build, int workers_needed, int x = -1, int y = -1);
        virtual ~Building() {};

        string get_name();
        pair<string, int> get_construction_status();
        int assign_workers(int amount);
        int free_workers(int amount);
        string get_worker_status();
        pair<int, int> get_workers();

        bool is_ready_to_be_built();
        void update_construction_status();
        void update_worker_status();

        void step();                                                    // Every day actions of every building (building, produce..)

        virtual void produce(float modifier = 1) = 0;                   // Initialize what the building produces
        virtual map<string, int> cost() = 0;                  // Initialize what the building costs
        virtual bool check_build_requirements(int terrain) = 0;        // Initialize what are the requirements for construction

};

class Woodcutter : public Building{

    public:
        Woodcutter() : Building("Woodcutter's Lodge", 30, 10) {};
        ~Woodcutter() {};
        void produce(float modifier = 1);
        map<string, int> cost();
        bool check_build_requirements(int terrain);

};

class Quarry : public Building{

    public:
        Quarry() : Building("Quarry", 30, 10) {};
        ~Quarry() {};
        void produce(float modifier = 1);
        map<string, int> cost();
        bool check_build_requirements(int terrain);

};

class ClayPit : public Building{

    public:
        ClayPit() : Building("Clay Pit", 30, 10) {};
        ~ClayPit() {};
        void produce(float modifier = 1);
        map<string, int> cost();
        bool check_build_requirements(int terrain);

};

class SandQuarry : public Building{

    public:
        SandQuarry() : Building("Sand Quarry", 30, 10) {};
        ~SandQuarry() {};
        void produce(float modifier = 1);
        map<string, int> cost();
        bool check_build_requirements(int terrain);

};

class Farm : public Building{

    public:
        Farm() : Building("Farm", 30, 10) {};
        ~Farm() {};
        void produce(float modifier = 1);
        map<string, int> cost();
        bool check_build_requirements(int terrain);

};
