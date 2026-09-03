#pragma once
#include<vector>
#include<memory>
#include"coroutine.h"
class Scheduler{
    public:
        void add(Coroutine::Func func);
        void run();
    private:
        std::vector<std::unique_ptr<Coroutine>>coroutines;
};