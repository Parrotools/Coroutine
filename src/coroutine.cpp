#include"coroutine.h"
#include"scheduler.h"
#include<cstdint>
#include<iostream>

bool Coroutine::finished()const{
    return state == State::Finished;
}
Coroutine::Coroutine(Func f,Scheduler* scheduler){
    func = f;
    this->scheduler = scheduler;
    state = State::Ready;
    void* stack_top = stack + sizeof(stack);
    // stack_top = (void*)((uintptr_t)stack_top & ~0xFULL);
    stack_top = reinterpret_cast<void*>(
        reinterpret_cast<uintptr_t>(stack_top)&~uintptr_t(0xF)
    );
    ctx.sp = stack_top;
    // ctx.lr = (void*)coroutine_entry;
    ctx.lr = reinterpret_cast<void*>(coroutine_entry);
}
void Coroutine::resume(){
    if(state==State::Finished){
        return;
    }
    scheduler->current=this;
    Scheduler::active=scheduler;
    state = State::Running;
    switch_context(&scheduler->main_ctx,&ctx);
    scheduler->current=nullptr;
    Scheduler::active=nullptr;
}
void Coroutine::run(){
    func();
}
void Coroutine::finish(){
    // finished=true;
    state = State::Finished;
}
extern "C"
void coroutine_entry(){
    Scheduler* scheduler = Scheduler::active;
    Coroutine* current = scheduler->current;
    current->run();
    current->finish();
    switch_context(&current->ctx,&scheduler->main_ctx);
}
void yield(){
    // current->state = Coroutine::State::Suspended;
    Scheduler* scheduler = Scheduler::active;
    Coroutine* current = scheduler->current;
    current->state = Coroutine::State::Suspended;

    switch_context(&current->ctx,&scheduler->main_ctx);
}