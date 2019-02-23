//
//  main.cpp
//  04_MaximumMinimumPath
//
//  Created by alumi5566 on 2019/2/19.
//  Copyright © 2019 alumi5566. All rights reserved.
//

//You are gonna climb mountains represented by a matrix. Each integer in the matrix represents the altitude at that point. You are supposed to climb from the top-left corner to the bottom-right corner and only move rightward or downward in each step.
//You can have many paths to do so. Each path has a minimum altitude. Find the maximum among all the minimum altitudes of all paths.
//e.g.
//  [5, 4, 5]
//  [1, 3, 6]
//
//Three paths: 5 1 3 6，5 4 3 6，5 4 5 6. Minimums are 1, 3, 4 respectively. Return the maximum in them which is 4.

//  [8, 4, 7]
//  [6, 5, 9]
//  3 paths:
//  8-4-7-9 min: 4
//  8-4-5-9 min: 4
//  8-6-5-9 min: 5
//  return: 5


// similiar to leetcode #174. Dungeon Game
// use DFS
// use dp: DP[i][j]: what is the minimal altitudes

#include "../amazonOA/Header.h"
using namespace std;

// 這個縮減table size
int calculateMinimum(vector<vector<int> > matrix) {
    vector<int> result(matrix[0].size());
    // assume keep walk right, reault[i] is the minimal of path (0,0)->(0,i)
    result[0] = matrix[0][0];
    for(int i=1; i<matrix[0].size(); i++){
        result[i] = min(result[i-1], matrix[0][i]);
    }
    // start from first row, calculate the minimal of path (k,0)->(k,i) for k row
    for(int i=1; i<matrix.size(); i++){
        result[0] = min(matrix[i][0], result[0]);
        for(int j=1; j<matrix[0].size(); j++){
            // 
            if(result[j] < matrix[i][j] && result[j-1] < matrix[i][j]){
                result[j] = max(result[j-1], result[j]);
            }else{
                result[j] = matrix[i][j];
            }
        }
        // 
    }
    return result[result.size()-1];
}

// DP
int calculateMinimum2(vector<vector<int> > matrix) {
    if (matrix.size() == 0 || matrix[0].size() == 0) {
        return 0;
    }
    int n = matrix.size();
    int m = matrix[0].size();
    //int[][] dp = new int[n][m];// dp[i,j]路径中最小值 (不过下边有所不同)
    //vector<vector<int> > dp
    vector<vector<int> > dp(matrix.size(),vector<int>(matrix[0].size(), 0));
    dp[0][0] = matrix[0][0];// [0,0] 肯定在考虑点中
    for (int i = 1; i < n; i++) {
        dp[i][0] = min(dp[i - 1][0], matrix[i][0]);
    }
    for (int i = 1; i < m; i++) {
        dp[0][i] = min(dp[0][i - 1], matrix[0][i]);
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            dp[i][j] = min(max(dp[i - 1][j], dp[i][j - 1]),matrix[i][j]);
            // 每次选点的时候,因为路径只可能是从上或者从左, 所以选其中较大的, 再去合当前值比较.即可
        }
    }
    return dp[n - 1][m - 1];
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "04_Hello, World!\n";
    vector<vector<int> > dungeon{ { 5, 4, 5 }, { 1, 3, 6 } };
    // result = 4
    //vector<vector<int> > dungeon{ { 8, 4, 7 }, { 6, 5, 9 } };
    // result = 5
    cout << calculateMinimum2(dungeon) << endl;
    return 0;
}
