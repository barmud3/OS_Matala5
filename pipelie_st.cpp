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

bool isPrime(unsigned int num)
{
    if (num < 3) // num = 1 or 2 .
    {
        return false;
    }
    
    for (size_t i = 2; i <= sqrt(num); i++)
    {
        if (num%i == 0)
        {
            return false;
        }
    }
    return true;
}

void Task1(unsigned int N, unsigned int seed , ActiveObject* transform , void* task) {
    ActiveObject::counter = N;
    (void)task;
    std::mt19937 generator(seed); // Initialize random number generator with seed
    std::uniform_int_distribution<int> distribution(0, 999); // Define range from 0 to 999
    int* array[N];
    for (unsigned int i = 0; i < N; ++i) {
        int number1 = distribution(generator); // Generate first 3-digit number
        int number2 = distribution(generator); // Generate second 3-digit number
        int* number = new int(number1 * 1000 + number2); // Combine the two numbers
        array[i] = number;
    }
    for (size_t i = 0; i < N; i++)
    {
        usleep(1000);
        getQueue(transform)->Enqueue((void*)(array[i]));
    }
    
}

void Task2(ActiveObject* nextAO , void* task) {
    int num = *((int*)(task));
    cout << num << endl;
    bool prime = isPrime(num);
    
    if (!prime) {
        cout << "false" << endl;
    } else {
        cout << "true" << endl;
    }
    int* numTransfer = new int(num + 11);
    getQueue(nextAO)->Enqueue(static_cast<void*>(numTransfer));

}

void Task3(ActiveObject* nextAO , void* task) {
    int num = *((int*)(task));
    cout << num << endl;
    bool prime = isPrime(num);
    
    if (!prime) {
        cout << "false" << endl;
    } else {
        cout << "true" << endl;
    }
    int* numTransfer = new int(num - 13);
    getQueue(nextAO)->Enqueue(static_cast<void*>(numTransfer));
}

void Task4(ActiveObject* myAO, void* task) {
    int num = *((int*)(task));
    cout << num << endl;
    bool prime = isPrime(num);
    
    if (!prime) {
        cout << "false" << endl;
    } else {
        cout << "true" << endl;
    }
    int numTransfer = num + 2;
    cout << numTransfer << endl;

    if(ActiveObject::counter == 1){
            ActiveObject::stopFlag = true;
            stop(myAO);
        }
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

    aObject1.CreateActiveObject([&](void* task) {
        Task1(N, seed, &aObject2 , task);
    } , 1 , "AO_1");
    
    aObject2.CreateActiveObject([&](void* task) {
        Task2(&aObject3, task);
    } , 2, "AO_2");

    aObject3.CreateActiveObject([&](void* task) {
        Task3(&aObject4, task);
    } ,3 , "AO_3");

    aObject4.CreateActiveObject([&](void* task) {
        Task4(&aObject4,task);
    } , 4 , "AO_4");

    while(!ActiveObject::stopFlag){


    }
    sleep(1);

    return 0;
}
