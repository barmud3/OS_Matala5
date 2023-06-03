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

    std::function<void(void*)> myFunc;
    void CreateActiveObject(std::function<void(void*)> func , bool isOB1);
    bool isStopFlag() const;
    ThreadSafeQueue* getQueue();
    void stop();
    static void* Loop(void* arg);
    static void* ThreadFuncWrapper(void* arg);
};








#endif //OS_MATALA5_ACTIVEOBJECT_HPP