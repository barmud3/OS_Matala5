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
    
    for (size_t i = 3; i <= sqrt(num); i++) //Without num 2 that he is even.
    {
        if (num%i == 0)
        {
            return false;
        }
    }
    return true;
    
}

void Task1(unsigned int N, unsigned int seed , ActiveObject* transform , void* task) {
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
        cout << "Wait 3 seconds then push new task to AO2's queue" << endl;
        usleep(3000);
        transform->getQueue()->Enqueue((void*)(array[i]));
    }
    
}

void Task2(ActiveObject* nextAO , void* task) {
    int num = *((int*)(task));
    cout << num << endl << endl;
    bool prime = isPrime(num);
    
    if (!prime) {
        cout << "PRIME : FALSE" << endl;
    } else {
        cout << "PRIME : TRUE" << endl;
    }
    
    int numTransfer = num + 11;

    nextAO->getQueue()->Enqueue((void*)(&numTransfer));
    cout << "CHECK NUM !! " << *(&numTransfer) << endl;
}

void Task3(ActiveObject* nextAO , void* task) {
    int num = *((int*)(task));
    cout << "CHECK NUM !! " << num << endl;
    int prime = isPrime(num);
    if (!prime) {
        cout << "PRIME : FALSE" << endl;
    } else {
        cout << "PRIME : TRUE" << endl;
    }
    int numTransfer = num - 13;
    nextAO->getQueue()->Enqueue((void*)(&numTransfer));
}

void Task4(void* task) {
    int num = *((int*)(task));
    int prime = isPrime(num);
    if (prime != 0) {
        cout << "PRIME : FALSE" << endl;
    } else {
        cout << "PRIME : TRUE" << endl;
    }
    int numTransfer = num + 2;
    cout << "LAST NUM GOT: " << numTransfer << endl;
}

int main(int argc, char const *argv[])
{
    if (argc < 2 || argc > 3)
    {
        printf("./st_pipline [N] [random seed] *OR* ./st_pipline [N]\n");
        exit(1);
    }
    unsigned int N = stoi(argv[1]);
    cout << "N: " << to_string(N) << endl;
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
        Task4(task);
    } , 4 , "AO_4");

    aObject1.joinThread();
    aObject2.joinThread();
    aObject3.joinThread();
    aObject4.joinThread();


    return 0;
}

