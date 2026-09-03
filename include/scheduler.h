#pragma once
#include<vector>
#include<memory>
#include"coroutine.h"
#include"context.h"
class Scheduler{
    public:
        void add(Coroutine::Func func);
        void run();
    private:
        Context main_ctx{};
        Coroutine* current = nullptr;
        std::vector<std::unique_ptr<Coroutine>>coroutines;
        inline static thread_local Scheduler* active = nullptr;
        friend class Coroutine;
        friend void yield();
        friend void coroutine_entry();

};