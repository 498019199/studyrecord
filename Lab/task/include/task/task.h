#pragma once

#include <coroutine>
#include <memory>
namespace task_space{

struct task 
{
    struct promise_type 
    {
        task get_return_object() noexcept 
        {
            return std::coroutine_handle<promise_type>::from_promise(*this);
        }

        std::suspend_never initial_suspend() noexcept { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() noexcept {}
        void unhandled_exception() noexcept {}
    };

    using coroutine_handle = std::coroutine_handle<promise_type>;
    task(coroutine_handle handle) : handle_(handle) {}
    ~task() { if (handle_) handle_.destroy(); }
    void resume() { handle_.resume(); }
private:
    coroutine_handle handle_;
};

using ptr_task = std::shared_ptr<task>;
}