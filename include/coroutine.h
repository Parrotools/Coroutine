#pragma once
#include "context.h"
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
        Coroutine(Func f);
        void resume();
        void run();
        void finish();
        bool finished()const;

    private:
        Context ctx{};
        Func func;
        char stack[64*1024];
        State state = State::Ready;
        friend void coroutine_entry();
        friend void yield();
};
