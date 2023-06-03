#include "ActiveObject.hpp"

void ActiveObject::CreateActiveObject(std::function<void(void*)> func , bool isOB1) {
    cout << "INSIDE CREATE ACTIVE OBJECT" << endl;
    //myQueue = new ThreadSafeQueue();
    this->myFunc = func;
    stopFlag = false;
    int result= 0;
    if (isOB1 == 1) //AO1
    {
        result = pthread_create(&thread, nullptr, ThreadFuncWrapper, this);
    }
    else{

        result = pthread_create(&thread, nullptr, Loop, this);
    }
    if (result != 0) {
        std::cerr << "Failed to create thread." << std::endl;
        return;
    }
}


ThreadSafeQueue* ActiveObject::getQueue() {
    return myQueue;
}

bool ActiveObject::isStopFlag() const {
    return stopFlag;
}

void ActiveObject::stop() {

    this->stopFlag = true;
    this->getQueue()->stopCV.notify_all();
}

void* ActiveObject::Loop(void* arg) {
    auto* AO = static_cast<ActiveObject*>(arg);
    void* task = AO->getQueue()->Dequeue();
    cout << "Inside loop, flag: " << AO->isStopFlag() << endl;
    while (task) {
        AO->myFunc(task);
        task = AO->getQueue()->Dequeue();
    }

    return arg;
}

// Wrapper function to convert std::function to C-style function pointer
void* ActiveObject::ThreadFuncWrapper(void* arg) {
    auto* AO = static_cast<ActiveObject*>(arg);
    AO->myFunc(nullptr);  // Call the std::function with a dummy argument
    return arg;
}