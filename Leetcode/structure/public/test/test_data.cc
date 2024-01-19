#include <iostream>
#include <public/rbtree.h>
#include <map>

int main(int argn, char** args)
{
    std::cout << "hello world" << std::endl;

    std::map<int,int> _1;
    DataBase::rbtree<int> testMap;
    testMap.Add({1,2,3,4});

    testMap.Remove(4);
    return 0;
}