#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Point{
public:
    long long x;
    long long y;
};



int main(){
    ifstream f("../input.txt");
    string s;

    vector<Point> vPoints;
    
    while(getline(f,s)){
        int i = s.find(',');
        long long x = stoi(s.substr(0,i));
        long long y = stoi(s.substr(i+1));
        Point p{x,y};
        vPoints.push_back(p);
    }

    long long max_area = 0;
    for(Point p1: vPoints){
        for(Point p2: vPoints){
            if((p1.x==p2.x)&&(p1.y==p2.y)){
                continue;
            }else{
                long long height = (p1.x - p2.x)>=0 ? (p1.x - p2.x) : abs(p1.x - p2.x)+1;
                long long width = (p1.y - p2.y)>=0 ? (p1.y - p2.y) : abs(p1.y - p2.y)+1;
                long long area = height*width;
                max_area = (area>max_area) ? area : max_area;
            }
        }
    }

    cout << "Solution: " << max_area << endl;

}