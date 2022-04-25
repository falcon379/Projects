#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;

View SetPlayerCoordinateForView(float x, float y)
{

	float tempX = x; float tempY = y;

	if (x < 640) tempX = 640;
	if (y < 500) tempY = 500;
	if (y > 854) tempY = 854;

	view.setCenter(tempX, tempY);  

	view.setCenter(x + 400, y);
	return view;
}
