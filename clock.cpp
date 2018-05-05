#include <iostream>
#include <sys/time.h>        //gettimeofday()
#include <unistd.h>

using namespace std;

/*
 windows常用的time()和clock() 在linux上面會有問題
 用gettimeofday()可以得到當前時間與unix epoch time的差異
 註：epoch time: 00:00:00 Coordinated Universal Time (UTC), Thursday, 1 January 1970
 儲存在
     struct timeval
     {
     __time_t tv_sec;        // Seconds.
    __suseconds_t tv_usec;   // Microseconds.
    };
 裡面 (tv_sec和tv_usec表示同樣一個時間的整數位和微秒數位)
 */

int main() {
    struct timeval tpstart,tpend;
    double timeuse;
    cout<<"this is going to sleep 3 sec"<<endl;
    gettimeofday(&tpstart,NULL);
    //delay(5);
    usleep(3000000);
    gettimeofday(&tpend,NULL);
    timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    cout<< "used time:"<< timeuse<<"us"<<endl;
    cout<< "used time:"<< timeuse/1000<<"ms"<<endl;
    cout<< "used time:"<< (tpend.tv_usec-tpstart.tv_usec)/1000<<"ms"<<endl;
    cout<< "used time:"<< (tpend.tv_sec-tpstart.tv_sec)<<"s"<<endl;
}
