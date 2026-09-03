#include<iostream>
#include "coroutine.h"
using namespace std;
void hello(){
    // cout<<"hello coroutine\n";
    cout<<"A\n";
    yield();
    cout<<"B\n";
}
int main(){
    std::cout<<"Coroutine project start\n";
    Coroutine co(hello);
    // cout<<"main before resume\n";
    // co.resume();
    // cout<<"main after resume\n";
    cout<<"main 1\n";
    co.resume();
    cout<<"main 2\n";
    co.resume();
    cout<<"main 3\n";

    return 0;
}