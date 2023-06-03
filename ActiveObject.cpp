#include "ActiveObject.hpp"

int ActiveObject::counter = -1;
bool ActiveObject::stopFlag = false;

void ActiveObject::joinThread(){

    pthread_join(this->thread, nullptr);

}

void ActiveObject::CreateActiveObject(std::function<void(void*)> func , int OBNum , string name) {
    myQueue = new ThreadSafeQueue();
    this->name = name;
    this->myFunc = func;
    stopFlag = false;
    int result= 0;
    if (OBNum == 1) //AO1
    {
        result = pthread_create(&thread, nullptr, Loop1, this);
    }
    else if (OBNum == 2){
        result = pthread_create(&thread, nullptr, Loop2, this);
    }
    else if (OBNum == 3)
    {
        result = pthread_create(&thread, nullptr, Loop3, this);
    }
    else
    {
        result = pthread_create(&thread, nullptr, Loop4, this);
    }
    if (result != 0) {
        std::cerr << "Failed to create thread." << std::endl;
        return;
    }
}


bool ActiveObject::isStopFlag() const {
    return stopFlag;
}

void* ActiveObject::Loop2(void* arg) {
    auto* AO = static_cast<ActiveObject*>(arg);
    void* task = AO->myQueue->Dequeue();
    while (task) {
        AO->myFunc(task);
        task = AO->myQueue->Dequeue();
        if(ActiveObject::stopFlag == true){
            stop(AO);
        }
    }
    return arg;
}

void* ActiveObject::Loop3(void* arg) {
    auto* AO = static_cast<ActiveObject*>(arg);
    void* task = AO->myQueue->Dequeue();
    while (task) {
        AO->myFunc(task);
        task = AO->myQueue->Dequeue();
        if(ActiveObject::stopFlag == true){
            stop(AO);
        }
    }

    return arg;
}

void* ActiveObject::Loop4(void* arg) {
    auto* AO = static_cast<ActiveObject*>(arg);
    void* task = AO->myQueue->Dequeue();
    while (task) {
        AO->myFunc(task);
        task = AO->myQueue->Dequeue();
        ActiveObject::counter--;
    }
    return arg;
}

// Wrapper function to convert std::function to C-style function pointer
void* ActiveObject::Loop1(void* arg) {
    
    auto* AO = static_cast<ActiveObject*>(arg);
    AO->myFunc(nullptr);  // Call the std::function with a dummy argument
    return arg;
}

ThreadSafeQueue* getQueue(ActiveObject* AO){
    return AO->myQueue;
}

void stop(ActiveObject* AO){
    AO->myQueue->stopCV.notify_all();
    pthread_cancel(AO->thread);
    
}
