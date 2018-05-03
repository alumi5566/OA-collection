
/*
Game Result Prediction

Problem Statement
Assume you are working on a project to compare a bunch of sports teams. 
To simplify the problem, let・s assume, all teams・ performance rankings are constant, so a strong team will always beat the weak team. And the input data is always correct.

The history statistics of game results are input as 'game(A op B)', op can be >, = or < to indicate the game result. 
The user would like to predict two teams・ game result and the prediction has 4 cases: A > B, or A < B, or ? (we cannot tell), or A = B. 
For example,
Given
game(A>B); game(B>C); game(B>D); game(A=E)
Then
predict(A,B) returns ．>'
predict(B,A) returns '<'
predict(A,C) returns '>'   (transitivity applies)
predict(C,D) returns '?'
predict(A,E) returns '='
predict(E,B) returns ．>・

1. Please provide a coding solution to this problem. Add some test cases if time permits.
2. (Optional) if you have more time, please check the solution to make it a library where multiple threads can add game history during runtime. And user may query the prediction result in different threads also. Code snippet or write up are both acceptable.
*/
//emma.xiu@oracle.com

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include<unordered_map>
#include <algorithm>
#include <sstream>
using namespace std;

void dumpTable(unordered_map<string,set<string>> table){
  for(auto it = table.begin();it!=table.end();++it){
    cout << it->first <<": ";
    set<string> s = it->second;
    for(auto it2 = s.begin();it2!=s.end();++it2)
      cout << *it2 << " ";
    cout << endl;
  }
  cout << endl;  
}

// To execute C++, please define "int main()"
int main() {

  vector <string> contain;
  unordered_map<string,set<string>> WINtable;
  unordered_map<string,set<string>> LOSEtable;
  unordered_map<string,set<string>> EQUALtable;
  vector <string> candidate;
  string inputS;
  //cin >> inputS;
  // keep these two lines
  //getline(cin,inputS);
  //cout<<inputS<<endl;
  //inputS = "game(A>B); game(B>C); game(B>D); game(A=E)";
  inputS = "game(A>B); game(B>C); game(B>D); game(A=E)";
  for(int i=0;i<inputS.size();i++){
    string symb = inputS.substr(i,1);
    //cout << symb;
    string p1;
    string p2;
    if(symb == ">" || symb == "<" || symb == "="){
      p1 = inputS[i-1];
      p2 = inputS[i+1];
      cout<<"("<<p1<<","<<p2<<") "<<endl;
    }
    if(symb == ">" || symb == "<"){
      if(symb == "<")
          swap(p1,p2);
      // 1. WINtable
      set<string> s;
      s.insert(p2);
      auto it = WINtable.find(p1);
      if(it != WINtable.end()){  // find one!!
        s = it->second;
        s.insert(p2);
        WINtable[p1] = s;
        //WINtable.insert(pair<string,set<string>>(p1,s));
      }else{
        WINtable.insert(pair<string,set<string>>(p1,s));
      }
      // 2. LOSEtable
      set<string> s2;
      s2.insert(p1);
      it = LOSEtable.find(p2);
      if(it != LOSEtable.end()){  // find one!!
        s2 = it->second;
        s2.insert(p1);
        LOSEtable[p2] = s2;
        //WINtable.insert(pair<string,set<string>>(p1,s));
      }else{
        LOSEtable.insert(pair<string,set<string>>(p2,s2));
      }
      //3. Check LOSEtable if p1 lose anyone?
      it = LOSEtable.find(p1);
      if(it != LOSEtable.end()){  // find one!!
        set<string> s3 = it->second;
        for(auto it = s3.begin();it!=s3.end();++it){// for every p1 lose, p2 also lose
          // a. add p2 to these winner's list
          string winner = *it;
          WINtable[winner].insert(p2);
          // b. add there winner to p2's lost list
          LOSEtable[p2].insert(winner);
        }
        //LOSEtable[p2] = s2;
        //WINtable.insert(pair<string,set<string>>(p1,s));
      }      
      
    }else if(symb == "="){
      // simply copy WINtable of p1 to p2
      string source;
      string destiny;
      if( WINtable.find(p1)!=WINtable.end()){
        auto it = WINtable.find(p1);
        set<string> s = it->second;
        WINtable.insert(pair<string,set<string>>(p2,s));
        source = p1;
        destiny = p2;
      }else if(WINtable.find(p2)!=WINtable.end()){
        auto it = WINtable.find(p2);
        set<string> s = it->second;
        WINtable.insert(pair<string,set<string>>(p1,s));
        source = p2;
        destiny = p1;
      }else{
        cout<<"something wrong"<<endl;
      }
      // in LOSEtable, for every player lose p1, add p2 to their list
      for(auto it2 = WINtable[source].begin();it2!=WINtable[source].end();++it2){
        LOSEtable[*it2].insert(destiny);
      }
      // add both into UQUALtable
      // add p1
      auto it = EQUALtable.find(p1);
      set<string> s;
      s.insert(p2);
      if(it != EQUALtable.end()){
        EQUALtable[p1].insert(p2);
      }else{
        EQUALtable.insert(pair<string,set<string>>(p1,s));
      }
      // add p2
      it = EQUALtable.find(p2);
      set<string> s2;
      s2.insert(p1);
      if(it != EQUALtable.end()){
        EQUALtable[p2].insert(p1);
      }else{
        EQUALtable.insert(pair<string,set<string>>(p2,s2));
      }
    }
  }
  // finish building table
  cout<<"WINtable:"<<endl;
  dumpTable(WINtable);
  cout<<"LOSEtable:"<<endl;
  dumpTable(LOSEtable);
  cout<<"EQUALtable:"<<endl;
  dumpTable(EQUALtable);
  
  //getline(cin,inputS);
  //cout<<inputS<<endl;
  vector<string> inputS2 = {"predict(A,B)","predict(B,A)","predict(A,C)","predict(C,D)",
            "predict(A,E)","predict(E,B)"};
  for(int i=0;i<inputS2.size();i++){
    //cout<<inputS2[i]<<endl;
    string p1 = inputS2[i].substr(8,1);
    string p2 = inputS2[i].substr(10,1);
    cout<<"("<<p1<<","<<p2<<") ";
    // check EQUALtable first
    auto it = EQUALtable.find(p1);
    if(it != EQUALtable.end()){
      set<string> s = it->second;
      if(s.find(p2) != s.end()){
        cout<<" ="<<endl;
        goto EQUALnEND;
      }
    }
    // check WINtable
    it = WINtable.find(p1);
    if(it != WINtable.end()){  // find one!!
      set<string> s = it->second;
      if(s.find(p2) != s.end()){
        cout<<" >"<<endl;
      }else{
        cout<<" <"<<endl;
      }
    }else{
      cout<<" ?"<<endl;
    }
EQUALnEND:;
  // this label used when we got a equal and wanna skip the cmp part  
  }

  
  return 0;
}


