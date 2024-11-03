#include <iostream>
#include <iterator>
#include <list>

#include "helpers.h"
#include "MapNode.h"
#include "Route.h"
#include "Message.h"
#include "Connectable.h"

#pragma once

using namespace std;

// Game class responsible for keeping track of game state and rendering scenes in the console

class Game
{

    private:
        // Basic stats
        int* day;
        int gold = 0;

        // Sum of resources in respective buildings
        vector<pair<string, int>> resources_tracker = {
            {"Wood", 0},
            {"Stone", 0},
            {"Clay", 0},
            {"Sand", 0},
            {"Food", 0},
        };

        vector<pair<string, int>> means = {
            {"Carriages", 1},
            {"Workers", 10}
        };

        vector<pair<string, int>> means_in_use = {
            {"Carriages", 0},
            {"Workers", 0}
        };

        vector<pair<string, vector<pair<string, int>>*>> basic_data = {
            {"RESOURCES", &resources_tracker},
            {"AVAILABLE", &means},
            {"IN USE", &means_in_use}
        };

        const vector<string> available_buildings = {
            "Woodcutter's Lodge",
            "Quarry",
            "Clay Pit",
            "Sand Quarry",
            "Farm"
        };

        vector<Settlement*> settlements;
        vector<Building*> buildings;
        list<Route*> routes;

        MailBox* mailbox;

        // Map and Environment
        int map_width, map_height;
        MapNode **game_map;

    public:
        Game(MailBox* mailbox, int* day);
        ~Game();
        void start(const int map_width, const int map_height);
        void step();
        void save();
        void load();
        void map_seed();

        // Rendering functions
        void intro();
        void render_blank_rows(int number_of_rows);
        void render_standard();
        int render_messages();
        void render_map();
        void render_map_tile(int x, int y);
        int render_buildings();
        void render_building(Building *b);
        void render_building_info(int building_index);
        int render_settlements();
        void render_settlement(Settlement *s);
        void render_stock(Connectable *c, bool indexes = false);
        void render_settlement_market_sell(Settlement *s);
        void render_settlement_market_buy(Settlement *s);
        int render_routes();
        void render_route(Route *r);

        // Resource functions
        void add_tracker_resource(string resource_name, int amount);
        bool use_means(string means_name, int amount);
        bool release_means(string means_name, int amount);
        bool add_means(string mean_name, int amount);
        bool build(int x, int y, string building_name);
        vector<string> get_available_buildings();
        void clear_resources_tracker();
        void update_resources_tracker();
        int sell_resources(Settlement *s, string resource_name, int amount);
        int buy_means(Settlement *s, string mean_name, int amount);

        // Gameplay functions
        void buildings_step();
        void settlements_step();

        bool reserve_carriage();
        bool release_carriage();
        bool assign_workers(Building *b, int amount, int *assigned_workers);
        bool free_workers(Building *b, int amount, int *freed_workers);
        bool create_route(Connectable *sender, Connectable *receiver, std::string resource_name, int amount, bool repeating);
        void update_routes();
        void cancel_route(Route *r);

        // Helper functions
        MapNode* get_map_tile(int x, int y);
        Building* get_building_by_id(int id);
        Settlement* get_settlement_by_id(int id);
        Route* get_route_by_id(int id);

};
