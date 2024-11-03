#include <iostream>
#include <string>

#pragma once

using namespace std;

string pad_right(string str, int width);
string pad_right(int str, int width);
bool coordinates_in_range(int x, int y, int max_x, int max_y);
bool number_in_range(int n, int min, int max);
