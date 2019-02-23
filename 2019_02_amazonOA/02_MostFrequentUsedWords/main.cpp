//
//  main.cpp
//  02_MostFrequentUsedWords
//
//  Created by alumi5566 on 2019/2/19.
//  Copyright © 2019 alumi5566. All rights reserved.
//

// You are given a sentence string and a list with words to exclude.
// Find the most frequent used words in the sentence but not in the words-to-exclude list.
// input: "Jack and Jill went to the market to buy bread and cheese. Cheese is Jack's and Jill's favority food."
// ["and", "he", "the", "to", "is", "Jack", "Jill"].
// return: ["cheese", "s"]

// leetcode #819 https://leetcode.com/problems/most-common-word/discuss/184971/C%2B%2B-4ms-straightforward-solution

#include "../amazonOA/Header.h"

using namespace std;

//string mostCommonWord(string paragraph, vector<string>& banned) {
vector<string> mostCommonWord(string paragraph, vector<string>& banned) {
    unordered_map<string, int>m;
    unordered_set<string>s;
    // pre-processing: turn to lower case and eliminate special ch
    string _paragraph = "";
    for(int i=0;i<paragraph.size();i++){
        if(isalpha(paragraph[i])){
            _paragraph += tolower(paragraph[i]);
        }else{
            _paragraph += ' ';
        }
    }
    // buld table s for banned
    for(int i=0;i<banned.size();i++){
        s.insert(banned[i]);
    }
    // build table m for  _paragraph
    istringstream iss(_paragraph);
    string word;
    // for every word in _paragraph
    while(iss >> word){
        if(s.find(word) == s.end()){
            m[word]++;
        }
    }
    
    // go through table and get max freq result
    int maxFreq = 0;
    string ret="";
    for(auto it=m.begin();it!=m.end();++it){
        if(it->second>=maxFreq){
            maxFreq = it->second;
            ret = it->first;
        }
    }
    vector<string> ret2;
    for(auto w: m){
        if(w.second == maxFreq){
            ret2.push_back(w.first);
        }
    }
    return ret2;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "02_Hello, World!\n";
    // for unique output
    string paragraph = "Bob hit a ball, the hit BALL flew far after it was hit.";
    vector<string> banned{"hit"};
    // Output: "ball"
    
    // for multiple output
    string sentence = "jack and jill went to the market to buy bread and cheese. cheese is jack's and jill's favorite food.";
    vector<string> excluded = {"and", "he", "the", "to", "is"};
    // vector<string> expected = {"cheese", "jack", "jill", "s"};
    for(auto w:mostCommonWord(sentence, excluded))
        cout << w << endl;
    return 0;
}
