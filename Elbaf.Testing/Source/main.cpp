#include <iostream>
#include <Math\Fundamental.h>
#include <Math\Vector.h>
#include <Core\IGameWindow.h>

int main()
{
	std::cout << (Vector::Normalize<Vector2f>(Vector2i(5, 1)) * 2) << "\n";
	std::cin.ignore();

	return 1;
}