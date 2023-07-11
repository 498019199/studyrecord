#include <task/task_scheduler.h>
#include <iostream>

int app_main(int argn, char** args)
{
    return 0;
}

int main(int argn, char** args)
{
    auto tsh = new task_space::task_scheduler();
    tsh->init(1);
    tsh->add_task([](){
        //app_main(argn, args);
        std::cout << "test coro" << std::endl;
    });
    tsh->run();
    return 0;
}