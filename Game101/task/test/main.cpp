#include <task/task.h>

int main()
{
    task t = foo();
    t.resume();
    return 0;
}