#include "Game.h"

Game::Game(MailBox* mailbox, int* day){

    this->mailbox = mailbox;
    this->day = day;

}

void Game::intro(){

    string buffer;

    this->render_blank_rows(40);
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
    cout << "You start with 50 wood in one of the settlements on the map, 1 carriage and 10 workers." << endl;
    cout << "It's recommended you start with building a woodcutter's lodge and sending the 50 wood there for it's construction" << endl;
    cout << "Good luck. More in help section." << endl;
    cout << endl;

    cout << "Press any key to start.." << endl;
    cin >> buffer;

}

void Game::start(const int map_width, const int map_height){

    this->map_width = map_width;
    this->map_height = map_height;

    this->game_map = new MapNode*[map_height];
    for(int i = 0; i < map_height; i++)
    {
        this->game_map[i] = new MapNode[map_width];
    }

    this->map_seed();

    // Starting resoruce
    this->settlements[0]->add_stock("Wood", 50);

}

void Game::map_seed(){

    int settlements_count = 0;

    do{
        for(int i = 0; i < map_width; i++)
        {
            for(int j = 0; j < map_height; j++)
            {
                if(game_map[i][j].is_flat())
                {
                    if(rand()%100 > 80 && settlements_count < 3)
                    {
                        Settlement *s = game_map[i][j].create_settlement(j, i);
                        this->settlements.push_back(s);
                        settlements_count++;
                    }
                }
            }
        }
    }while(settlements_count < 3);
}

Game::~Game(){

    int i;

    // Clear allocated map variables
    for(i = 0; i < map_height; i++)
    {
        delete[] this->game_map[i];
    }

    delete[] this->game_map;

    // Clear dynamically created buildings
    for(i = 0; i < this->buildings.size(); i++)
    {
        delete this->buildings[i];
    }

    // Clear dynamically created routes
    for(auto itr = this->routes.begin(); itr != this->routes.end(); itr++)
    {
        delete *itr;
        itr = this->routes.erase(itr);
    }

}

void Game::step(){

    buildings_step();
    settlements_step();
    update_routes();

    update_resources_tracker();

}

// Rendering functions ---------------------------------------------------------

void Game::render_blank_rows(int number_of_rows){

    for(int i = 0; i < number_of_rows; i++)
    {
        cout << endl;
    }

}

void Game::render_standard(){

    cout << pad_right("Day:", 15) << *this->day << endl;
    cout << pad_right("Gold:", 15) << this->gold << endl;
    cout << endl;

    int biggest = 0;
    int counter = 0;

    vector<pair<string, int>>::iterator itr_child[this->basic_data.size()][2];

    for(auto &x : this->basic_data)
    {
        itr_child[counter][0] = x.second->begin();
        itr_child[counter][1] = x.second->end();

        cout << pad_right(x.first, 20);
        if(x.second->size() > biggest) biggest = x.second->size();
        counter++;
    }
    cout << endl;

    for(int i = 0; i < biggest; i++)
    {
        for(int j = 0; j < this->basic_data.size(); j++)
        {
            if(itr_child[j][0] != itr_child[j][1])
            {
                cout << pad_right(itr_child[j][0]->first, 14) << pad_right(itr_child[j][0]->second, 5) << " ";
                itr_child[j][0] = next(itr_child[j][0]);
            }else{
                cout << pad_right("", 20);
            }
        }
        cout << endl;
    }

    this->render_messages();

}

int Game::render_messages(){

    list<Message*> messages = this->mailbox->get_messages();

    if(!messages.empty()) cout << endl;
    for(auto itr = messages.begin(); itr != messages.end(); itr++)
    {
        cout << (*itr)->message() << endl;
    }

    return messages.size();

}

void Game::render_map(){

    cout << "WORLD MAP" << endl;
    cout << endl;
    cout << "  ";
    for(int i = 0; i < this->map_width; i++)
    {
        cout << " " << i << " ";
    }
    cout << endl;
    for(int i = 0; i < this->map_width; i++)
    {
        cout << i << " ";
        for(int j = 0; j < this->map_height; j++)
        {
            // Actual rendering of map tile
            cout << " " << this->game_map[i][j].get_map_symbol() << " ";
        }
        cout << endl;
    }
}

void Game::render_map_tile(int x, int y){

    MapNode *tile = &this->game_map[y][x];

    // Tile information
    cout << endl;
    cout << "Tile " << "<" << y << ":" << x << ">" << " - " << tile->get_biome() << endl;
    cout << tile->get_biome_description() << endl;


    // Settlement(s) information
    cout << endl;
    if(!tile->has_settlement()) cout << "There are no settlements.. Maybe someone will come in the future." << endl;
    else{
        Settlement *settlement = tile->get_settlement();
        cout << "There is a " << settlement->get_type() << " called " << settlement->get_name() << endl;
    }

    // Building(s) information
    if(!tile->has_building()) cout << "There are no buildings.. We should get to work." << endl;
    for(int i = 0; i < tile->buildings.size(); i++)
    {
        cout << "There is a " << tile->buildings[i]->get_name() << endl;
    }

}

// Returns number of rendered buildings
int Game::render_buildings(){

    for(int i = 0; i < this->buildings.size(); i++)
    {
        cout << i+1 << ". " << pad_right(this->buildings[i]->get_name(), 20) << "<" <<this->buildings[i]->get_coordinates().first << ":" << this->buildings[i]->get_coordinates().second << ">" << endl;
    }

    if(this->buildings.empty()) cout << endl << "You haven't built anything yet.." << endl << endl;

    return this->buildings.size();
}

void Game::render_building(Building *b){

    cout << b->get_name() << endl;
    cout << "<" << b->get_coordinates().first << ":" << b->get_coordinates().second << ">" << endl;
    cout << endl;

    cout << pad_right("Status:", 15) << b->get_construction_status().first << ", " << b->get_construction_status().second << " days remaining" << endl;
    cout << pad_right("Workers:", 15) << b->get_worker_status() << ", " << b->get_workers().first << "/" << b->get_workers().second << endl;

    cout << endl;
    this->render_stock(b);

}

void Game::render_building_info(int building_index){

    cout << "Rendering building info." << endl;

}

int Game::render_settlements(){

    for(int i = 0; i < this->settlements.size(); i++)
    {
        cout << i+1 << ". " << pad_right(this->settlements[i]->get_name(), 20) << "<" <<this->settlements[i]->get_coordinates().first << ":" << this->settlements[i]->get_coordinates().second << ">" << endl;
    }

    return this->settlements.size();

}

void Game::render_settlement(Settlement *s){

    cout << s->get_type() << " " << s->get_name() << endl;
    cout << endl;
    cout << s->get_description() << endl;
    cout << endl;
    cout << pad_right("People:", 15) << s->get_people() << endl;
    cout << endl;
    cout << "Warehouse:" << endl;
    this->render_stock(s);

}

void Game::render_stock(Connectable *c, bool indexes){

    if(!c->has_any_stock())
    {
        cout << "Nothing in stock.." << endl;
        return;
    }
    auto stock = c->list_resources();
    for(int i = 0; i < stock.size(); i++)
    {
        if(stock[i].second > 0){
            if(indexes) cout << i+1 << ". ";
            cout << pad_right(stock[i].first, 15) << stock[i].second << endl;
        }
    }

}

void Game::render_settlement_market_sell(Settlement *s){

    cout << s->get_name() << "'s prices:" << endl;
    cout << endl;

    vector<pair<string, int>> stock = s->list_resources();
    vector<pair<string, int>> prices = s->get_resource_prices();

    for(int i = 0; i < stock.size(); i++)
    {
        cout << i+1 << ". " << pad_right(stock[i].first, 15) << prices[i].second << " gold per unit" << endl;
    }

}

void Game::render_settlement_market_buy(Settlement *s){

    cout << s->get_name() << "'s prices:" << endl;
    cout << endl;

    vector<pair<string, int>> means_prices = s->get_means_prices();

    for(int i = 0; i < means_prices.size(); i++){

        cout << i+1 << ". " << pad_right(means_prices[i].first, 10) << means_prices[i].second << " gold per unit" << endl;

    }

}

int Game::render_routes(){

    int i = 1;
    string direction;
    string payload;
    Route *route;
    for(auto itr = this->routes.begin(); itr != this->routes.end(); itr++, i++)
    {
        route = *itr;
        direction = " ----------> ";
        if(route->is_backwards()) direction = " <---------- ";
        payload = to_string(route->get_actual_payload().second) + " " + route->get_actual_payload().first;
        cout << i << ". " << pad_right(payload, 10)
             << " <" << route->get_sender_coordinates().first
             << ":" << route->get_sender_coordinates().second << "> "
             << route->sender_name()
             << direction
             << route->receiver_name()
             << " <" << route->get_receiver_coordinates().first << ":"
             << route->get_receiver_coordinates().second << "> - "
             << route->remaining_time() << " days remaining." << endl;
    }

    if(this->routes.empty()) cout << "There are currently no resources en route.." << endl;

    return this->routes.size();

}

void Game::render_route(Route *r){

    string direction = " ----------> ";
    if(r->is_backwards()) direction = " <---------- ";
    cout << r->sender_name() << direction << r->receiver_name() << " " << r->remaining_time() << " days remaining." << endl;
    cout << endl;

    cout << "Carriage is transporting:" << endl;
    cout << pad_right(r->get_desired_payload().first, 15) << r->get_actual_payload().second << "/" << r->get_desired_payload().second << endl;
    cout << endl;

    cout << pad_right("Perpetual:", 15) << (r->is_repeating() ? "Yes" : "No") << endl;
    cout << pad_right("Route time:", 15) << r->get_route_time() << " days" << endl;
    cout << pad_right("Status:", 15) << (r->is_active() ? "Active" : "Cancelled") << endl;

}

// Resource functions ----------------------------------------------------------

void Game::add_tracker_resource(string resource_name, int amount){

    for(auto &x : this->resources_tracker)
    {
        if(x.first == resource_name)
        {
            x.second += amount;
            break;
        }
    }
}

bool Game::use_means(string means_name, int amount){

    for(int i = 0; i < this->means.size(); i++)
    {
        if(this->means[i].first == means_name)
        {
            if(this->means[i].second - amount >= 0)
            {
                this->means[i].second -= amount;
                this->means_in_use[i].second += amount;
                return true;
            }else{
                return false;
            }
        }

    }
    return false;
}

bool Game::release_means(string means_name, int amount){

    return this->use_means(means_name, -amount);

}

bool Game::add_means(string mean_name, int amount){

    for(auto &x : this->means)
    {
        if(x.first == mean_name)
        {
            x.second += amount;
            return true;
        }
    }

    return false;
}

vector<string> Game::get_available_buildings()
{
    return this->available_buildings;
}

bool Game::build(int x, int y, string building_name){

    if(!coordinates_in_range(x, y, this->map_width-1, this->map_height-1)){
        cout << "Coordinates not on map." << endl;
        return false;
    }

    if(building_name == "Farm")
    {
        Farm *b = new Farm();
        if(b->check_build_requirements(game_map[y][x].get_terrain_id()))
        {
            this->buildings.push_back(b);
            this->game_map[y][x].add_building(b);
        }else{
            cout << "You cannot build that on a " << game_map[y][x].get_biome() << " tile." << endl;
            return false;
        }
    }else if(building_name == "Woodcutter's Lodge")
    {
        Woodcutter *b = new Woodcutter();
        if(b->check_build_requirements(game_map[y][x].get_terrain_id()))
        {
            this->buildings.push_back(b);
            this->game_map[y][x].add_building(b);
        }else{
            cout << "You cannot build that on a " << game_map[y][x].get_biome() << " tile." << endl;
            return false;
        }
    }else if(building_name == "Quarry")
    {
        Quarry *b = new Quarry();
        if(b->check_build_requirements(game_map[y][x].get_terrain_id()))
        {
            this->buildings.push_back(b);
            this->game_map[y][x].add_building(b);
        }else{
            cout << "You cannot build that on a " << game_map[y][x].get_biome() << " tile." << endl;
            return false;
        }
    }else if(building_name == "Clay Pit")
    {
        ClayPit *b = new ClayPit();
        if(b->check_build_requirements(game_map[y][x].get_terrain_id()))
        {
            this->buildings.push_back(b);
            this->game_map[y][x].add_building(b);
        }else{
            cout << "You cannot build that on a " << game_map[y][x].get_biome() << " tile." << endl;
            return false;
        }
    }else if(building_name == "Sand Quarry")
    {
        SandQuarry *b = new SandQuarry();
        if(b->check_build_requirements(game_map[y][x].get_terrain_id()))
        {
            this->buildings.push_back(b);
            this->game_map[y][x].add_building(b);
        }else{
            cout << "You cannot build that on a " << game_map[y][x].get_biome() << " tile." << endl;
            return false;
        }
    }

    int last_index = (this->buildings).size() - 1;

    this->buildings[last_index]->set_coordinates(x, y);
    this->buildings[last_index]->set_mailbox(this->mailbox);

    return true;
}

void Game::buildings_step(){

    for(auto b : buildings)
    {
        b->step();
    }

}

void Game::settlements_step(){

    for(auto s : settlements)
    {
        s->step();
    }

}

bool Game::reserve_carriage(){

    return this->use_means("Carriages", 1);

}

bool Game::release_carriage(){

    return this->release_means("Carriages", 1);

}

bool Game::assign_workers(Building *b, int amount, int *assigned_workers){

    int failed_to_assign;
    failed_to_assign = b->assign_workers(amount);
    *assigned_workers = amount - failed_to_assign;
    return this->use_means("Workers", *assigned_workers);

}

bool Game::free_workers(Building *b, int amount, int *freed_workers){

    *freed_workers = b->free_workers(amount);
    return this->release_means("Workers", *freed_workers);

}

bool Game::create_route(Connectable *sender, Connectable *receiver, string resource_name, int amount, bool repeating){

    // Check if sender and receiver are not the same object
    if(sender == receiver) return false;

    // Check if there is a carriage available
    if(!this->reserve_carriage()) return false;

    Route *r = new Route(this->mailbox, sender, receiver, resource_name, amount, repeating);
    this->routes.push_back(r);

    return true;

}

void Game::update_routes(){

    Route *route;
    for(auto itr = this->routes.begin(); itr != this->routes.end(); itr++)
    {
        route = *itr;
        route->step();
        if(!route->is_active())
        {
            route->route_end();
            itr = this->routes.erase(itr);
            this->release_carriage();
        }
    }

}

void Game::cancel_route(Route *r){

    r->stop_repeating();

}

void Game::clear_resources_tracker(){

    for(auto &x : this->resources_tracker)
    {
        x.second = 0;
    }

}

void Game::update_resources_tracker(){

    this->clear_resources_tracker();

    // Add up resources in buildings
    for(auto b : this->buildings)
    {
        for(auto s : b->list_resources())
        {
            this->add_tracker_resource(s.first, s.second);
        }
    }

    // Add up resources in settlements
    for(auto s : this->settlements)
    {
        for(auto x : s->list_resources())
        {
            this->add_tracker_resource(x.first, x.second);
        }
    }

    // Add up resources en route
    string resource_name;
    int amount;
    for(auto r : this->routes)
    {
        resource_name = r->get_actual_payload().first;
        amount = r->get_actual_payload().second;
        this->add_tracker_resource(resource_name, amount);
    }

}

int Game::sell_resources(Settlement *s, string resource_name, int amount){

    int gold_amount = s->sell_resources(resource_name, amount);
    this->gold += gold_amount;

    return gold_amount;

}

int Game::buy_means(Settlement *s, string mean_name, int amount){

    int total_price = s->buy_means(mean_name, amount, this->gold);
    this->gold -= total_price;

    if(total_price > 0)
    {
        this->add_means(mean_name, amount);
    }

    return total_price;

}

// Helper functions ------------------------------------------------------------
MapNode* Game::get_map_tile(int x, int y){

    if(coordinates_in_range(x, y, this->map_width-1, this->map_height-1)){
        return &(this->game_map[y][x]);
    }
    else{
        cout << "Coordinates not on map." << endl;
        return nullptr;
    }

}

Building* Game::get_building_by_id(int id){

    return this->buildings[id];

}

Settlement* Game::get_settlement_by_id(int id){

    return this->settlements[id];

}

Route* Game::get_route_by_id(int id){

    int i = 0;
    for(auto itr = this->routes.begin(); itr != this->routes.end(); itr++, i++)
    {
        if(i == id) return *itr;
    }

    return nullptr;

}
