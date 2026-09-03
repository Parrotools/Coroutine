#pragma once 
struct Context{
    void* sp;
    void* x19;
    void* x20;
    void* x21;
    void* x22;
    void* x23;
    void* x24;
    void* x25;
    void* x26;
    void* x27;
    void* x28;
    void* fp;
    void* lr;
};
extern "C"
void switch_context(
    Context* old,
    Context* next
);