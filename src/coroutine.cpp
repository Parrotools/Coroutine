#include"coroutine.h"
#include<iostream>

Coroutine* current = nullptr;
Context main_ctx;
bool Coroutine::finished()const{
    return state == State::Finished;
}
Coroutine::Coroutine(Func f){
    func = f;
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
    current = this;
    switch_context(&main_ctx,&ctx);
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
    current->run();
    current->finish();
    switch_context(&current->ctx,&main_ctx);
}
void yield(){
    current->state = Coroutine::State::Suspended;
    
    switch_context(&current->ctx,&main_ctx);
}