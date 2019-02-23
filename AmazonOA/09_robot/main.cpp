//
//  main.cpp
//  09_robot
//
//  Created by alumi5566 on 2019/2/19.
//  Copyright © 2019 alumi5566. All rights reserved.
//

#include "../amazonOA/Header.h"
using namespace std;

// similar to Leetcode 505. The Maze II
// http://www.cnblogs.com/grandyang/p/6725380.html
// The maze is represented by a binary 2D array. 1 means the wall and 0 means the empty space.
// 球只能一直線衝，直到碰到強才能換方向
// 1. 用dfs，差別在直直衝
int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
    int m = maze.size(), n = maze[0].size();
    vector<vector<int>> dists(m, vector<int>(n, INT_MAX));
    vector<vector<int>> dirs{{0,-1},{-1,0},{0,1},{1,0}};
    queue<pair<int, int>> q;
    q.push({start[0], start[1]});
    dists[start[0]][start[1]] = 0;
    while (!q.empty()) {
        pair<int, int> t = q.front();
        q.pop();
        for (auto d : dirs) {
            int x = t.first, y = t.second, dist = dists[t.first][t.second];
            // for direction d: keep going until hit wall or oob
            while (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == 0) {
                x += d[0];
                y += d[1];
                ++dist;
            }
            // back one step
            x -= d[0];
            y -= d[1];
            --dist;
            // now (x, y) is at some corner
            // see if new dist is less than previous dist[x][y] (we get a better path if so)
            // replace dists[x][y] with dist
            if(dists[x][y] > dist){
                dists[x][y] = dist;
                // is we reach destination, don't push, we don't need to go further from destination
                if (x != destination[0] || y != destination[1])
                    q.push({x, y});
            }
        }
    }
    // at this time, dist[][] saves minimum distance for every location
    // if dists[destination[0]][destination[1]] == INT_MAX, impossible to reach
    int res = dists[destination[0]][destination[1]];
    return (res == INT_MAX) ? -1 : res;
}

// 2. 用Dijkstra
//static bool comp = [](vector<int>& a, vector<int>& b) {
//    return a[2] > b[2];
//};
struct comp{
    bool operator()(vector<int>& a, vector<int>& b){
        return a[2] > b[2];
    }
};
int shortestDistance2(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
    int m = maze.size(), n = maze[0].size();
    vector<vector<int>> dists(m, vector<int>(n, INT_MAX));
    vector<vector<int>> dirs{{0,-1},{-1,0},{0,1},{1,0}};
//    auto cmp = [](vector<int>& a, vector<int>& b) {
//        return a[2] > b[2];
//    };
    // decltype(cmp) => same type as the cmp
    priority_queue<vector<int>, vector<vector<int>>, comp> pq;
    pq.push({start[0], start[1], 0});
    dists[start[0]][start[1]] = 0;
    while (!pq.empty()) {
        vector<int> t = pq.top();
        pq.pop();
        if (dists[t[0]][t[1]] < t[2])
            continue;
        for (auto dir : dirs) {
            int x = t[0], y = t[1], dist = dists[t[0]][t[1]];
            while (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == 0) {
                x += dir[0];
                y += dir[1];
                ++dist;
            }
            x -= dir[0];
            y -= dir[1];
            --dist;
            if (dists[x][y] > dist) {
                dists[x][y] = dist;
                if (x != destination[0] || y != destination[1])
                    pq.push({x, y, dist});
            }
        }
    }
    int res = dists[destination[0]][destination[1]];
    return (res == INT_MAX) ? -1 : res;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "09_Hello, World!\n";
    vector<vector<int>> maza{
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 0, 1, 1},
        {0, 0, 0, 0, 0}
    };
    vector<int> start({0, 4});
    vector<int> stop({4, 4});
//    Output: 12
//    vector<int> start({0, 4});
//    vector<int> stop({3, 2});
//    Output: -1
    cout << shortestDistance(maza, start, stop) << endl;
    cout << shortestDistance2(maza, start, stop) << endl;
    return 0;
}
