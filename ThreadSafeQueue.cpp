#include "ThreadSafeQueue.hpp"

void ThreadSafeQueue::Enqueue(void *item) {

    std::lock_guard<std::mutex> lock(mtx);  // Lock the mutex

    myQueue.push(item);                     // Add the item to the queue
    cout << pthread_self() << " Pushing item "<< to_string(*((int*)item)) << " to queue" << endl;
    cv.notify_one();                        // Notify one waiting thread
}

void* ThreadSafeQueue::Dequeue() {
    std::unique_lock<std::mutex> lock(mtx);

    // Check the stopFlag before waiting on the condition variable
    if (stopFlag) {
        return nullptr;
    }
    cout << pthread_self() << " check if the queue is filled, wait if not" << endl;
    cv.wait(lock, [this]{ return !myQueue.empty() || stopFlag; });
    
    if (stopFlag) {
        return nullptr;
    }

    void* item = myQueue.front();
    cout << pthread_self() << " dequeue item "<< to_string(*((int*)item)) << " from queue" << endl;
    myQueue.pop();

    return item;
}

void ThreadSafeQueue::Stop() {
    stopFlag = true;
    cv.notify_all();
}
