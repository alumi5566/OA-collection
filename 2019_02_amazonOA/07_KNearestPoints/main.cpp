//
//  main.cpp
//  07_KNearestPoints
//
//  Created by alumi5566 on 2019/2/19.
//  Copyright © 2019 alumi5566. All rights reserved.
//

#include "../amazonOA/Header.h"
using namespace std;

// The background is to load goods into a truck.
// The truck is at the origin and you are given the coordinates of all goods.
// Find the k nearest goods.
// Use PriorityQueue. Write your own Comparator.

// leetcode #973. K Closest Points to Origin
// 用 自定義的priority queue, 在提取前K個
typedef pair<int, vector<int> > pi;
vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
    priority_queue<pi, vector<pi>, greater<pi> > pq;
    vector<vector<int>> ret;
    for(auto point:points){
        int dist = point[0]*point[0]+point[1]*point[1];
        pq.push({ dist, point});
    }
    for(int i=0;i<K;i++){
        ret.push_back(pq.top().second);
        pq.pop();
    }
    return ret;
}

// 直接sorting O(nlogn), 這個超快
static bool comp(vector<int>& a, vector<int>& b){
    return a[0] * a[0] + a[1] * a[1] < b[0] * b[0] + b[1] * b[1];
}
vector<vector<int>> kClosest2(vector<vector<int>>& points, int K) {
    sort(points.begin(), points.end(), comp);
    return vector<vector<int>>(points.begin(), points.begin() + K);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "07_Hello, World!\n";
//    vector<vector<int>>points = {{1,3},{-2,2}};
//    int K = 1;
    vector<vector<int>>points = {{3,3},{5,-1},{-2,4}};
    int K = 2;
    for(auto v:kClosest2(points, K)){
        cout << "[" << v[0] << " ," << v[1] << "]" << endl;
    }
    return 0;
}
