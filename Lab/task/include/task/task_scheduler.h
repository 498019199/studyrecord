#pragma once
#include <task/task.h>
#include <task/processor.h>

#include <vector>


namespace task{

class task_scheduler
{
public:
    void init(int count);

    void add_task(task t); 

    void run(); 
private:
    std::vector<task> tasks_;
    std::map<int ,ptr_processor> pro_map_;
};

}