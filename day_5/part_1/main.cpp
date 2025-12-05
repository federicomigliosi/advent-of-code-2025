#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <fstream>

using namespace std;

vector<long long> read_ingredients_ID(string s){
    vector<long long> database;
    ifstream f(s);
    string line;
    bool line_break_found = false;

    while(getline(f, line)){
        if(line.size()==1){
            line_break_found = true;
            continue;
        }
        if(line_break_found){
            long long ingredient_ID = stoll(line);
            database.push_back(ingredient_ID);
        }
    }

    return database;
}

vector<pair<long long, long long>> read_fresh_ingredient_ID_range(string s){
    vector<pair<long long, long long>> database;
    ifstream f(s);
    string line;
    bool line_break_found = false;

    while(getline(f, line)){
        if(line.size()==1){
            line_break_found = true;
            continue;
        }
        if(!line_break_found){
            int index = line.find("-");
            auto p = make_pair(stoll(line.substr(0, index)) , stoll(line.substr(index+1)));
            database.push_back(p);
        }
    }

    return database;
}

int main(){

    vector<long long> ingredient_ID_database = read_ingredients_ID("../input.txt");
    vector<pair <long long, long long>> fresh_ingredient_ID_range_database = read_fresh_ingredient_ID_range("../input.txt");

    int available_ingredients = 0;
    
    for(auto ingredient_ID: ingredient_ID_database){
        for(auto p: fresh_ingredient_ID_range_database){
            if((ingredient_ID >= p.first) && (ingredient_ID <= p.second)){
                available_ingredients += 1;
                break;
            }
        }
    }

    cout << "Solution : " << available_ingredients << endl;
}