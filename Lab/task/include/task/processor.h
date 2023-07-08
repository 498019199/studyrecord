#pragma once
#include <functional>
#include <cstdint>
#include <task/task.h>
#include <map>
namespace task{

using task_fun = std::function<void()>;
class processor
{
public:
    int add_task(const task_fun& func);
    void remove_task(int task_id);
    void suspend_task(int task_id);
    void resume_task(int task_id);

private:
    uint64_t thread_id_ = 0;
    std::map<int, ptr_task> tasks_;
};

using ptr_processor = std::shared_ptr<processor>;
}