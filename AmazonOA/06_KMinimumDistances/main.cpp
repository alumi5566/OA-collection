//
//  main.cpp
//  06_KMinimumDistances
//
//  Created by alumi5566 on 2019/2/19.
//  Copyright © 2019 alumi5566. All rights reserved.
//

// 這題用 BFS，BFS 大致上都用queue，但是有分iterative 或是 recursive
// 有空複習一下 DFS 的 iterative 和 recursive
// 和這題很像，用BFS: https://www.geeksforgeeks.org/shortest-distance-two-cells-matrix-grid/
// 和這題也很像，用BFS: https://www.geeksforgeeks.org/find-shortest-distance-guard-bank/
// BFS的兩種寫法: https://www.techiedelight.com/breadth-first-search/
// number of island: 用BFS和DFS都可以: http://www.gohired.in/2018/04/05/number-of-islands-bfs-dfs/


#include "../amazonOA/Header.h"
using namespace std;

//int ret = 0;
class QItem {
public:
    int row;
    int col;
    int dist;
    QItem(int x, int y, int w)
    : row(x), col(y), dist(w)
    {
    }
};

int BFS(vector<vector<int>> matrix){
    // label all '0' as visited
    vector<vector<bool>> visited(matrix.size(), vector<bool>(matrix[0].size(), false));
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++)
        {
            if (matrix[i][j] == 0)
                visited[i][j] = true;
            else
                visited[i][j] = false;
        }
    }
    
    queue<QItem> q;
    QItem source(0, 0, 0);
    q.push(source);
    visited[0][0] = true;

    while(!q.empty()){
        QItem p = q.front();
        q.pop();
        if (matrix[p.row][p.col] == 9)
            return p.dist;
        
        // moving up
        if (p.row - 1 >= 0 && !visited[p.row - 1][p.col]) {
            q.push(QItem(p.row - 1, p.col, p.dist + 1));
            visited[p.row - 1][p.col] = true;
        }
        // moving down
        if (p.row + 1 < matrix.size() && !visited[p.row + 1][p.col]) {
            q.push(QItem(p.row + 1, p.col, p.dist + 1));
            visited[p.row + 1][p.col] = true;
        }
        // moving left
        if (p.col - 1 >= 0 && !visited[p.row][p.col - 1]) {
            q.push(QItem(p.row, p.col - 1, p.dist + 1));
            visited[p.row][p.col - 1] = true;
        }
        // moving right
        if (p.col + 1 < matrix[0].size() && !visited[p.row][p.col + 1]) {
            q.push(QItem(p.row, p.col + 1, p.dist + 1));
            visited[p.row][p.col + 1] = true;
        }
    }
    return -1;
}

int removeOb(int row, int col, vector<vector<int>> matrix){
    int ret = BFS(matrix);
    return ret;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "06_Hello, World!\n";
//    vector<vector<int> > matrix{ { 1, 0, 0 }, { 1, 0, 0 }, { 1, 9, 1 } };
    // output: 3
    vector<vector<int> > matrix{ { 1, 1, 1, 1 }, { 0, 1, 1, 1 },
        { 0, 1, 0, 1 }, { 1, 1, 9, 1 }, { 0, 0, 1, 1 }};
    // output: 5
    cout << removeOb(3,3,matrix) <<endl;
    return 0;
}
