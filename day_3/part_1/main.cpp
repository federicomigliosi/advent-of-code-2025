#include <iostream>
#include <fstream>
#include <string>
#include <charconv>

using namespace std;

string find_max_value(string s, int start_index, int finish_index, int* value_found_at_position){
    int max_value = s[start_index] - '0';
    *value_found_at_position = start_index;
    for(int j = start_index; j<=finish_index; j++){
        int i = s[j] - '0';
        if(i>max_value){
            max_value = i;
            *value_found_at_position = j;
        }
    }
    return to_string(max_value);
}

int main(){
    ifstream f("input.txt");
    string l;

    int output = 0;

    while(getline(f,l)){
        int position_first_max_value = 0;
        //Do not consider last character
        string first_max_value = find_max_value(l, 0, l.length()-3, &position_first_max_value);

        int position_second_max_value = 0;
        string second_max_value = find_max_value(l, position_first_max_value+1, l.length()-2, &position_second_max_value);
        output += stoi(first_max_value + second_max_value);
    }

    cout << "Solution : " << output << endl;

}