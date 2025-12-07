#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;
int main(){
    ifstream f("input.txt");

    vector<vector<long long>> grid;

    string line;
    while (getline(f, line))
    {
        istringstream ss(line);

        grid.push_back({});

        char x;
        while (ss >> x){
            if(x=='.'){
                grid.back().push_back(0);
            }else if(x=='^'){
                grid.back().push_back(-2);
            }else if(x=='S'){
                grid.back().push_back(-1);
            }
        }
    }

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if(grid[i][j]==-1 && i==0){
                grid[i+1][j] += 1;
            }else if(grid[i][j]==-2 && i!=0){
                if(j-1>=0){
                    grid[i][j-1] += grid[i-1][j];
                }
                if(j+1 <= (grid[i].size() - 1)){
                    grid[i][j+1] += grid[i-1][j];
                }
            }else{
                //If it is not the first row
                if(i!=0 && grid[i-1][j]!=-1 && grid[i-1][j]!=-2){
                    grid[i][j] += grid[i-1][j];
                }
            }
        }
    }

    long long acc =0;
    for(long long x: grid.back()){
        acc += x;
    }
    cout << "Solution: "<< acc << endl;
}