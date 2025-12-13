#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <map>

using namespace std;

class Point {
    public:
    long long x{};
    long long y{};
    long long z{};

    Point(long long x, long long y, long long z)
        : x(x), y(y), z(z) {}

    // --- Distance to another point ---
    double distanceTo(const Point& other) const {
        return std::sqrt(
            std::pow(x - other.x, 2) +
            std::pow(y - other.y, 2) +
            std::pow(z - other.z, 2)
        );
    }

    // --- Operators ---
    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return z < other.z;
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};
    

using Circuit = set<Point>;
using SharedCircuit = shared_ptr<Circuit>;

struct DistancePair {
    double distance;
    Point a;
    Point b;
};

// --- Parse file into points ---
vector<Point> parseFile(const string& filename){
    ifstream f(filename);
    string s;

    vector<Point> points;
    while (getline(f, s)) {
        auto p1 = s.find(',');
        auto p2 = s.find(',', p1 + 1);

        long long x = stoll(s.substr(0, p1));
        long long y = stoll(s.substr(p1 + 1, p2 - p1 - 1));
        long long z = stoll(s.substr(p2 + 1));

        points.push_back({x, y, z});
    }
    return points;
}

// --- Build sorted list of all unique point–point pairs ---
vector<DistancePair> sortedPairsByDistance(const vector<Point>& points){
    vector<DistancePair> pairs;
    pairs.reserve(points.size() * points.size() / 2);

    for (size_t i = 0; i < points.size(); i++) {
        for (size_t j = i + 1; j < points.size(); j++) {
            double d = points[i].distanceTo(points[j]);
            pairs.push_back({d, points[i], points[j]});
        }
    }

    sort(pairs.begin(), pairs.end(),
              [](auto& a, auto& b){ return a.distance < b.distance; });

    return pairs;
}

// --- Connect two points into circuits (connected components) ---
pair<int,int> connect(const Point& a, const Point& b, map<Point, SharedCircuit>& circuitsByPoint){
    int connectedChg = 0;
    int circuitsChg = 0;

    bool hasA = circuitsByPoint.contains(a);
    bool hasB = circuitsByPoint.contains(b);

    if ((!hasA && !hasB) || (hasA != hasB)) {
        SharedCircuit circuit =
            hasA ? circuitsByPoint[a] :
            hasB ? circuitsByPoint[b] :
                   std::make_shared<Circuit>();

        circuit->insert(a);
        circuit->insert(b);

        circuitsByPoint[a] = circuit;
        circuitsByPoint[b] = circuit;

        connectedChg++;
        circuitsChg--;
    }
    else {
        // Merge two circuits if different
        auto circuitA = circuitsByPoint[a];
        auto circuitB = circuitsByPoint[b];

        if (circuitA != circuitB) {
            for (const auto& p : *circuitB) {
                circuitA->insert(p);
                circuitsByPoint[p] = circuitA;
            }
            circuitB.reset();
            connectedChg++;
            circuitsChg--;
        }
    }

    return {connectedChg, circuitsChg};
}

long long part1(const std::vector<Point>& points, int connectCount = 1000){
    std::vector<DistancePair> distPairs = sortedPairsByDistance(points);

    if (connectCount > (int)distPairs.size()){
        connectCount = distPairs.size();
    }

    map<Point, SharedCircuit> circuitsByPoint;
    int connected = 0;

    for (int i = 0; i < connectCount; i++){
        const auto& p = distPairs[i];
        auto [chg, _] = connect(p.a, p.b, circuitsByPoint);
        connected += chg;
    }

    // Get unique circuits
    std::set<SharedCircuit> uniqueCircuits;
    for (auto& kv : circuitsByPoint){
        uniqueCircuits.insert(kv.second);
    }

    // Move to vector and sort by size descending
    std::vector<SharedCircuit> circuits(uniqueCircuits.begin(), uniqueCircuits.end());
    std::sort(circuits.begin(), circuits.end(),
              [](const SharedCircuit& a, const SharedCircuit& b){ return a->size() > b->size(); });

    // Take top 3
    circuits.resize(3);

    long long result = 1;
    for (auto& c : circuits){
        result *= static_cast<long long>(c->size());
    }

    return result;
}


int main(){
    vector<Point> points = parseFile("../input.txt");

    cout << "Loaded " << points.size() << " points.\n";

    cout << "Solution: " <<  part1(points) << endl;

    return 0;
}
