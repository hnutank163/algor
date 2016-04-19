#ifndef _THREAD_POOL_HPP
#define _THREAD_POLL_HPP
#include <cstdlib>
#include <cstdio>
#include <deque>
#include <vector>
#include <iostream>
#include <cstring>
#include <pthread.h>
#include <errno.h>
#include <error.h>

using namespace std;

class Task{
private:
    void (*m_func_ptr)(void *);
    void *m_arg;

public:
    explicit Task( void(*func_ptr)(void *), void *arg ): m_func_ptr(func_ptr), m_arg(arg){

    }

    void run(){
        this->m_func_ptr(m_arg);
    }

    void operator() (){
        this->m_func_ptr(m_arg);
    }
};

class ThreadPool{
private:
    int poolSize;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    vector<pthread_t> pthreads;
    deque<Task *> tasks;
    bool state;
    void excute_thread(){
        Task *task = NULL;

        while(true){
            cout<<"waiting for task\n";
            pthread_mutex_lock(&mutex);
            while( state == true && tasks.empty()){
                pthread_cond_wait(&cond, &mutex);
            }

            if( !state){
                cout<<"unlock and exiting "<<pthread_self()<<endl;
                pthread_mutex_unlock(&mutex);
                pthread_exit(NULL);
            }
            task = tasks.front();
            tasks.pop_front();
            pthread_mutex_unlock(&mutex);
            task->run();
            delete task;
        }
    }

public:
    ThreadPool(int size=5):poolSize(size), state(true){
        initial();
    }

    ~ThreadPool(){
        if(state)
            destory();
    }

    static void * start_thread(void *arg){
        ThreadPool *tp = (ThreadPool *)arg;
        tp->excute_thread();
        return NULL;
    }

    void initial(){
        try{
            int ret;
            ret = pthread_mutex_init(&mutex,NULL);
            if( ret)
            {
                perror("mutext init");
                exit(ret);
            }

            ret = pthread_cond_init(&cond,NULL);
            if(ret){
                perror("cond init");
                exit(ret);
            }

            pthread_t tid;
            for(int i=0; i<poolSize; ++i)
            {
                ret = pthread_create(&tid, NULL, ThreadPool::start_thread, this);
                if(ret){
                    perror("pthread_create");
                    exit(ret);
                }
                pthreads.push_back(tid);
            }
        }
        catch(std::exception &e){
            cout<<e.what()<<endl;
            exit(1);
        }
    }

    void destory(){
        pthread_mutex_lock(&mutex);
        state = false;
        pthread_mutex_unlock(&mutex);

        cout<<"broadcast all threads stop\n";
        pthread_cond_broadcast(&cond);
        int ret ;

        for(int i=0; i<poolSize; ++i){
            void *result;
            ret = pthread_join(pthreads[i] ,&result);
            cout<<"pthread_join "<<ret<<" "<<strerror(errno)<<endl;
            pthread_cond_broadcast(&cond);
        }
        cout<<poolSize<<" threads exit "<<endl;
    }

    void add_task(Task *task){
        pthread_mutex_lock(&mutex);
        tasks.push_back(task);
        pthread_mutex_unlock(&mutex);
        pthread_cond_broadcast(&cond);
    }
};

#endif
