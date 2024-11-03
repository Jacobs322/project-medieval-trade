#include <iostream>
#include <chrono>
#include <random>
#include <ctime>

#include "helpers.h"

#include "Message.h"
#include "Game.h"
#include "Menu.h"

using namespace std;
using namespace chrono;

float tick = 0.2;
const int map_width = 10;
const int map_height = 10;

int t_counter = 0;

// TO DO...
// Some kind of input protection..
// Pointer cleanup (mainly function pointers)
// Content fillup and prettyfication

const vector<string> available_resources= {
    "Wood",
    "Stone",
    "Clay",
    "Sand",
    "Food"
};

int main()
{
    // Variable declaration
    MailBox mailbox(&t_counter);
    Game game(&mailbox, &t_counter);
    Menu menu(&game);
    int new_counter = 1;
    int steps = 1;
    bool terminate = false;

    // Intro

    game.intro();

    srand(time(NULL));
    game.start(map_width, map_height);

    // Game Loop
    auto start_time = system_clock::now();
    auto end_time = system_clock::now();
    duration<double> diff = end_time - start_time;

    // Test and Debug

    while(true)
    {
        end_time = std::chrono::system_clock::now();
        diff = end_time - start_time;

        if(diff.count() > tick){

            t_counter++;
            start_time = system_clock::now();

            cout << "Day: " << t_counter << endl;
            game.step();

            if(t_counter == new_counter)
            {
                menu.standard(&steps, &terminate);
                if(terminate) break;
                new_counter = t_counter + steps;
                mailbox.clear_messages();
            }

        }
    }


    // After-Exit

    cout << "Terminating program" << endl;
    // Game & Menu deleted statically

    return 0;
}
