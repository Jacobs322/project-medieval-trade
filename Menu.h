#include <iostream>

#include "Game.h"

#pragma once

// Menu class responsible for capturing user input and controlling program flow

using namespace std;

class Menu
{
    private:
        Game* game;
        enum MenuItems {
            Map = 1,
            Build = 2,
            My_Buildings = 3,
            Resources = 4,
            Routes = 5,
            PassTime = 6,
            Help = 7,
            Exit = 8
        };
        enum MapMenuItems {
            Inspect = 2,
        };

        enum BuildingItems {
            Send_Resources = 2,
            Create_Route = 3,
            Assign_Workers = 4,
            Free_Workers = 5
        };

        enum SettlementItems {
            Sell_Resources = 3,
            Buy_Items = 4
        };

        enum Misc {
            Back = 1,
            Cancel_Route = 2
        };

    public:
        Menu(Game* game);
        void standard(int* steps, bool* terminate);
        void map(bool* parent_menu_repeat);
        void map_inspect(bool* parent_menu_repeat, int x, int y);
        void settlement_inspect(bool* parent_menu_repeat, Settlement *s);
        void build(bool* parent_menu_repeat);
        void my_buildings(bool* parent_menu_repeat);
        void resources_overview(bool* parent_menu_repeat);
        void building_inspect(bool* parent_menu_repeat, Building *b);
        void create_route(bool *parent_menu_repeat, Connectable *sender, bool repeating);
        void routes(bool* parent_menu_repeat);
        void route_inspect(bool* parent_menu_repeat, Route* r);
        void help(bool* parent_menu_repeat);
        void sell_resources(bool* parent_menu_repeat, Settlement *s);
        void buy_items(bool* parent_menu_repeat, Settlement *s);
};
