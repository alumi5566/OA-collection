//
//  main.cpp
//  14_MST
//
//  Created by alumi5566 on 2019/2/20.
//  Copyright © 2019 alumi5566. All rights reserved.
//

#include "../amazonOA/Header.h"
using namespace std;

static bool comp(pair< vector<int>, int>& a, pair< vector<int>, int>& b){
    return a.second < b.second;
}
//void prime(int city, int rules, vector< pair< vector<int>, int> > &v){
//    // s: city added
//    unordered_set<int> s;
//    sort(v.begin(), v.end(), comp);
//    for(auto _v:v){
//        cout << _v.first[0] << " , " << _v.first[1] << " , " << _v.second <<endl;
//    }
//    int pivot = 0;
//    vector< pair< vector<int>, int> > ret; // this records the MST
//    while(s.size() != city && pivot != rules){
//        pair< vector<int>, int> p = v[pivot];
//        if(s.find(p.first[0]) != s.end() && s.find(p.first[1]) != s.end()){
//            pivot++;
//            continue;
//        }
//        s.insert(p.first[0]);
//        s.insert(p.first[1]);
//        ret.push_back(v[pivot]);
//    }
//    cout << "output:" << endl;
//    for(auto _v:ret){
//        cout << _v.first[0] << " , " << _v.first[1] << " , " << _v.second <<endl;
//    }
//}
int minKey(vector<int> key, vector<bool> mstSet, int city)
{
    // Initialize min value
    int min = INT_MAX, min_index;
    for (int v = 0; v < city; v++){
        if (mstSet[v] == false && key[v] < min){
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void prime(int city, int rules, vector< pair< vector<int>, int> > &v){
    vector< vector<int>> table(city, vector<int>(city, 0));
    for(auto _v : v){
        table[_v.first[0]-1][_v.first[1]-1] = _v.second;
        table[_v.first[1]-1][_v.first[0]-1] = _v.second;
    }
    // Array to store constructed MST
    vector<int> parent(city, -1);
    // Key values used to pick minimum weight edge in cut
    vector<int> key(city, INT_MAX);
    // To represent set of vertices not yet included in MST
    vector<bool> mstSet(city, false);
    // Always include first 1st vertex in MST.
    // Make key 0 so that this vertex is picked as first vertex.
    key[0] = 0;
    parent[0] = -1; // First node is always root of MST
    
    for(int count = 0; count < city-1; count++){
        int u = minKey(key, mstSet, city);
        mstSet[u] = true;
        for (int v = 0; v < city; v++)
            // graph[u][v] is non zero only for adjacent vertices of m
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]
            if (table[u][v] && mstSet[v] == false && table[u][v] < key[v]){
                parent[v] = u;
                key[v] = table[u][v];
            }
    }
    
    cout << "Edge \tWeight" << endl;
    for (int i = 1; i < city; i++)
        cout << parent[i]+1 << " - " << i+1 << " " << table[i][parent[i]] << endl;
//        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "14_Hello, World!\n";
    int i = 5,j = 8;
    // pair: [ [cityA, cityB], distance ]
    vector< pair< vector<int>, int> > v;
    v.push_back({ {1, 2}, 2});
    v.push_back({ {2, 5}, 9});
    v.push_back({ {5, 4}, 7});
    v.push_back({ {4, 1}, 10});
    v.push_back({ {1, 3}, 12});
    v.push_back({ {4, 3}, 6});
    v.push_back({ {5, 3}, 3});
    v.push_back({ {2, 3}, 8});
    prime(i, j, v);
    return 0;
}
