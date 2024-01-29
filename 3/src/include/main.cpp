#include "classes.hpp"
#include <cstdlib>
#include <iostream>

#include "../../raylib/src/raylib.h"

int main()
{

	srand(time(NULL));

	Game g(std::make_pair(6,6));

	const int PLAYER_SIZE = 40;
    	const int screenWidth = 960;
    	const int screenHeight = 456;

	g.StartScreen(screenWidth, screenHeight);

	g.DrawingMap(screenWidth, screenHeight);
}
