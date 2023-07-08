#include <task/task_scheduler.h>

void task_scheduler::add_task(task t)
{
    tasks_.push_back(t);
}

void task_scheduler::run()
{
    while (!tasks_.empty()) 
    {
        auto t = tasks_.front();
        tasks_.erase(tasks_.begin());
        t.resume();
        //if (t) tasks_.push_back(t);
    }
}