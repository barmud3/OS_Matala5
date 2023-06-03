#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <chrono>
#include <queue>
#include <unistd.h>
#include <math.h>
#include "ActiveObject.hpp"

using namespace std;

int isPrime(unsigned int num)
{
    if (num < 3) // num = 1 or 2 .
    {
        return 0;
    }
    
    for (size_t i = 3; i <= sqrt(num); i++) //Without num 2 that he is even.
    {
        if (num%i == 0)
        {
            return 0;
        }
    }
    return 1;
    
}

void Task1(unsigned int N, unsigned int seed , ActiveObject* transform) {
    cout << "INSIDE TASK1 " << endl;
    std::mt19937 generator(seed); // Initialize random number generator with seed
    std::uniform_int_distribution<int> distribution(0, 999); // Define range from 0 to 999
    int* array[N];
    for (unsigned int i = 0; i < N; ++i) {
        int number1 = distribution(generator); // Generate first 3-digit number
        int number2 = distribution(generator); // Generate second 3-digit number
        int number = number1 * 1000 + number2; // Combine the two numbers

        array[i] = new int[number];
    }
    for (size_t i = 0; i < N; i++)
    {
        sleep(3);
        transform->getQueue()->Enqueue(array[i]);
    }
    
}

void Task2_3(ActiveObject* myAO , ActiveObject* nextAO , int numSubtract) {
    cout << "INSIDE TASK2_3 " << endl;
    int* pointInt = static_cast<int*>(myAO->getQueue()->Dequeue());
    int num = *pointInt;
    cout << "NUM: " << num << endl;
    int prime = isPrime(num);
    if (prime != 0) {
        cout << "FALSE" << endl;
    } else {
        cout << "TRUE" << endl;
    }
    int numTransfer = num - numSubtract;
    void* intPtr = static_cast<void*>(&numTransfer);
    nextAO->getQueue()->Enqueue(intPtr);
}

void Task4(ActiveObject* myAO) {
    cout << "INSIDE TASK4 " << endl;
    int* pointInt = static_cast<int*>(myAO->getQueue()->Dequeue());
    int num = *pointInt;
    cout << "NUM: " << num << endl;
    int prime = isPrime(num);
    if (prime != 0) {
        cout << "FALSE" << endl;
    } else {
        cout << "TRUE" << endl;
    }
    int numTransfer = num + 2;
    cout << "NEW NUM: " << numTransfer << endl;
}

int main(int argc, char const *argv[])
{
    if (argc < 2 || argc > 3)
    {
        printf("./st_pipline [N] [random seed] *OR* ./st_pipline [N]\n");
        exit(1);
    }
    unsigned int N = stoi(argv[1]);
    unsigned int seed;
    if (argc == 2) //didn't get random seed 
    {
        seed = static_cast<unsigned int>(time(nullptr));
    }
    else
    {
        seed = stoi(argv[2]);
    }

    ActiveObject aObject1;
    ActiveObject aObject2;
    ActiveObject aObject3;
    ActiveObject aObject4;

    aObject1.CreateActiveObject([&](void* arg) {
        (void)arg;
        cout << pthread_self() << endl;
        Task1(N, seed, &aObject2);
    } , 1);
    
    aObject2.CreateActiveObject([&](void* arg) {
        (void)arg;
        Task2_3(&aObject2, &aObject3, 11);
    } , 0);

    aObject3.CreateActiveObject([&](void* arg) {
        (void)arg;
        Task2_3(&aObject3, &aObject4, 13);
    } ,0 );

    aObject4.CreateActiveObject([&](void* arg) {
        (void)arg;
        Task4(&aObject4);
    } , 0);

    // aObject1.stop();
    // aObject2.stop();
    // aObject3.stop();
    // aObject4.stop();

    return 0;
}

