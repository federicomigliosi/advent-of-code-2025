#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

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

    vector<pair <long long, long long>> fresh_ingredient_ID_range_database = read_fresh_ingredient_ID_range("../input.txt");

    //order the ranges accornding to their first element
    sort(fresh_ingredient_ID_range_database.begin(), fresh_ingredient_ID_range_database.end(),[](pair<long long, long long> x, pair<long long, long long> y){
                                                                                                    return (x.first < y.first);
                                                                                                });

    long long fresh_ingredients = 0;

    long long starting_point = 0;                                                                                   
    for(auto p: fresh_ingredient_ID_range_database){
        long long first = p.first;
        long long second = p.second;

        if(first < starting_point){
            if(second > starting_point){
                fresh_ingredients += (second - starting_point);
            }
        }else if(first > starting_point){
            fresh_ingredients += (second - first + 1);
        }else{
            //case : first == starting_point
            fresh_ingredients += (second - starting_point);
        }
        starting_point = (starting_point<second) ? second : starting_point;
    }

    cout << "Solution : " << fresh_ingredients << endl;
}