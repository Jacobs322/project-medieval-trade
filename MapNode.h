#include <iostream>
#include <random>
#include <vector>

#include "Building.h"
#include "Settlement.h"

#pragma once

// MapNode class responsible for binding objects on a single tile on a map

using namespace std;

class MapNode
{
    private:
        int terrain_id;
        enum TerrainOptions {
            FLAT = 0,
            MARSH = 1,
            MOUNTAIN = 2,
            FOREST = 3
        };

        struct{

            char symbol;
            string biome;
            string description;

        } terrain;

        Settlement* settlement;

    public:
        MapNode();
        ~MapNode();
        char get_map_symbol();
        int get_terrain_id();
        string get_biome();
        string get_biome_description();
        bool is_flat();
        bool is_water();
        bool is_forest();
        bool is_mountain();
        bool has_settlement();
        Settlement* create_settlement(int x, int y);
        bool has_building();
        void add_building(Building *b);
        Settlement* get_settlement();

        // Public variables
        vector<Building*> buildings;
};
