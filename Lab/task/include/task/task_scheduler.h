#pragma once

#include <vector>

#include <task/task.h>
#include <task/processor.h>

namespace task_space{

class task_scheduler
{
public:
    void init(int count);

    uint32_t add_task(const task_fun& t); 

    void run(); 
private:
    std::vector<task> tasks_;
    std::map<int ,ptr_processor> pro_map_;
};
}
