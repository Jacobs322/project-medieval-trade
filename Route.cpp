#include "Route.h"

using namespace std;

Route::Route(MailBox *m, Connectable *sender, Connectable *receiver, std::string resource_name, int amount, bool repeating){

    this->m = m;
    this->sender = sender;
    this->receiver = receiver;
    this->desired_payload.first = resource_name;
    this->desired_payload.second = amount;
    this->actual_payload.first = resource_name;
    this->actual_payload.second = 0;
    this->repeating = repeating;

    this->route_time = this->calculate_route_time();
    this->load_resources();
    this->time_to_arrive = this->route_time;

    this->backwards = false;
    this->active = true;

}

int Route::calculate_route_time(){

    int x1 = this->sender->get_coordinates().first;
    int y1 = this->sender->get_coordinates().second;
    int x2 = this->receiver->get_coordinates().first;
    int y2 = this->receiver->get_coordinates().second;

    int width = abs(x2 - x1);
    int height = abs(y2 - y1);
    float distance = sqrt(width + height);

    return round(distance * this->carriage_speed);

}

void Route::route_end(){

    this->m->create_message("Route has finished.");

}

void Route::step(){

    this->time_to_arrive--;

    if(this->backwards && !this->repeating)
    {
        this->active = false;
        return;
    }

    if(this->time_to_arrive == 0)
    {
        if(this->backwards)
        {
            this->load_resources();
            this->backwards = false;
        }else{
            this->unload_resources();
            if(this->repeating)
            {
                this->backwards = true;
            }else{
                this->active = false;
                return;
            }

        }

        this->time_to_arrive = this->route_time;
    }

}

// Load resources from sender
void Route::load_resources(){

    if(this->desired_payload.second > this->carraige_max_load) this->desired_payload.second = this->carraige_max_load;

    int actual = this->sender->take_stock(this->desired_payload.first, this->desired_payload.second);

    this->actual_payload.second = actual;

    if(actual == 0){
        string message = "Route warning - " + this->sender->get_name() + "'s stock is empty.\n";
        this->m->create_message(message);
    }

}

// Unload resources into destination
void Route::unload_resources(){

    int actual = this->receiver->add_stock(this->actual_payload.first, this->actual_payload.second);

    if(actual > 0){
        string message = "Route warning - " + this->receiver->get_name() + "'s stock is overflowing.\n";
        this->m->create_message(message);
    }

    this->actual_payload.second = 0;

}

void Route::stop_repeating(){

    this->repeating = false;

}

bool Route::is_active(){
    return this->active;
}

bool Route::is_repeating(){
    return this->repeating;
}

bool Route::is_backwards(){
    return this->backwards;
}

pair<string, int> Route::get_desired_payload(){
    return this->desired_payload;
}

pair<string, int> Route::get_actual_payload(){
    return this->actual_payload;
}

string Route::sender_name(){
    return this->sender->get_name();
}

std::pair<int, int> Route::get_sender_coordinates(){
    return this->sender->get_coordinates();
}

string Route::receiver_name(){
    return this->receiver->get_name();
}

std::pair<int, int> Route::get_receiver_coordinates(){
    return this->receiver->get_coordinates();
}

int Route::remaining_time(){
    return this->time_to_arrive;
}

int Route::get_route_time(){
    return this->route_time;
}
