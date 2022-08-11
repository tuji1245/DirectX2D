#include <iostream>

using namespace std;
#include <memory>
#include <Graphic\Color.hpp>

int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	Engine2D::Color color{};

	cout << color.r << " " << color.g << "\n";
	cout << color.array[0] << " " << color.array[1] << "\n";
	
	
	system("pause");

	return 0;
}