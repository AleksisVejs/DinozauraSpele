#include <iostream>
#include <SFML/Graphics.hpp>
#include <string> 
#include <fstream>
#include "SFML/Audio.hpp"

using namespace sf;

#define WIDTH 600
#define HEIGHT 300

struct Position
{
	int x;
	int y;
};

int main(void)
{	
	Clock clock;

	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Dinozaurs");
	window.setFramerateLimit(60);

	Font pointFont;
	Text pointText;
	Music music;
	Texture t1;
	Texture t2;
	pointFont.loadFromFile("dosis.light.ttf");
	t1.loadFromFile("dinoR.png");
	t2.loadFromFile("dinoL.png");
	music.openFromFile("forwhomthebelltolls.ogg");
	music.setVolume(10);
	music.play();

	Sprite dinoArr[2];
	dinoArr[0] = Sprite(t1);
	dinoArr[1] = Sprite(t2);

	pointText.setFont(pointFont);
	pointText.setPosition(20, 10);
	pointText.setFillColor(Color::Black);
	pointText.setString("Punkti: 0");

	static const int DINO_Y_BOTTOM = HEIGHT - t1.getSize().y;

	Position dinoPos;
	dinoPos.x = 50;
	dinoPos.y = DINO_Y_BOTTOM;

	int index = 0;
	float frame = 0.f;
	float frameSpeed = 0.5f;
	const int changeCount = 5;

	const int gravity = 4;
	bool isJumping = false;
	bool isBottom = true;

	Texture t3;
	t3.loadFromFile("tree.png");
	Sprite tree(t3);

	static const int TREE_Y_BOTTOM = HEIGHT - t3.getSize().y;

	Position treePos;
	treePos.x = WIDTH - 20;
	treePos.y = TREE_Y_BOTTOM;

	const int treeSpeed = 5;

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			if (isBottom && !isJumping)
			{
				isJumping = true;
				isBottom = false;
			}
		}

		if (isJumping)
		{
			dinoPos.y -= gravity;
		}

		else
		{
			dinoPos.y += gravity;
		}

		if (dinoPos.y >= DINO_Y_BOTTOM)
		{
			dinoPos.y = DINO_Y_BOTTOM;
			isBottom = true;
		}

		if (dinoPos.y <= DINO_Y_BOTTOM - 115)
		{
			isJumping = false;
		}

		frame += frameSpeed;

		if (frame > changeCount)
		{
			frame -= changeCount;
			++index;
			if (index >= 2) { index = 0; }
		}

		if (treePos.x <= 0)
		{
			treePos.x = WIDTH;
		}

		else
		{
			treePos.x -= treeSpeed;
		}

		Time time = clock.getElapsedTime();
		int points = time.asSeconds();
		std::string pointsString = std::to_string(points);
		pointText.setString("Punkti: " + pointsString);

		tree.setPosition(treePos.x, treePos.y);

		dinoArr[index].setPosition(dinoPos.x, dinoPos.y);

		window.clear(Color::White);
		window.draw(pointText);
		window.draw(dinoArr[index]);
		window.draw(tree);

		if (dinoArr[index].getGlobalBounds().intersects(tree.getGlobalBounds()))
		{
			window.close();
		}

		window.display();
	}
	return 0;
}

