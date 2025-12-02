#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool has_repeated_sequences(string s, int length){
    //i: length of a subsequence
    for(int i=1; i<=(length/2); i++){
        if(length%i==0){
            //n: number of subsequences of length i
            int n = length/i;
            bool has_repeated_sequences = true;
            for(int j=1; j<=n; j++){
                if(s.substr(0,i) != s.substr(i*(j-1),i)){
                    has_repeated_sequences &= false;
                }
            }
            if(has_repeated_sequences){
                return true;
            }
        }
    }
    return false;
}

long long checkRange(string range){
    long long output = 0;
    int dash_position = range.find("-");
    long long first_ID = stoll(range.substr(0,dash_position));
    long long last_ID = stoll(range.substr(dash_position+1,range.length()));
    for(long long i = first_ID; i<=last_ID; i++){
        string string_ID = to_string(i);
        output += (has_repeated_sequences(string_ID, string_ID.length()) ? i: 0);
    }
    return output;
}

int main(){
    string s;
    ifstream f("input.txt");

    f >> s;

    int input_length = s.length();
    long long output = 0;

    int previous_delimitator=0;

    for(int i=0; i<=input_length; i++){
        if(s[i]==',' || i==input_length){
            string range = s.substr(previous_delimitator,i-previous_delimitator);
            output += checkRange(range);
            previous_delimitator = i+1;
        }
    }

    cout << "Solution : " << output << endl;

    f.close();
}