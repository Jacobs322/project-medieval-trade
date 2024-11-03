#include "Menu.h"
#include "helpers.h"

using namespace std;

Menu::Menu(Game* game){

    this->game = game;

}


// Base menu
void Menu::standard(int* steps, bool* terminate){

    int input;
    bool read_again;

    *steps = 1;

    do{
        read_again = false;
        // Render active scene
        game->render_blank_rows(40);
        game->render_standard();

        cout << endl;
        cout << "1. Map" << endl;
        cout << "2. Build" << endl;
        cout << "3. My Buildings" << endl;
        cout << "4. Resources overview" << endl;
        cout << "5. Routes" << endl;
        cout << "6. Pass time" << endl;
        cout << "7. Help" << endl;
        cout << "8. Exit" << endl << endl;

        cout << "Number: ";
        cin >> input;

        if(!number_in_range(input, Map, Exit))
        {
            read_again = true;
            continue;
        }

        switch(input)
        {

            case Map:

                this->map(&read_again);

            break;
            case Build:

                this->build(&read_again);

            break;
            case My_Buildings:

                this->my_buildings(&read_again);

            break;
            case Resources:

                this->resources_overview(&read_again);

            case Routes:

                this->routes(&read_again);

            break;
            case PassTime:

                cout << "How long do you want to wait? (days)" << endl;
                cout << "Number: ";
                cin >> input;
                if(input == 0){
                    read_again = true;
                    continue;
                }
                *steps = input;

            break;
            case Help:

                this->help(&read_again);

            break;
            case Exit:

                *terminate = true;

            break;
            default:
                read_again = true;

        }
    }while(read_again);

}

// Base -> Map
void Menu::map(bool* parent_menu_repeat){

    int input;
    int x, y;
    bool read_again;

    *parent_menu_repeat = true;

    do{
        read_again = false;
        // Render active scene
        game->render_blank_rows(40);
        game->render_map();

        cout << endl;
        cout << "1. Back" << endl;
        cout << "2. Inspect tile" << endl;
        cout << endl;

        cout << "Number: ";
        cin >> input;

        if(!number_in_range(input, Back, Inspect))
        {
            read_again = true;
            continue;
        }

        switch(input)
        {
            case Back:

                return;
            case Inspect:

                cout << endl;
                cout << "Which tile, e.g. (0, 0), would you like to inspect?" << endl;
                cout << "Number: ";
                cin >> x;
                cout << "Number: ";
                cin >> y;

                map_inspect(&read_again, x, y);
                break;
            default:
                read_again = true;

        }
    }while(read_again);

}

// Base -> Map -> Inspect
void Menu::map_inspect(bool* parent_menu_repeat, int x, int y){

    *parent_menu_repeat = true;

    string buffer;
    int input;
    bool read_again;

    MapNode *m = game->get_map_tile(x, y);
    // Check if map tile exists (coordinates are on map)
    if(m == nullptr){
        *parent_menu_repeat = true;
        cout << "Any key: ";
        cin >> buffer;
        return;
    }

    int menu_end = 1;

    do{
        read_again = false;
        // Render active scene
        game->render_blank_rows(40);
        game->render_map();
        game->render_map_tile(x, y);

        cout << endl;
        cout << "1. Back" << endl;
        if(m->has_settlement()){
            cout << "2. Visit settlement" << endl;
            menu_end = 2;
        }

        cout << "Number: ";
        cin >> input;

        if(!number_in_range(input, Back, menu_end))
        {
            read_again = true;
            continue;
        }

        if(input == 2) settlement_inspect(&read_again, m->get_settlement());

    }while(read_again);

}

// Base -> Map -> Inspect -> Settlement
void Menu::settlement_inspect(bool* parent_menu_repeat, Settlement *s){

    *parent_menu_repeat = true;

    int input;
    bool read_again;

    do{
        read_again = false;
        // Render active scene
        game->render_blank_rows(40);
        game->render_settlement(s);

        cout << endl;
        cout << "1. Back" << endl;
        cout << "2. Send resources (One-time route)" << endl;
        cout << "3. Sell resources" << endl;
        cout << "4. Buy means" << endl;

        cout << "Number: ";
        cin >> input;

        if(!number_in_range(input, Back, Buy_Items))
        {
            read_again = true;
            continue;
        }

        switch(input)
        {
            case Back:
                return;
            case Send_Resources:

                this->create_route(&read_again, s, false);

                break;
            case Sell_Resources:

                this->sell_resources(&read_again, s);

                break;
            case Buy_Items:

                this->buy_items(&read_again, s);

                break;
            default:
                read_again = true;
        }

    }while(read_again);


}

// Base -> Map -> Inspect -> Build

// Base -> Build
void Menu::build(bool* parent_menu_repeat){

    *parent_menu_repeat = true;

    int input;
    int i;
    string buffer;
    int x, y;
    bool read_again;
    int building_index;

    do{
        read_again = false;
        // Render active scene
        game->render_blank_rows(40);

        cout << "What would you like to build? (Type 0 to go back)" << endl;
        cout << endl;

        // Render list of available buildings
        vector<string> available_buildings = this->game->get_available_buildings();
        for(i = 0; i < available_buildings.size(); i++)
        {
            cout << i+1 << ". " << available_buildings[i] << endl;
        }
        cout << endl;
        cout << "Number: ";
        cin >> input;
        if (input == 0) continue;

        building_index = input - 1;

        if(!number_in_range(input, 1, i))
        {
            read_again = true;
            continue;
        }

        // Display building info and ask for confirmation
        game->render_blank_rows(40);
        game->render_building_info(building_index);

        cout << endl;
        cout << "Confirm construction? 1/0 (Type 0 to go back)" << endl;
        cout << "Number: ";
        cin >> input;

        if (input == 0) continue;

        // Render map and ask for location of building
        game->render_blank_rows(40);
        game->render_map();
        cout << "Where would you like to build " << available_buildings[building_index] << "?" << endl;
        cout << "Number: ";
        cin >> x;
        cout << "Number: ";
        cin >> y;

        read_again = !this->game->build(x, y, available_buildings[building_index]);
        if(read_again){
            cout << "Any key: ";
            cin >> buffer;
        }

    }while(read_again);

}

// Base -> My Buildings
void Menu::my_buildings(bool* parent_menu_repeat){

    *parent_menu_repeat = true;

    int input;
    bool read_again;
    Building *b;

    do{
        read_again = false;
        // Render active scene
        game->render_blank_rows(40);
        game->render_buildings();

        cout << endl;
        cout << "1. Back" << endl;
        cout << "2. Inspect" << endl;

        cout << "Number: ";
        cin >> input;

        if(!number_in_range(input, Back, Inspect))
        {
            read_again = true;
            continue;
        }

        switch(input)
        {
            case Back:

                return;
                break;
            case Inspect:

                cout << endl;
                cout << "Which building would you want to inspect?" << endl;

                cout << "Number: ";
                cin >> input;
                b = this->game->get_building_by_id(input-1);

                building_inspect(&read_again, b);
                break;

            default:
                read_again = true;

        }

    }while(read_again);

}

// Base -> Resources Overview
void Menu::resources_overview(bool* parent_menu_repeat){

    *parent_menu_repeat = true;

    int input;
    bool read_again;
    Building *b;

    do{
        read_again = false;
        // Render active scene
        game->render_blank_rows(40);
        game->render_buildings();

        cout << endl;
        cout << "1. Back" << endl;
        cout << "2. Inspect" << endl;

        cout << "Number: ";
        cin >> input;

        if(!number_in_range(input, Back, Inspect))
        {
            read_again = true;
            continue;
        }

        switch(input)
        {
            case Back:

                return;
                break;
            case Inspect:

                cout << endl;
                cout << "Which building would you want to inspect?" << endl;

                cout << "Number: ";
                cin >> input;
                b = this->game->get_building_by_id(input-1);

                building_inspect(&read_again, b);
                break;

            default:
                read_again = true;

        }

    }while(read_again);

}

// Base -> My Buildings -> Building
void Menu::building_inspect(bool* parent_menu_repeat, Building* b){

    *parent_menu_repeat = true;

    int input;
    bool read_again;
    string buffer;

    do{
        read_again = false;
        // Render active scene
        game->render_blank_rows(40);
        game->render_building(b);

        cout << endl;
        cout << "1. Back" << endl;
        cout << "2. Send resources (One-time)" << endl;
        cout << "3. Create route (Repeating)" << endl;
        cout << "4. Assign workers" << endl;
        cout << "5. Free workers" << endl;
        cout << endl;

        cout << "Number: ";
        cin >> input;
        cout << endl;

        if(!number_in_range(input, Back, Free_Workers))
        {
            read_again = true;
            continue;
        }

        int x;
        bool repeating = false;

        switch(input)
        {
            case Back:
                return;
            case Send_Resources:
            case Create_Route:

                if(input == Create_Route) repeating = true;
                this->create_route(&read_again, b, repeating);

                break;
            case Assign_Workers:

                cout << "How many workers to assign?" << endl;
                cout << endl;
                cout << "Number: ";
                cin >> input;
                if(!game->assign_workers(b, input, &x)){
                    cout << "Not enough workers.." << endl;
                }else{
                    cout << x << " workers assigned." << endl;
                }
                cout << "Any key: ";
                cin >> buffer;

                break;
            case Free_Workers:

                cout << "How many workers to free?" << endl;
                cout << endl;
                cin >> input;
                cout << "Number: ";
                if(!game->free_workers(b, input, &x)){
                    cout << "Not enough workers.." << endl;
                }else{
                    cout << x << " workers freed." << endl;
                }
                cout << "Any key: ";
                cin >> buffer;

                break;
            default:
                read_again = true;

        }

    }while(read_again);

}

void Menu::create_route(bool *parent_menu_repeat, Connectable *sender, bool repeating){

    *parent_menu_repeat = true;

    int num_buffer;
    int input;
    string buffer;
    int send_resources_helper;
    int connectable_index;
    int stock_index;
    int stock_amount;
    Connectable *receiver;
    bool route;

    cout << endl;
    cout << "Where to send the resources? (0 to go back)" << endl;
    cout << "1. Settlement" << endl;
    cout << "2. Building" << endl;

    cout << "Number: ";
    cin >> send_resources_helper;

    game->render_blank_rows(40);
    switch(send_resources_helper)
    {
        case 1:
            num_buffer = game->render_settlements();
            break;
        case 2:
            num_buffer = game->render_buildings();
            break;
        case 0:
            return;
        default:
            cout << "Any key: ";
            cin >> buffer;
            return;
        }

        cout << "Number: ";
        cin >> input;
        if(input == 0 || send_resources_helper == 0) return;
        connectable_index = input - 1;

        game->render_blank_rows(40);
        cout << "Which resource do you want to send?" << endl;
        cout << endl;
        game->render_stock(sender, true);
        cout << endl;

        if(!sender->has_any_stock()){
            cout << "Any key: ";
            cin >> buffer;
            return;
        }
        cout << "Number: ";
        cin >> input;
        stock_index = input - 1;

        if(sender->get_resource(sender->list_resources()[stock_index].first) == 0){
            cout << "Any key: ";
            cin >> buffer;
            return;
        }

        game->render_blank_rows(40);
        cout << "How much do you want to send? (Carriage max capacity = 50)" << endl;
        cout << endl;
        cout << "Number: ";
        cin >> stock_amount;

        if(send_resources_helper == 1){
            receiver = game->get_settlement_by_id(connectable_index);
        }else{
            receiver = game->get_building_by_id(connectable_index);
        }

        route = game->create_route(sender, receiver, sender->list_resources()[stock_index].first, stock_amount, repeating);

        if(!route)
        {
            cout << "Resource send unsuccessful. (Trade route not created)" << endl;
            cout << "Any key: ";
            cin >> buffer;
        }else{
            cout << "Resource sent successfully." << endl;
            cout << "Any key: ";
            cin >> buffer;
        }
}

void Menu::routes(bool* parent_menu_repeat){

    *parent_menu_repeat = true;

    int input;
    bool read_again;

    do{
        read_again = false;
        // Render active scene
        game->render_blank_rows(40);
        game->render_routes();

        cout << endl;
        cout << "1. Back" << endl;
        cout << "2. Inspect" << endl;

        cout << "Number: ";
        cin >> input;

        if(!number_in_range(input, Back, Inspect))
        {
            read_again = true;
            continue;
        }

        switch(input)
        {
            case Back:

                return;
                break;
            case Inspect:

                cout << endl;
                cout << "Which route would you like to inspect?" << endl;
                cout << "Number: ";
                cin >> input;

                input--;

                if(!game->get_route_by_id(input)){
                        read_again = true;
                        continue;
                }

                route_inspect(&read_again, game->get_route_by_id(input));

            default:
                read_again = true;

        }

    }while(read_again);

}

void Menu::route_inspect(bool* parent_menu_repeat, Route* r){

    *parent_menu_repeat = true;

    int input;
    string buffer;
    bool read_again;

    do{
        read_again = false;
        // Render active scene
        game->render_blank_rows(40);
        game->render_route(r);

        cout << endl;
        cout << "1. Back" << endl;
        cout << "2. Cancel route" << endl;

        cout << "Number: ";
        cin >> input;

        if(!number_in_range(input, Back, Cancel_Route))
        {
            read_again = true;
            continue;
        }

        switch(input)
        {
            case Back:

                return;
                break;
            case Cancel_Route:

                game->cancel_route(r);
                cout << "Route cancelled. It will end once it has unloaded it's resources." << endl;
                cout << "Any key: ";
                cin >> buffer;

            default:
                read_again = true;

        }

    }while(read_again);

}

void Menu::help(bool* parent_menu_repeat){

    *parent_menu_repeat = true;

    string buffer;

    this->game->render_blank_rows(40);
    cout << "Project Medieval Trade" << endl;
    cout << "You are a merchant, your task is to gather resources, transport them and sell them for a profit" << endl;
    cout << endl;
    cout << "You can:" << endl;
    cout << "1. Explore the map" << endl;
    cout << "2. Build" << endl;
    cout << "3. Manage your buildings" << endl;
    cout << "4. Create trade routes" << endl;
    cout << endl;
    cout << "MAP:" << endl;
    cout << "O - settlement\nI - Forest\nV - Mountain\n~ - Marsh\n  - Flatlands" << endl;
    cout << endl;
    cout << "Each building can be only build on it's specified tile and produces only once \nit's built (needs resources) and once it has assigned workers" << endl;
    cout << endl;
    cout << "To sell your produced resources, you need to send them to a settlement, where you can sell." << endl;
    cout << "To transport resources you need carriages, one for every route." << endl;
    cout << "You can buy carriages and hire workers in settlements" << endl;
    cout << endl;
    cout << "TIPS:" << endl;
    cout << "You can visit settlements when inspecting a map tile with 'O'." << endl;
    cout << "You can create trade routes from buildings or settlements." << endl;
    cout << "Your buildings need 50 wood to start the construction process." << endl;
    cout << "Your buildings need workers assigned to function properly." << endl;
    cout << "Settlements have max resource capacity of 500." << endl;
    cout << "Your buildings have max resource capacity of 50." << endl;
    cout << endl;

    cout << "Press any key to continue.." << endl;
    cin >> buffer;

}

void Menu::sell_resources(bool* parent_menu_repeat, Settlement *s){

    *parent_menu_repeat = true;

    int input;
    string buffer;
    bool read_again;

    do{
        read_again = false;
        // Render active scene
        game->render_blank_rows(40);
        game->render_settlement_market_sell(s);

        cout << endl;
        cout << "Which resource would you like to sell? (0 to go back)" << endl;
        cout << endl;
        cout << "Number: ";
        cin >> input;

        if(input <= 0 ) return;
        if(input > s->list_resources().size()){
            read_again = true;
            continue;
        }

        buffer = s->list_resources()[input-1].first;

        cout << endl;
        cout << "How much of the resource would you like to sell?" << endl;
        cout << endl;
        cout << "Number: ";
        cin >> input;

        if(input <= 0)
        {
            read_again = true;
            continue;
        }

        input = game->sell_resources(s, buffer, input);
        cout << "You have received " << input << " gold." << endl;
        cout << "Any key: ";
        cin >> buffer;

    }while(read_again);

}

void Menu::buy_items(bool* parent_menu_repeat, Settlement *s){

    *parent_menu_repeat = true;

    int input;
    string buffer;
    bool read_again;

    do{
        read_again = false;
        // Render active scene
        game->render_blank_rows(40);
        game->render_settlement_market_buy(s);

        cout << endl;
        cout << "Which mean would you like to buy? (0 to go back)" << endl;
        cout << endl;
        cout << "Number: ";
        cin >> input;

        if(input <= 0 ) return;
        if(input > s->get_means_prices().size()){
            read_again = true;
            continue;
        }

        buffer = s->get_means_prices()[input-1].first;

        cout << endl;
        cout << "How much of the mean would you like to buy?" << endl;
        cout << endl;
        cout << "Number: ";
        cin >> input;

        if(input <= 0)
        {
            read_again = true;
            continue;
        }

        input = game->buy_means(s, buffer, input);
        if(input == 0){
            cout << "Buy unsuccessful" << endl;
        }else{
            cout << "Buy succesfull." << endl;
        }
        cout << "Any key: ";
        cin >> buffer;

    }while(read_again);

}
