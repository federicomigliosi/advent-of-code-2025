#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){

	int dial = 50;
	int output = 0;
	ifstream f ("input.txt");
	string line;
	if (!f.is_open()) {
        	cerr << "Error opening the file!";
        	return 1;
    	}

	while(getline(f,line)){
		char rotation_direction = line[0];
		int rotation_value = stoi(line.substr(1,(line.size() - 1)));

		while(rotation_value != 0){

			if(rotation_direction == 'R'){
				dial = (dial + 1)%100;
			}else if(rotation_direction == 'L'){
				dial = (dial - 1)%100;
			}

			if(dial == 0){
				output+=1;
			}

			rotation_value-=1;

		}
	}

	f.close();

	cout << "The password for part 2 is: " << output << endl;
}