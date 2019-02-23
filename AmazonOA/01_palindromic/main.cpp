//
//  main.cpp
//  01_palindromic
//
//  Created by alumi5566 on 2019/2/19.
//  Copyright © 2019 alumi5566. All rights reserved.
//

// 網路資源：
// http://www.cnblogs.com/grandyang/p/4464476.html
// http://www.cnblogs.com/grandyang/p/4475985.html
// https://segmentfault.com/a/1190000003914228
// leetcode #05 https://leetcode.com/problems/longest-palindromic-substring/

#include "../amazonOA/Header.h"

using namespace std;

// this is O(n*n) solution, but faster than Manacher's
string longestPalindrome(string s) {
    const int size_s = s.size();
    int max_s = 0, max_l = 0;
    for (int i = 0; i < size_s;) {
        int start = i, end = i;
        while (end + 1 < size_s && s[end] == s[end+1]) end++;
        i = end + 1;
        while (start - 1 >= 0 && end + 1 < size_s && s[start-1] == s[end+1]) {
            start--;
            end++;
        }
        if (end - start + 1 > max_l) {
            max_l = end - start + 1;
            max_s = start;
        }
    }
    return s.substr(max_s, max_l);
}

// Manacher's
string manacher(string s){
    // Insert '#'
    if (s.empty()) return "";
    string t = "#";
    //string t = "#";
    for (int i = 0; i < s.size(); i++) {
        t += s[i];
        t += "#";
    }
    // Process t
    vector<int> RL(t.size(), 0);
    int maxRight = 0, maxCenter = 0, retLen = 0, retCenter = 0;
    for (int i = 1; i < t.size(); ++i) {
        int mirror = maxCenter - (i - maxCenter);
        RL[i] = maxRight > i ? min(RL[mirror], maxRight - i) : 1;
        // from the know palindromic, extend and update maxRight/maxCenter
        int LHS = i - RL[i], RHS = i + RL[i];
        while (LHS - 1 >= 0 && RHS + 1 < t.size() && t[LHS - 1] == t[RHS + 1]) {
            --LHS;
            ++RHS;
            ++RL[i];
        }
        if (maxRight < i + RL[i]) {
            maxRight = i + RL[i];
            maxCenter = i;
        }
        // update the return value
        if (retLen < RL[i]) {
            retLen = RL[i];
            retCenter = i;
        }
    }
    return s.substr((retCenter - retLen) / 2, retLen);
}

// why $?
string manacher2(string s) {
    // Insert '#'
    string t = "$#";
    for (int i = 0; i < s.size(); ++i) {
        t += s[i];
        t += "#";
    }
    // Process t
    vector<int> p(t.size(), 0);
    int mx = 0, id = 0, resLen = 0, resCenter = 0;
    for (int i = 1; i < t.size(); ++i) {
        p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
        while (t[i + p[i]] == t[i - p[i]]) ++p[i];
        if (mx < i + p[i]) {
            mx = i + p[i];
            id = i;
        }
        if (resLen < p[i]) {
            resLen = p[i];
            resCenter = i;
        }
    }
    return s.substr((resCenter - resLen) / 2, resLen - 1);
}

int main()
{
    cout << "01_Hello World" << endl;
    //string s = "abcba";// return abcba
    string s = "abcbx";// return bcb
    //string s = "xyzzyabc";// return yzzy
    cout << longestPalindrome(s)<<endl;
    cout << manacher(s)<<endl;
    return 0;
}

