#include<scheduler.h>
void Scheduler::add(Coroutine::Func func){
    coroutines.push_back(std::make_unique<Coroutine>(func));
    
}
void Scheduler::run(){
    bool all_finished = false;
    while(!all_finished){
        all_finished = true;
        for(auto& coroutine:coroutines){
            if(!coroutine->finished()){
                all_finished=false;
                coroutine->resume();
            }
        }
    }
}