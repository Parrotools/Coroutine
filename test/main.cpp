#include <iostream>

#include "scheduler.h"


void taskA()
{
    std::cout << "A1\n";

    yield();

    std::cout << "A2\n";

    yield();

    std::cout << "A3\n";
}


void taskB()
{
    std::cout << "B1\n";

    yield();

    std::cout << "B2\n";

    yield();

    std::cout << "B3\n";
}


int main()
{
    Scheduler scheduler;


    scheduler.add(taskA);

    scheduler.add(taskB);


    scheduler.run();


    std::cout << "scheduler finished\n";


    return 0;
}