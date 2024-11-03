#include <iostream>
#include <vector>

using namespace std;

class Stockpile{

    private:
        vector<string> available_resources= {"Wood", "Stone", "Clay", "Sand", "Food"};

        vector<pair<string, int>> resources;

        int maximum_capacity = 50;

    public:
        Stockpile();
        ~Stockpile(){};

        void set_capacity(int new_capacity);

        int add_resource(string name, int amount);
        int remove_resource(string name, int amount);
        int get_resource(string name);
        bool has_any_stock();
        vector<pair<string, int>> list_resources();

};
