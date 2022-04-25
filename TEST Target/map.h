#include <SFML\Graphics.hpp>
const int HEIGHT_MAP = 25;
const int WIDTH_MAP = 40;


sf::String TileMap[HEIGHT_MAP] = {
	"0000000000000000000000000000000000000000",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0000000000000000000000000000000000000000",
};

void randomMapGenerate() {

	int randomElementX = 0;
	int randomElementY = 0;
	srand(time(0));
	int countStone = 50;
	int countHP = 10;
	int countWeapon = 10;

	while (countStone > 0 )
	{
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		if (TileMap[randomElementY][randomElementX] == ' ') 
		{
			TileMap[randomElementY][randomElementX] = '0'; 
			countStone--;
		}
	}
	while ( countHP > 0 )
	{
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			TileMap[randomElementY][randomElementX] = 'h';
			countHP--;
		}

	}
	while ( countWeapon > 0)
	{
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);

		if (TileMap[randomElementY][randomElementX] == ' ')
		{
			TileMap[randomElementY][randomElementX] = 's';
			countWeapon--;
		}

	}
}
