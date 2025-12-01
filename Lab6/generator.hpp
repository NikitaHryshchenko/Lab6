#pragma once
#include <coroutine>
#include <random>
#include "await_controller.hpp"

struct GeneratorTask {
    struct promise_type {
        GeneratorTask get_return_object() {
            return GeneratorTask{ std::coroutine_handle<promise_type>::from_promise(*this) };
        }

        std::suspend_always initial_suspend() noexcept {
            return {};
        }

        std::suspend_always final_suspend() noexcept {
            return {};
        }

        void return_void() noexcept {}

        void unhandled_exception() {
            std::terminate();
        }
    };

    std::coroutine_handle<promise_type> handle;

    explicit GeneratorTask(std::coroutine_handle<promise_type> h)
        : handle(h) {
    }

    GeneratorTask(const GeneratorTask&) = delete;

    GeneratorTask(GeneratorTask&& other) noexcept
        : handle(other.handle) {
        other.handle = nullptr;
    }

    ~GeneratorTask() {
        if (handle) {
            handle.destroy();
        }
    }

    bool resume() {
        if (!handle || handle.done()) {
            return false;
        }
        handle.resume();
        return !handle.done();
    }
};

inline GeneratorTask random_generator() {
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> distribution(1, 256);

    while (true) {
        int value = distribution(engine);
        co_await AwaitController{ value };
    }
}
