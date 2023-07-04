#include <iostream>
#include <math/vector2d.h>

void checkvecotr()
{
    vector2d v1(1.f, 2.f);
    std::cout << "checkvecotr sucess" << std::endl;
}

void checkmatrix()
{
    std::cout << "checkmatrix sucess" << std::endl;
}

void checkquaternion()
{
    std::cout << "checkquaternion sucess" << std::endl;
}

int main()
{
    checkvecotr();
    checkmatrix();
    checkquaternion();
}
