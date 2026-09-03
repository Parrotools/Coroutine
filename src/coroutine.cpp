#include"coroutine.h"
#include<iostream>

Coroutine* current = nullptr;
Context main_ctx;
bool Coroutine::finished()const{
    return state == State::Finished;
}
Coroutine::Coroutine(Func f){
    func = f;
    finished = false;
    void* stack_top = stack + sizeof(stack);
    stack_top = (void*)((uintptr_t)stack_top & ~0xFULL);
    ctx.sp = stack_top;
    ctx.lr = (void*)coroutine_entry;
}
void Coroutine::resume(){
    if(finished){
        return;
    }
    current = this;
    switch_context(&main_ctx,&ctx);
}
void Coroutine::run(){
    func();
}
void Coroutine::finish(){
    finished=true;
}
extern "C"
void coroutine_entry(){
    current->run();
    current->finish();
    switch_context(&current->ctx,&main_ctx);
}
void yield(){
    switch_context(&current->ctx,&main_ctx);
}