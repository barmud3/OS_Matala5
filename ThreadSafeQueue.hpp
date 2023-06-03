#ifndef OS_MATALA5_THREADSAFEQUEUE_HPP
#define OS_MATALA5_THREADSAFEQUEUE_HPP
#include <queue>
#include <mutex>
#include <condition_variable>
#include <iostream>
using namespace std;

class ThreadSafeQueue{

private:

    bool stopFlag;
    std::mutex mtx;             // Mutex for protecting the queue
    std::condition_variable cv; // Condition variable for waiting on the queue
    std::queue<void*> myQueue;  // Queue to hold void pointers
    

public:
    string name;
    ThreadSafeQueue() : stopFlag(false) {}
    void Enqueue(void* task);
    void* Dequeue();
    void Stop();

    std::condition_variable stopCV;
};




#endif //OS_MATALA5_THREADSAFEQUEUE_HPP
