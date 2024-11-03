#include "helpers.h"

using namespace std;

string pad_right(string str, int width){
    
    string appendix = "";
    int diff = width - str.length(); 
    if(diff > 0){
        
        for(int i = 0; i < diff; i++)
        {
            appendix += " ";
        }
        
    }
    return str + appendix;
    
}

std::string pad_right(int str, int width){
    
    string appendix = "";
    
    string result = to_string(str);
    
    int diff = width - result.length(); 
    if(diff > 0){
        
        for(int i = 0; i < diff; i++)
        {
            appendix += " ";
        }
        
    }
    return result + appendix;
    
}

bool coordinates_in_range(int x, int y, int max_x, int max_y){
    
    if(x > max_x || x < 0) return false;
    if(y > max_y || y < 0) return false;
    return true;
    
}

bool number_in_range(int n, int min, int max){
    
    return (n >= min && n <= max) ? true : false;
    
}