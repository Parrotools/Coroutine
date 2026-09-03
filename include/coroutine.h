#pragma once
#include "context.h"
class Scheduler;
extern "C"
void coroutine_entry();
void yield();
class Coroutine{
    public:
        using Func = void(*)();
        enum class State{
            Ready,
            Running,
            Suspended,
            Finished
        };
        Coroutine(Func f,Scheduler* scheduler);
        void resume();
        void run();
        void finish();
        bool finished()const;

    private:
        Context ctx{};
        Func func;
        char stack[64*1024];
        State state = State::Ready;
        Scheduler* scheduler;
        friend class Scheduler;
        friend void coroutine_entry();
        friend void yield();
};
