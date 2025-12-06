#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdint> 

using namespace std;

int main(){
    ifstream f("../input.txt");
    string line;
    vector<vector<string>> grid;

    while(getline(f,line)){
        istringstream ss(line);

        grid.push_back({});

        string x;
        while (ss >> x){
            grid.back().push_back(x);
    
        }
    }

    uint64_t grand_total = 0;
    for(int i=0; i<grid[0].size(); i++){
        uint64_t addition_accumulator = 0;
        uint64_t multiplication_accumulator = 1;
        for(auto a: grid){
            if(a[i]=="+"){
                grand_total += addition_accumulator;
                cout << "Addition result: "<< addition_accumulator << endl;
            }else if(a[i]=="*"){
                grand_total += multiplication_accumulator;
                cout << "Multiplication result: " << multiplication_accumulator << endl;
            }else{
                addition_accumulator += stoll(a[i]);
                multiplication_accumulator *= stoll(a[i]);
            }
        }
    }

    cout << "Solution : " << grand_total << endl;

    f.close();
}