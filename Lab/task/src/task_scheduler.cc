#include <task/task_scheduler.h>

#include <thread>
#include <algorithm>

#include <unistd.h>
namespace task{

void task_scheduler::init(int count)
{
    count = std::clamp(count, 
        1, static_cast<int>(sysconf(_SC_NPROCESSORS_ONLN)));
    
    for (int i = 0; i < count; i++)
    {
        auto pro = std::make_shared<processor>();
    }
}

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
}