#pragma once
#include <task/task.h>
#include <vector>

class task_scheduler
{
public:
    void add_task(task t); 

    void run(); 
private:
    std::vector<task> tasks_;
};

