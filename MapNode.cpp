#include "MapNode.h"

using namespace std;

MapNode::MapNode(){

    this->terrain_id = rand()%4;
    this->settlement = nullptr;

    switch(this->terrain_id){

        case FLAT:
            this->terrain.symbol = ' ';
            this->terrain.biome = "Flatlands";
            this->terrain.description = "Expansive, fertile plains ideal for farming and settlement, but exposed to the elements and potential invasions.";
            break;

        case MARSH:
            this->terrain.symbol = '~';
            this->terrain.biome = "Marsh";
            this->terrain.description = "Wet, muddy terrain with dense vegetation, difficult to navigate but abundant in unique resources and wildlife.";
            break;

        case MOUNTAIN:
            this->terrain.symbol = 'V';
            this->terrain.biome = "Mountains";
            this->terrain.description = "Steep, rocky peaks providing natural defenses and valuable minerals, but challenging to traverse.";
            break;

        case FOREST:
            this->terrain.symbol = 'I';
            this->terrain.biome = "Forest";
            this->terrain.description = "Thick woodlands full of wildlife and resources, suitable for hunting and gathering, and offering natural cover.";
            break;

    }

}

MapNode::~MapNode(){

    delete this->settlement;

}

char MapNode::get_map_symbol(){

    if(this->has_settlement())
    {
        return 'O';
    }

    return this->terrain.symbol;

}

int MapNode::get_terrain_id(){
    return this->terrain_id;
}

string MapNode::get_biome(){

    return this->terrain.biome;

}

string MapNode::get_biome_description(){

    return this->terrain.description;

}

bool MapNode::is_flat(){

    return this->terrain_id == FLAT;

}

bool MapNode::is_water(){

    return this->terrain_id == MARSH;

}

bool MapNode::is_forest(){

    return this->terrain_id == FOREST;

}

bool MapNode::is_mountain(){

    return this->terrain_id == MOUNTAIN;

}

bool MapNode::has_settlement(){

    if(this->settlement == nullptr) return false;
    return true;
}

Settlement* MapNode::create_settlement(int x, int y){

    this->settlement = new Settlement(x, y);
    return this->settlement;

}

bool MapNode::has_building(){

    if(!this->buildings.empty())
    {
        return true;
    }
    return false;

}

void MapNode::add_building(Building *b){

    (this->buildings).push_back(b);

}

Settlement* MapNode::get_settlement(){
    return this->settlement;
}
