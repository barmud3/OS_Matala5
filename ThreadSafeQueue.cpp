#include "ThreadSafeQueue.hpp"
#include "ActiveObject.hpp"

bool ThreadSafeQueue::stopFlag = false;

void ThreadSafeQueue::Enqueue(void *item) {

    std::lock_guard<std::mutex> lock(mtx);  // Lock the mutex

    myQueue.push(item);                     // Add the item to the queue
    cv.notify_one();                        // Notify one waiting thread
}

void* ThreadSafeQueue::Dequeue() {
    std::unique_lock<std::mutex> lock(mtx);

    // Check the stopFlag before waiting on the condition variable
    if (ActiveObject::stopFlag) {
        Stop();
        return nullptr;
    }
    cv.wait(lock, [this]{ return !myQueue.empty() || stopFlag; });
    
    if (ActiveObject::stopFlag) {
        Stop();
        return nullptr;
    }

    void* item = myQueue.front();
    myQueue.pop();

    return item;
}

void ThreadSafeQueue::Stop() {
    ThreadSafeQueue::stopFlag = true;
    cv.notify_all();
}
