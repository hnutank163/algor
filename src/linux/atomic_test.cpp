#include <atomic>
#include <boost/thread.hpp>
#include <boost/timer.hpp>

using namespace std;
using namespace boost;
pthread_mutex_t mutex_;
pthread_spinlock_t spin;
//std::atomic_long l(0) ;
long l;

void click()
{
    for(int i=0; i<10000000; ++i)
    {
        //m.lock();
        //pthread_mutex_lock(&mutex_);
        //pthread_spin_lock(&spin);
        __sync_add_and_fetch(&l,1);
        //++l;
        //pthread_mutex_unlock(&mutex_);
        //pthread_spin_unlock(&spin);
        //m.unlock();
    }
}

int main(){
    boost::timer tm;
    boost::thread_group threads;
    pthread_mutex_init(&mutex_, NULL);
    pthread_spin_init(&spin, 0);
    for(int i=0 ;i<5; ++i)
        threads.create_thread(click);
    threads.join_all();
    cout<<tm.elapsed()<<endl;
    return 0;
}
