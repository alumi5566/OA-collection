#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sys/time.h>        //gettimeofday()
#include <map>

#define N 5
using namespace std;

int main() {
    vector<string> addTable;
    vector<string> subTable;
    int count = 0;
    struct timeval tpstart,tpend;
    double timeuse;
    map<double, string> timeTAble;
    
    while(count!=N){
        int num1 = rand()%9+1;
        int num2 = rand()%9+1;
        int flag = rand()%2;
        int answer;
        string s;
        gettimeofday(&tpstart,NULL);
        
        if(flag){ // +
            s = to_string(num1)+to_string(num2);
            while(find(addTable.begin(),addTable.end(),s) != addTable.end()){
                num1 = rand()%9+1;
                num2 = rand()%9+1;
                s = to_string(num1)+to_string(num2);
            }
            s = to_string(num1)+to_string(num2);
            addTable.push_back(s);
            //cout << "n1="<<num1<<"+n2="<<num2<<endl;
            cout <<num1<<"+"<<num2<<endl;
            cin >> answer;
            while(answer != num1+num2){
                //cout << "n1="<<num1<<"+n2="<<num2<<endl;
                cout <<num1<<"+"<<num2<<endl;
                cin >> answer;
            }
        }else{ //-
            string s = to_string(num1)+to_string(num2);
            while(find(subTable.begin(),subTable.end(),s) != subTable.end()){
                num1 = rand()%9+1;
                num2 = rand()%9+1;
                s = to_string(num1)+to_string(num2);
            }
            s = to_string(num1)+to_string(num2);
            subTable.push_back(s);
            //cout << "n1="<<num1<<"-n2="<<num2<<endl;
            cout <<num1<<"-"<<num2<<endl;
            cin >> answer;
            while(answer != num1-num2){
                //cout << "n1="<<num1<<"-n2="<<num2<<endl;
                cout <<num1<<"-"<<num2<<endl;
                cin >> answer;
            }
        }
        gettimeofday(&tpend,NULL);
        timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
        //cout<< "used time:"<< timeuse<<"us"<<endl;
        cout<< "used time:"<< (tpend.tv_sec-tpstart.tv_sec)<<"s"<<endl;
        if(flag){
            string s2 = to_string(num1)+"+"+to_string(num2);
            timeTAble.insert(make_pair<double,string>(timeuse,s2));
        }else{
            string s2 = to_string(num1)+"-"+to_string(num2);
            timeTAble.insert(make_pair<double,string>(timeuse,s2));
        }
        //timeTAble.insert(make_pair<double,string>(timeuse,s));
        count++;
    }
    int rank = 0;
    for(auto it=timeTAble.begin();it!=timeTAble.end();++it){
        if(rank <= 5){
            cout <<"rank:"<<rank+1<< "time: "<< it->first << "ns;  Q:" << it->second<<endl;
        }
        rank++;
    }
}
