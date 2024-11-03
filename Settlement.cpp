#include "Settlement.h"

using namespace std;

Settlement::Settlement(int x, int y) : Connectable(x, y, 500){



    const vector<pair<string, string>> settlementNames = {
        {"Alderton", "The people of Alderton are skilled farmers, known for their fertile lands and abundant harvests."},
        {"Braxton", "Braxton is home to hardy miners, extracting precious metals and gems from the nearby mountains."},
        {"Caerwyn", "Caerwyn's inhabitants are renowned craftsmen, producing exquisite pottery and textiles."},
        {"Dunwich", "Dunwich is a coastal town with expert fishermen and sailors, supplying the region with fresh seafood."},
        {"Eldergrove", "The people of Eldergrove are herbalists and healers, drawing upon the ancient forest for remedies."},
        {"Fairhaven", "Fairhaven's citizens are traders and merchants, facilitating commerce and trade across the land."},
        {"Greenstead", "Greenstead is known for its skilled woodworkers and carpenters, crafting fine furniture and tools."},
        {"Harrowgate", "Harrowgate is a fortified town with a strong military presence, protecting the realm from invaders."},
        {"Inglewood", "Inglewood's residents are hunters and trappers, providing furs and meat to neighboring settlements."},
        {"Jorvik", "Jorvik is a bustling city with a rich cultural heritage, famous for its scholars and historians."},
        {"Kingsbridge", "Kingsbridge is a strategic crossing point with skilled bridge builders and engineers."},
        {"Lindisfarne", "Lindisfarne's monks and scribes are renowned for their illuminated manuscripts and learning."},
        {"Marshfield", "Marshfield is surrounded by wetlands, with people skilled in weaving reeds and managing water."},
        {"Northwold", "Northwold's hardy folk are adept at surviving harsh winters, excelling in hunting and foraging."},
        {"Oakwood", "Oakwood's people are known for their expertise in forestry and woodcraft, producing strong timber."},
        {"Pendlewick", "Pendlewick is a town of weavers and spinners, creating fine fabrics and tapestries."},
        {"Quinborough", "Quinborough's residents are scholars and alchemists, pursuing knowledge and mystical arts."},
        {"Ravenholm", "Ravenholm is a mysterious village, with people skilled in stealth and espionage."},
        {"Stonemoor", "Stonemoor's masons and builders are known for their sturdy stone structures and fortifications."},
        {"Thornfield", "Thornfield's people are adept at agriculture and horticulture, growing a variety of crops and plants."},
        {"Ulvington", "Ulvington's residents are known for their metalworking skills, producing fine weapons and armor."},
        {"Valewood", "Valewood is home to skilled archers and hunters, revered for their marksmanship."},
        {"Westford", "Westford's people are adept at horse breeding and training, providing steeds for the realm."},
        {"Yarnton", "Yarnton's inhabitants are skilled sailors and shipbuilders, crafting vessels for trade and exploration."},
        {"Zephyria", "Zephyria's people are known for their musical talents, producing bards and entertainers."},
        {"Ashby", "Ashby's residents are skilled blacksmiths, producing tools and equipment for the region."},
        {"Briarwood", "Briarwood is a village of herbalists and botanists, known for their knowledge of medicinal plants."},
        {"Coldwyn", "Coldwyn's people are adept at surviving in the cold, excelling in ice fishing and winter sports."},
        {"Drakewich", "Drakewich is known for its dragon lore, with people dedicated to studying and taming dragons."},
        {"Evesham", "Evesham's residents are renowned for their fruit orchards and cider production."}
    };

     int rand_index = rand()%30;
     this->name = settlementNames[rand_index].first;
     this->description = settlementNames[rand_index].second;
     this->people = (rand()%100)+50;
     this->type = "Camp"; // Later Camp -> Village -> Town -> Capitol

}

int Settlement::sell_resources(string resource_name, int amount){

    int sold = this->take_stock(resource_name, amount);

    int price = this->get_resource_price(resource_name) * sold;
    return price;

}

int Settlement::buy_means(string mean_name, int amount, int available_gold){

    int price = this->get_mean_price(mean_name);
    int total_price = price * amount;
    if(total_price <= available_gold)
    {
        return total_price;
    }else{
        return 0;
    }

}

string Settlement::get_name(){

    return this->name;

}

string Settlement::get_type(){

    return this->type;

}

string Settlement::get_description(){

    return this->description;

}

std::vector<std::pair<std::string, int>> Settlement::get_resource_prices(){

    return this->resource_prices;

}

int Settlement::get_resource_price(string resource_name){

    for(auto x : this->resource_prices)
    {
        if(x.first == resource_name) return x.second;
    }

}

std::vector<std::pair<std::string, int>> Settlement::get_means_prices(){

    return this->means_prices;

}

int Settlement::get_mean_price(string mean_name){

    for(auto x : this->means_prices)
    {
        if(x.first == mean_name) return x.second;
    }

}

int Settlement::get_people(){

    return this->people;

}

void Settlement::step(){

    this->people += 2;

}
