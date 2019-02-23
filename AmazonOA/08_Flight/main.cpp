//
//  main.cpp
//  08_Flight
//
//  Created by alumi5566 on 2019/2/19.
//  Copyright © 2019 alumi5566. All rights reserved.
//
// geelforgeek https://www.geeksforgeeks.org/given-two-sorted-arrays-number-x-find-pair-whose-sum-closest-x/

#include "../amazonOA/Header.h"
using namespace std;


// 這題就是 Closest Two Sum

static bool comp(vector<int>& a, vector<int>& b){
    return a[1] < b[1];
}

vector<vector<int>> flight(int dist,vector<vector<int>>&in,vector<vector<int>>&out){
    sort(in.begin(), in.end(), comp);
    sort(out.begin(), out.end(), comp);
    unordered_map<int, vector<int>> mIn, mOut;
//    for(auto _in:in)
//        cout << "[" << _in[0] << " , " << _in[1] << "]" << endl;
//    for(auto _out:out)
//        cout << "[" << _out[0] << " , " << _out[1] << "]" << endl;
    int RHS = in.size()-1, LHS = 0;
    int ret_L, ret_R;
    vector<vector<int>> ret;
    int diff = INT_MAX;
    while(RHS >= 0 && LHS < out.size()){
        if(in[RHS][1] + out[LHS][1] == dist){
            diff = 0;
            ret_L = LHS;
            ret_R = RHS;
            break;
        }
        if( abs(in[RHS][1] + out[LHS][1] - dist) < diff && in[RHS][1] + out[LHS][1] < dist){
            ret.clear();
            diff = abs(in[RHS][1] + out[LHS][1] - dist);
            ret_L = LHS;
            ret_R = RHS;
        }else if(abs(in[RHS][1] + out[LHS][1] - dist) == diff){
            ret_L = LHS;
            ret_R = RHS;
            ret.push_back({in[RHS][1], out[LHS][1]});
        }
        
        if(in[RHS][1] + out[LHS][1] > dist){
            RHS--;
        }else if(in[RHS][1] + out[LHS][1] < dist){
            LHS++;
        }
    }
    cout << "diff:" <<diff << endl;
    cout << in[ret_R][0] << "," << out[ret_L][0] << endl;
    // at this time, diff is our best solution
    //if(diff == 0){
        ret.clear();
        for(auto _in:in)
            mIn[_in[1]].push_back(_in[0]);
        for(auto _out:out)
            mOut[_out[1]].push_back(_out[0]);
        for(auto m:mIn){
            // m and mOut has a match pair, go through both vector to collect the result
            if(mOut[diff + dist - m.first].size() != 0){
                for(auto _m:m.second)
                    for(auto _n:mOut[diff + dist - m.first])
                        ret.push_back({_m, _n});
            }
        }
    //}
    return ret;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "08_Hello, World!\n";
//    int dist = 7000;
//    vector<vector<int>> forward{{1,2000}, {2,4000}, {3,8000}};
//    vector<vector<int>> backward{{1,2000}};
    // output = [[2,1]]
    int dist = 10000;
    vector<vector<int>> forward{{1,3000}, {2,5000}, {3,7000}, {4,10000}};
    vector<vector<int>> backward{{1,2000}, {2,3000}, {3,4000}, {4,5000}};
    // output = [[2,4], [3,2]]
    for(auto v:flight(dist, forward, backward)){
        cout << "[" << v[0] << " , " << v[1] << "]" << endl;
    }
    return 0;
}
