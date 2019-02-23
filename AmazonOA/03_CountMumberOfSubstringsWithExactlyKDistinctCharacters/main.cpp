//
//  main.cpp
//  03_CountMumberOfSubstringsWithExactlyKDistinctCharacters
//
//  Created by alumi5566 on 2019/2/19.
//  Copyright © 2019 alumi5566. All rights reserved.
//

// leetcode #340
// for a given string, within all substring, how many are there contains k-distinct char
// solution: use a table[26] to store 'a'-'z'


#include "../amazonOA/Header.h"
using namespace std;

// 這個比較爛，用 O(n*n)
int countkDist(string str, int k){
    int ret = 0;
    int len = str.size();
    // for str[i:j], use table v to calculate freq of each ch
    for(int i=0;i<len;i++){
        int dist_count = 0;
        vector<int> v(26,0);
        
        for(int j=i;j<len;j++){
            if(v[str[j] - 'a'] == 0){
                dist_count++;
            }
            v[str[j] - 'a']++;
            if (dist_count == k)
                ret++;
            if(dist_count > k){
                break;
            }
        }
    }
    return ret;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "03_Hello, World!\n";
    string str = "abcbaa";
    int k = 3;
    // Total substrings with exactly 3 distinct characters : 8
    cout << "Total substrings with exactly "
    << k <<" distinct characters :"
    << countkDist(str, k) << endl;
    return 0;
}
