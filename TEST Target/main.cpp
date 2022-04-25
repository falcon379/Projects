#include <SFML/Graphics.hpp>
#include <iostream> 
#include <sstream>
#include <list>
#include "map.h" 
#include "view.h"   

using namespace sf;
using namespace std;

class Entity
{
public:
	float dx, dy, x, y, speed = 0;
	int w, h, health, damage;
	bool life, isMove;
	Texture texture;
	Sprite sprite;
	String name;
	Entity(Image& image, float X, float Y, int W, int H, String Name) {
		x = X; y = Y; w = W; h = H; name = Name; 
		speed = 0; health = 80; damage = 50; dx = 0; dy = 0;
		life = true; isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	}
	virtual void update(float time) = 0;
	FloatRect getRect() {return FloatRect(x, y, w, h);}
	
};

class Player :public Entity
{
public:
	enum  {left, right, up, down, attack, stay} state;
	int  PlayerScore;
	
	Player(Image& image, float X, float Y, int W, int H, String Name) : Entity(image, X, Y,  W,  H, Name)
	{
		PlayerScore = 0,state = stay;
		if (name=="player1"){ sprite.setTextureRect(IntRect(0, 0, w, h)); }
	
	}

	void control() 
	{
		if (Keyboard::isKeyPressed)
		{
			if ((Keyboard::isKeyPressed(Keyboard::Left)) || (Keyboard::isKeyPressed(Keyboard::A)))
			{
				state = left; speed = 0.5;
				sprite.setTextureRect(IntRect(0 + w, 0, -w, h));
			}

			if ((Keyboard::isKeyPressed(Keyboard::Right)) || (Keyboard::isKeyPressed(Keyboard::D)))
			{
				state = right; speed = 0.5;
				sprite.setTextureRect(IntRect(0, 0, w, h));
			}

			if ((Keyboard::isKeyPressed(Keyboard::Up)) || (Keyboard::isKeyPressed(Keyboard::W)))
			{
				state = up; speed = 0.5;
			}

			if ((Keyboard::isKeyPressed(Keyboard::Down)) || (Keyboard::isKeyPressed(Keyboard::S)))
			{
				state = down; speed = 0.5;
			}

			if (Keyboard::isKeyPressed(Keyboard::Space)) 
			{
				state = attack;
			}
		}
	}

	void CheckCollisionWithMap(float Dx, float Dy)
	{
		for (int i = y / 148; i < (y + h) / 148; i++)
			for (int j = x / 148; j < (x + w) / 148; j++)
			{
				if (TileMap[i][j] == '0')
				{
					if (Dy > 0) { y = i * 148 - h; dy = 0; }
					if (Dy < 0) { y = i * 148 + 148; dy = 0;}
					if (Dx > 0) { x = j * 148 - w; }
					if (Dx < 0) { x = j * 148 + 148;}
				}

				if (TileMap[i][j] == 's')
				{
					PlayerScore++;
					TileMap[i][j] = ' ';
				}
				else if (TileMap[i][j] == 'f')
				{
					damage += 30;
					TileMap[i][j] = ' ';

				}
				else if (TileMap[i][j] == 'h')
				{
					health += 20;
					TileMap[i][j] = ' ';
				}
			}
	}

	void update(float time) override
	{
		control();
		switch (state)
		{
		case left: dx = -speed; dy = 0; break;
		case right: dx = speed; dy = 0; break;
		case up: dx = 0; dy = -speed; break;
		case down: dx = 0; dy = speed; break;
		case attack: break;
		}
		x += dx * time;
		CheckCollisionWithMap(dx, 0);
		y += dy * time;
		CheckCollisionWithMap(0, dy);

		sprite.setPosition(x + w / 2, y + h / 2); 
		if (health <= 0) { life = false; }
		if (!isMove) { speed = 0; }
		if (life) { SetPlayerCoordinateForView(x, y); }
		
	}
};

class Enemy :public Entity {
public:
	Enemy(Image& image, float X, float Y, int W, int H, String Name) :Entity(image, X, Y, W, H, Name) {
		if (name == "EasyEnemy") {
			sprite.setTextureRect(IntRect(0, 0, w, h));
			dx = 0.2;
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = y / 148; i < (y + h) / 148; i++)
		for (int j = x / 148; j < (x + w) / 148; j++)
		{
			if (TileMap[i][j] == '0')
			{
				if (Dy > 0) { y = i * 148 - h; dy = -0.1; sprite.scale(-1, 1); }
				if (Dy < 0) { y = i * 148 + 148; dy = 0.1; sprite.scale(-1, 1); }
				if (Dx > 0) { x = j * 148 - w; dx = -0.1; sprite.scale(-1, 1); }
				if (Dx < 0) { x = j * 148 + 148; dx = 0.1; sprite.scale(-1, 1); }
			}
		}
	}

	void update(float time) override
	{
		if (name == "EasyEnemy") 
		{
			
				checkCollisionWithMap(dy, 0);
				x += dx * time;
				checkCollisionWithMap(dx, 0);
				x += dy * time;
				
		
			sprite.setPosition(x + w/ 2, y + h / 2);
			if (health <= 0) { life = false; }
		}
	}
};

class LifeBar 
{
public:
	Image image;
	Texture t;
	Sprite s;
	int max;
	RectangleShape bar;

	LifeBar()
	{
		image.loadFromFile("images/life.png");
		image.createMaskFromColor(Color(50, 96, 166));
		t.loadFromImage(image);
		s.setTexture(t);
		s.setTextureRect(IntRect(783, 2, 15, 84));

		bar.setFillColor(Color(0, 0, 0));
		max = 100;
	}

	void update(int k)// k-текущее здоровье
	{
		if (k > 0)
			if (k < max)
				bar.setSize(Vector2f(10, (max - k) * 70 / max));
	}

	void draw(RenderWindow& window)
	{
		Vector2f center = window.getView().getCenter();
		Vector2f size = window.getView().getSize();

		s.setPosition(center.x - size.x / 2 + 10, center.y - size.y / 2 + 10);//Set position window
		bar.setPosition(center.x - size.x / 2 + 14, center.y - size.y / 2 + 14);

		window.draw(s);
		window.draw(bar);
	}

};

int main()
{
	randomMapGenerate();

	RenderWindow window(VideoMode(1440, 1080), "Game");
	view.reset(FloatRect(0, 0, 1440, 1080));

	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	           
	Image player;
	player.loadFromFile("images/p.png");

	Image ii;
	ii.loadFromFile("images/ii.png");

	Player p(player, 300, 300, 148, 148, "player1");

	list<Entity*> entities;
	list<Entity*>::iterator it;

	
	entities.push_back(new Enemy(ii, 600, 400, 148, 148, "EasyEnemy"));
	entities.push_back(new Enemy(ii, 500, 1000, 148, 148, "EasyEnemy"));
	entities.push_back(new Enemy(ii, 1600, 800, 148, 148, "EasyEnemy"));
	entities.push_back(new Enemy(ii, 900, 1900, 148, 148, "EasyEnemy"));
	entities.push_back(new Enemy(ii, 2200, 1200, 148, 148, "EasyEnemy"));
	entities.push_back(new Enemy(ii, 2800, 2100, 148, 148, "EasyEnemy"));
	entities.push_back(new Enemy(ii, 3200, 800, 148, 148, "EasyEnemy"));


	/*Enemy easyEnemy(ii, 400, 400, 148, 148, "EasyEnemy");*/
	
	

	LifeBar lifeBarPlayer;//HP images

	
	Clock clock;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		
		clock.restart();
		time = time / 800;


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		lifeBarPlayer.update(p.health);//HP images
		p.update(time); 

		

			for (it = entities.begin(); it != entities.end();)
			{
				Entity* b = *it;//чтобы не писать (*it)->
				b->update(time);
				if (b->life == false) { it = entities.erase(it); delete b; }
				else { it++; }
			}
			for (it = entities.begin(); it != entities.end(); it++)
			{
				if ((*it)->getRect().intersects(p.getRect()))
				{
					if ((*it)->name == "EasyEnemy") 
					{
						if (Keyboard::isKeyPressed(Keyboard::Space)) { (*it)->health = 0; }
						/*else{ p.health -= 20; }*/ //не работает должным образом хз почему
					}
				}
			}
		
		
		
		window.setView(view);
		window.clear();

		for (int i = 0; i < HEIGHT_MAP; i++) 
		for (int j = 0; j < WIDTH_MAP; j++) {
			if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 148, 148)); 
			else if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(446, 0, 148, 148));//Weapon
			else if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(148, 0, 148, 148));//
			else if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(298, 0, 148, 148));//HP

			s_map.setPosition(j * 148, i * 148);

			window.draw(s_map);
		}
		

		lifeBarPlayer.draw(window);//HP images

		for (it = entities.begin(); it != entities.end(); it++) 
		{
			window.draw((*it)->sprite); 
		}
		
		window.draw(p.sprite);
		window.display();
	}

	return 0;
}