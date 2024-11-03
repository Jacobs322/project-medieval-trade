#include <iostream>

#include "Connectable.h"

using namespace std;

Connectable::Connectable(int x, int y, int max_res){

    this->set_coordinates(x, y);
    this->max_resources = max_res;

}

void Connectable::set_mailbox(MailBox *mailbox){
    this->p_mailbox = mailbox;
}

MailBox* Connectable::mailbox(){
    return this->p_mailbox;
}

void Connectable::set_coordinates(int x, int y)
{
    this->coordinates.x = x;
    this->coordinates.y = y;
}

pair<int, int> Connectable::get_coordinates()
{
    return make_pair(coordinates.x, coordinates.y);
}

// Returns stock that could not be stored
int Connectable::add_stock(string resource_name, int value)
{
    int stock_overflowing = this->Stockpile.add_resource(resource_name, value);

    if(stock_overflowing){
        string message = this->get_name() + "'s stock is overflowing";
        this->p_mailbox->create_message(message);
    }

    return stock_overflowing;

}

// Returns stock that was taken
int Connectable::take_stock(string resource_name, int value)
{
    return this->Stockpile.remove_resource(resource_name, value);
}

vector<pair<string, int>> Connectable::list_resources(){

    return this->Stockpile.list_resources();

}

int Connectable::get_resource(string resource_name){

    return this->Stockpile.get_resource(resource_name);

}

bool Connectable::has_any_stock(){

    return this->Stockpile.has_any_stock();

}
