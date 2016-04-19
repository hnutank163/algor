#include "ThreadPool.hpp"
#include <unistd.h>

void print(void *arg){
    int *i = (int *)arg;
    cout<<"--- "<<*i<<"---\n";
}

int main(){
    ThreadPool tp;
    int n=8;
    while(n--){
        int *pi = new int(n);
        Task *task = new Task(print, pi);
        tp.add_task(task);
    }
    usleep(1000*1000);
    return 0;
}
