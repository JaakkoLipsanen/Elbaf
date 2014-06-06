
#include <iostream>
#include <memory>
#include "Core\Game.h"
#include "TestGame.h"

int main()
{
	// todo: wrap this into an try...catch block?
	std::unique_ptr<Game> game(new TestGame);
	game->Run(); 

	return 0;
}