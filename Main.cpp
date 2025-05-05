#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.hpp"
//TO-DO make is rotate as well - Done
/*  int main(int arg, char** args[])
{//i think i am losing myself to to this fucking world 
the hell am i suppossed to do 
do i relly want to code 
meko pahado me jake rehna h bhai mujhse nhi ho pa rha h ab ye
ho gya mera
wahan jake bs mast apni ek programming language likhunga 
kyun krte h log ye sb kyun krna h logon ko kuch bhi
kya milta h logon to kuch bhi krne....bs dissappointment 
or phir dissappointment
	sf::RenderWindow window(sf::VideoMode(640, 480), "My Window");
	window.setFramerateLimit(200);
	sf::Texture logo_texture;
	if (!logo_texture.loadFromFile("resources/logo.png"))
	{
		std::cout << "Couldn't load texture";
		return EXIT_FAILURE;
	}

	sf::Vector2u size = logo_texture.getSize();

	sf::Sprite logo(logo_texture);
	logo.setOrigin(size.x / 2.0, size.y / 2.0);
	logo.setPosition(320, 240);
	logo.setColor(sf::Color(255, 0, 0, 100));

	sf::Vector2f increment(0.4f, 0.4f);
	float rotate = 3;
	sf::Vector2f scale(0.1f, 0.1f);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		if ((logo.getPosition().x + (size.x / 2.0) > window.getSize().x && increment.x > 0) ||
			(logo.getPosition().x - (size.x / 2.0) < 0 && increment.x < 0))
		{
			//increment.x > 0 ? increment.x += 0.1 : increment.x -= 0.1;
			increment.x = -increment.x;
			//rotate > 0 ? rotate++ : rotate--;
			rotate = -rotate;
			//logo.setScale(logo.getScale() + scale);
		}
		if ((logo.getPosition().y + (size.y / 2.0) > window.getSize().y && increment.y > 0) ||
			(logo.getPosition().y - (size.y / 2.0) < 0 && increment.y < 0))
		{
			//increment.y > 0 ? increment.y += 0.1 : increment.y -= 0.1;
			increment.y = -increment.y;
			//rotate > 0 ? rotate++ : rotate--;
			rotate = -rotate;
			//logo.setScale(logo.getScale() + scale);
		}

		logo.setPosition(logo.getPosition() + increment);
		logo.setRotation(logo.getRotation() + rotate);
		window.clear(sf::Color::Cyan);
		window.draw(logo);
		window.display();
	
	}

} */ 
 
int main(int arg, char** agrv[])
{
	Game game;
	while(!game.GetWindow()->IsDone())
	{
		//game.HandleInput();
		game.Update();
		game.Render();
		game.LastUpdate();
	}
}