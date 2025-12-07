#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cctype>
#include <cstdint>
#include <numeric>
#include <algorithm>

using namespace std;


int main(){
    ifstream f("input.txt");

	vector<string> v;
    string l;
    while(getline(f,l)){
        v.push_back(l);
    }

	uint64_t grand_total = 0;
	vector<uint64_t> a;

	for( int n=(v[ 0 ].size()-1); n >=0; n-- ){

		string s;
		for(int j=0; j != v.size() - 1; j++){
            s.push_back(v[j][n]);
        }

        //Skip rest of the code if it is a full empty vertical line
		if(count_if(s.begin(), s.end(), []( char c ) -> bool { return isdigit( c ); }) == 0){
            continue;
        }

        //Pushing back the vertical vector a, to perform a somewhat transposition
		a.push_back(stoull(s));

        //When reached the bottom of the vertical number lines,
        //  and no operation is found, then start from the beginning
		if(v[v.size() - 1][n] == ' '){
            continue;
        }

        char operation =v[v.size() - 1][n];
        uint64_t initial_value_accumulator = ((operation == '+') ? 0 : 1);

		grand_total += accumulate( a.begin(), a.end(),
                        initial_value_accumulator,
                        [operation]( uint64_t const x, uint64_t const y ) -> uint64_t
                        {
                            if(operation == '+'){
                                return (x + y);
                            }else{
                                return (x * y);
                            }
                        }
		);

		a.clear();
	}

	cout << "Solution : " << grand_total << endl;

    f.close();
}