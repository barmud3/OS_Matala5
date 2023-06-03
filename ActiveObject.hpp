#ifndef OS_MATALA5_ACTIVEOBJECT_HPP
#define OS_MATALA5_ACTIVEOBJECT_HPP

#include <iostream>
#include <queue>
#include <pthread.h>
#include <functional>
#include <iostream>
#include "ThreadSafeQueue.hpp"
using namespace std;
class ActiveObject{

private:

    ThreadSafeQueue* myQueue;
    pthread_t thread;
    bool stopFlag;

public:
    string name;
    std::function<void(void*)> myFunc;
    void CreateActiveObject(std::function<void(void*)> func , int OBNum , string name);
    bool isStopFlag() const;
    ThreadSafeQueue* getQueue();
    void stop();
    void joinThread();
    static void* Loop1(void* arg);
    static void* Loop2(void* arg);
    static void* Loop3(void* arg);
    static void* Loop4(void* arg);
    
};








#endif //OS_MATALA5_ACTIVEOBJECT_HPP
