#include <task/task_scheduler.h>

#include <thread>
#include <algorithm>

#include <unistd.h>

namespace task_space{
uint32_t s_task_id = 0;
void task_scheduler::init(int count)
{
    count = std::clamp(count, 
        1, static_cast<int>(sysconf(_SC_NPROCESSORS_ONLN)));
    
    for (int i = 0; i < count; i++)
    {
        auto pro = std::make_shared<processor>();
    }
}

uint32_t task_scheduler::add_task(const task_fun& t)
{
    s_task_id++;
    //tasks_.push_back(t);
    return s_task_id;
}

void task_scheduler::run()
{
    while (!tasks_.empty()) 
    {
        auto t = tasks_.front();
        tasks_.erase(tasks_.begin());
        //t.resume();
        //if (t) tasks_.push_back(t);
    }
}
}