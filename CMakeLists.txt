cmake_minimum_required(VERSION 3.20)

project(Coroutine)

enable_language(ASM)
set(CMAKE_CXX_STANDARD 20)


include_directories(
    include
)


add_executable(
    coroutine_test

    test/main.cpp

    src/coroutine.cpp
    src/scheduler.cpp
    src/context.S
)