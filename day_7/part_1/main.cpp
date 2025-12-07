#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
int main(){
    ifstream f("input.txt");

    string line;
    vector<string> grid;

    while(getline(f,line)){
        grid.push_back(line);
    }

    int solution =0;

    for(int i=0; i<=(grid.size() -1); i++){
        for(int j=0; j<grid[0].size(); j++){
            if(grid[i][j] == 'S'){
                grid[i+1][j] = '|';
            }else if((grid[i][j] == '|') && (i<=(grid.size() -2))){
                if(grid[i+1][j] == '^'){
                    solution += 1;
                    if(j-1 >=0){
                        grid[i+1][j-1] = '|';
                    }
                    if(j+1 <= (grid[i].size() - 1)){
                        grid[i+1][j+1] = '|';
                    }
                }else{
                    grid[i+1][j] = '|';
                }
            }
        }
    }

    cout << "Solution : " << solution << endl;
}