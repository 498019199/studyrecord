#include <task/processor.h>
int sTaskId = 0;

int processor::add_task(const task_fun& func)
{
    sTaskId++;
    return sTaskId;
}

void processor::remove_task(int task_id)
{
    
}

void processor::suspend_task(int task_id)
{
    
}

void processor::resume_task(int task_id)
{
    
}
