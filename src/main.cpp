#include <iostream>
#include "core/util.h"

using namespace tinge;

int main(int argc, char const *argv[])
{
    float4 a = float4{1, 0, 0, 2};
    float4 b = float4{7, 1, 4, 13};
    float4 c = normalize(a + b) * b;    

    std::cout << c << std::endl;
    std::cout << matrix3() << std::endl;

    return 0;
}
