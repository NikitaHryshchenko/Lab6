#pragma once
#include <coroutine>
#include "coroutine_a.hpp"

struct AwaitController {
    int value;

    bool await_ready() const noexcept {
        return false;
    }

    void await_suspend(std::coroutine_handle<>) const {
        if (value % 2 == 0) {
            coroutineA(value);
        }
    }

    void await_resume() const noexcept {}
};
