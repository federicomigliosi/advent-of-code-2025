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

    long long output = 0;

    while(getline(f,l)){
        string digit = "";
        int value_found_at_position = 0;

        for(int i=88; i<=99; i++){
            if(i==88){
                digit += find_max_value(l, value_found_at_position, i, &value_found_at_position);
            }else{
                digit += find_max_value(l, value_found_at_position + 1, i, &value_found_at_position);
            }
        }
        output += stoll(digit);
    }

    cout << "Solution : " << output << endl;

}