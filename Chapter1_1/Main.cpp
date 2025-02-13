#include "Game.h"

int main()
{
	Game game;
	if (game.IsValid())
	{
		game.RunLoop();
	}
}