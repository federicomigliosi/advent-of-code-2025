#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <sstream>

using namespace std;

bool can_be_accessed(vector<vector<char>>& grid, int i, int j, int l, int h){
    if(grid[i][j]!='@'){
        return false;
    }

    int number_of_rolls = 0;

    //top left
    number_of_rolls += (((i-1)<0) || ((j-1)<0)) ? 0 : ((grid[i-1][j-1]=='@' || grid[i-1][j-1]=='x') ? 1 : 0);

    //top center
    number_of_rolls += ((i-1)<0) ? 0 : ((grid[i-1][j]=='@' || grid[i-1][j]=='x') ? 1 : 0);

    //top right
    number_of_rolls += (((i-1)<0) || ((j+1)>=l)) ? 0 : ((grid[i-1][j+1]=='@' || grid[i-1][j+1]=='x') ? 1 : 0);

    //center left
    number_of_rolls += ((j-1)<0) ? 0 : ((grid[i][j-1]=='@' || grid[i][j-1]=='x') ? 1 : 0);

    //center right
    number_of_rolls += ((j+1)>=l) ? 0 : ((grid[i][j+1]=='@' || grid[i][j+1]=='x') ? 1 : 0);

    //bottom left
    number_of_rolls += (((i+1)>=h) || ((j-1)<0)) ? 0 : ((grid[i+1][j-1]=='@' || grid[i+1][j-1]=='x') ? 1 : 0);

    //bottom center
    number_of_rolls += ((i+1)>=h) ? 0 : ((grid[i+1][j]=='@' || grid[i+1][j]=='x') ? 1 : 0);

    //bottom right
    number_of_rolls += (((i+1)>=h) || ((j+1)>=l)) ? 0 : ((grid[i+1][j+1]=='@' || grid[i+1][j+1]=='x') ? 1 : 0);

    if(number_of_rolls<4){
        grid[i][j] = 'x';
        return true;
    }else{
        return false;
    }
}

void turn_x_into_dot(vector<vector<char>>& grid, int l, int h){
    for(int i=0; i<h; i++){
        for(int j=0; j<l; j++){
            if(grid[i][j]=='x'){
                grid[i][j]='.';
            }
        }
    }
}

int main(){
    ifstream f("input.txt");
    
    vector<vector<char>> grid;

    string line;
    while (getline(f, line))
    {
        istringstream ss(line);

        grid.push_back({});

        char x;
        while (ss >> x){
            grid.back().push_back(x);
    
        }
    }

    //Assuming all rows have the same length
    int l = grid[0].size();
    int h = grid.size();

    int how_many_can_be_accessed = 0;

    while(true){
        int removed_in_current_step = 0;
        for(int i=0; i<h; i++){
            for(int j=0; j<l; j++){
                removed_in_current_step += (can_be_accessed(grid,i,j,l,h) ? 1 : 0);
            }
        }
        how_many_can_be_accessed += removed_in_current_step;

        turn_x_into_dot(grid,l,h);
        
        if(removed_in_current_step==0){
            break;
        }
    }    

    cout << "Solution : " << how_many_can_be_accessed << endl;

    f.close();
}