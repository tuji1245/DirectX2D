#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

#include <d3d11.h>
#include <memory>
std::shared_ptr<ID3D11Device> device;


std::weak_ptr<ID3D11Device> GetDevice()
{
    return device;
}

int main(void)
{
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);



    return 0;
}