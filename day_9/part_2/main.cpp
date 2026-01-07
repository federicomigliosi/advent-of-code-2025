#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

// -----------------------------------------------------------------------------
// Type aliases
// -----------------------------------------------------------------------------
using PointLL = array<long long, 2>;  // Original coordinates
using Point   = array<int, 2>;        // Compressed coordinates
using Grid    = vector<vector<int>>;

// -----------------------------------------------------------------------------
// Coordinate compression
// Preserves the original order of points
// -----------------------------------------------------------------------------
vector<Point> compressCoordinates(const vector<PointLL>& points) {
    set<long long> uniqueRows;
    set<long long> uniqueCols;

    for (const auto& p : points) {
        uniqueRows.insert(p[0]);
        uniqueCols.insert(p[1]);
    }

    vector<Point> compressed;
    compressed.reserve(points.size());

    for (const auto& p : points) {
        int r = distance(uniqueRows.begin(), uniqueRows.find(p[0]));
        int c = distance(uniqueCols.begin(), uniqueCols.find(p[1]));
        compressed.push_back({r, c});
    }

    return compressed;
}

// -----------------------------------------------------------------------------
// Build a grid and mark the polygon edges
// -----------------------------------------------------------------------------
Grid buildGrid(const vector<Point>& points) {
    int maxRow = 0;
    int maxCol = 0;

    for (const auto& p : points) {
        maxRow = max(maxRow, p[0]);
        maxCol = max(maxCol, p[1]);
    }

    Grid grid(maxRow + 1, vector<int>(maxCol + 1, 0));

    // Draw lines between consecutive points
    for (size_t i = 1; i < points.size(); ++i) {
        int dr = points[i][0] - points[i - 1][0];
        int dc = points[i][1] - points[i - 1][1];

        int stepR = (dr == 0) ? 0 : dr / abs(dr);
        int stepC = (dc == 0) ? 0 : dc / abs(dc);

        Point current = points[i - 1];
        while (current != points[i]) {
            grid[current[0]][current[1]] = 1;
            current[0] += stepR;
            current[1] += stepC;
        }
    }

    return grid;
}

// -----------------------------------------------------------------------------
// Flood fill from outside the polygon
// Marks reachable empty space as filled
// -----------------------------------------------------------------------------
void floodFill(Grid& grid) {
    // Find a starting point outside the polygon
    int startRow = 0;
    while (startRow < grid.size() && grid[startRow][0] == 0) {
        startRow++;
    }

    queue<Point> q;
    q.push({startRow + 1, 1});

    const vector<Point> directions = {
        { 1,  0},
        {-1,  0},
        { 0,  1},
        { 0, -1}
    };

    while (!q.empty()) {
        Point cur = q.front();
        q.pop();

        grid[cur[0]][cur[1]] = 2;

        for (const auto& d : directions) {
            Point next{cur[0] + d[0], cur[1] + d[1]};

            if (next[0] >= 0 && next[0] < grid.size() &&
                next[1] >= 0 && next[1] < grid[0].size() &&
                grid[next[0]][next[1]] == 0) {

                grid[next[0]][next[1]] = -1;
                q.push(next);
            }
        }
    }
}

// -----------------------------------------------------------------------------
// Check if a rectangle is completely filled (no zeros inside)
// -----------------------------------------------------------------------------
bool isFilledRectangle(const Grid& grid, const Point& a, const Point& b) {
    int rMin = min(a[0], b[0]);
    int rMax = max(a[0], b[0]);
    int cMin = min(a[1], b[1]);
    int cMax = max(a[1], b[1]);

    for (int r = rMin; r <= rMax; ++r) {
        for (int c = cMin; c <= cMax; ++c) {
            if (grid[r][c] == 0) {
                return false;
            }
        }
    }
    return true;
}

// -----------------------------------------------------------------------------
// Find the largest valid rectangle using original coordinates
// -----------------------------------------------------------------------------
size_t findLargestRectangle(
    const Grid& grid,
    const vector<Point>& compressed,
    const vector<PointLL>& original) {

    size_t bestArea = 0;

    for (size_t i = 0; i < original.size(); ++i) {
        for (size_t j = 0; j < original.size(); ++j) {

            if (!isFilledRectangle(grid, compressed[i], compressed[j])) {
                continue;
            }

            size_t height = abs(original[i][0] - original[j][0]) + 1;
            size_t width  = abs(original[i][1] - original[j][1]) + 1;

            bestArea = max(bestArea, height * width);
        }
    }

    return bestArea;
}


int main() {
    ifstream file("../input.txt");
    vector<PointLL> points;
    string line;

    while (getline(file, line)) {
        size_t comma = line.find(',');
        long long r = stoll(line.substr(0, comma));
        long long c = stoll(line.substr(comma + 1));
        points.push_back({r, c});
    }

    // Close the polygon
    points.push_back(points.front());

    auto compressed = compressCoordinates(points);
    auto grid = buildGrid(compressed);

    floodFill(grid);

    cout << findLargestRectangle(grid, compressed, points) << '\n';
    return 0;
}
