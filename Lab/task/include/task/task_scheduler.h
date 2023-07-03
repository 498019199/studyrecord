#pragma
#include <task/task.h>

class task_scheduler
{
public:
    void add_task(task t) 
    {
        tasks_.push_back(t);
    }
    void run() 
    {
        while (!tasks_.empty()) 
        {
            auto t = tasks_.front();
            tasks_.erase(tasks_.begin());
            t.resume();
            if (t) tasks_.push_back(t);
        }
    }
private:
    std::vector<task> tasks_;
};