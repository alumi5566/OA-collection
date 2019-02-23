//
//  main.cpp
//  11_ReorderLogFiles
//
//  Created by alumi5566 on 2019/2/20.
//  Copyright © 2019 alumi5566. All rights reserved.
//

#include "../amazonOA/Header.h"
using namespace std;

// leetcode #937 https://leetcode.com/problems/reorder-log-files/
// 快速寫法: https://zxi.mytechroad.com/blog/string/leetcode-937-reorder-log-files/

// 自己寫的
bool myfunction(const string i,const string j){
    string s1 = i.substr(i.find(" ")+1,i.size()-i.find(" "));
    string s2 = j.substr(j.find(" ")+1,j.size()-j.find(" "));
    return (s1<s2);
}
struct myclass {
    bool operator() (string i,string j) {
        string s1 = i.substr(i.find(" ")+1,i.size()-i.find(" "));
        string s2 = j.substr(j.find(" ")+1,j.size()-j.find(" "));
        return (s1<s2);
    }
} myobject;
vector<string> reorderLogFiles(vector<string>& logs) {
    vector<string> let;
    vector<string> num;
    for(int i=0;i<logs.size();i++){
        int pos = logs[i].find(" ");
        char c = logs[i][pos+1];
        if(c>='0' && c<='9'){
            num.push_back(logs[i]);
        }else{
            let.push_back(logs[i]);
        }
    }
    std::sort(let.begin(), let.end(), myobject);
    for(int i=0;i<num.size();i++)
        let.push_back(num[i]);
    return let;
}

// 快速寫法
vector<string> reorderLogFiles2(vector<string>& logs) {
    auto alpha_end = std::stable_partition(begin(logs),  end(logs),[](const string& log){
        return isalpha(log.back());
    });
    std::sort(begin(logs), alpha_end, [](const string& a, const string& b){
        return a.substr(a.find(' ')) < b.substr(b.find(' '));
    });
    return logs;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "11_Hello, World!\n";
    vector<string> logs{
        {"a1 9 2 3 1"},
        {"g1 act car"},
        {"zo4 4 7"},
        {"ab1 off key dog"},
        {"a8 act zoo"}
    };
    for(auto s:reorderLogFiles(logs)){
        cout << s << endl;
    }
    
    return 0;
}
