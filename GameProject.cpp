#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include "Player.h"
#include "Animation.h"
#include "Obstacles.h"
#include "Status.h"
using namespace std;

struct GameOverMessage
{
	sf::Font font;
	sf::Text text;
	GameOverMessage() {
		if (!font.loadFromFile("Monogram.ttf"))
		{
			cout << "Error loading arial.ttf" << endl;
		}
		text.setFont(font);
		text.setString("Game Over");
		text.setCharacterSize(80); // in pixels, not points!
		// set the color
		// set the text style
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);
		text.setPosition(sf::Vector2f(1024 / 2, 768 / 2 ));
	}

	void draw(sf::RenderWindow& window) {
		window.draw(text);
	}
};

int main()
{
	// Create the main window
	GameOverMessage gameovermsg;
	Status status;
	sf::RenderWindow window(sf::VideoMode(status.window_width, status.window_height), "VitaTheDino");
	sf::Texture bg;
	bg.loadFromFile("background.png");
	sf::Sprite sBackground(bg);
	Player vita({ status.window_width / 2 - 55, status.window_height / 2 - 30});
	Obstacles object({ 1000.0f ,400.0f });
	sf::Vector2f _dir = { 1.0f, 1.0f };
	float life = 2;
	//Font
	sf::Font font;
	if (!font.loadFromFile("Monogram.ttf"))
		return EXIT_FAILURE;
	sf::Text text("VitaTheDino", font, 50);

	// timepoint for delta time calculation
	auto tp = chrono::steady_clock::now();
	// Load a music to play
	sf::Music music;
	if (!music.openFromFile("Ludum Dare 32 - Track 2.wav"))
		return EXIT_FAILURE;
	// Play the music
	music.play();

	// Start the game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// get delta time
		float dt;
		{
			const auto new_tp = chrono::steady_clock::now();
			dt = chrono::duration<float>(new_tp - tp).count();
			tp = new_tp;
		}

		//Handle input //TODO: move to status class
		if (life > 0) {
			sf::Vector2f dir = { 0.0f,0.0f };
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if (vita.getY() + 16 <= 0) dir.y = 0.0f;
				else dir.y -= 2.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if (vita.getY() + 88 >= status.window_height) dir.y = 0.0f;
				else dir.y += 2.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (vita.getX() + 20 <= 0) dir.x = 0.0f;
				else dir.x -= 2.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (vita.getX() + 80 >= status.window_width) dir.x = 0.0f;
				else dir.x += 2.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (vita.getX() + 80 >= status.window_width) dir.x = 0.0f;
				else dir.x += 5.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (vita.getX() + 20 <= 0) dir.x = 0.0f;
				else dir.x -= 5.0f;
			}
			if (object.getX() - 250 >= status.window_width) _dir.x = -1.0f;
			if (object.getX() + 250 <= 0) _dir.x = 1.0f;
			if (object.getY() - 250 >= status.window_height) _dir.y = -1.0f;
			if (object.getY() + 250 <= 0) _dir.y = 1.0f;

			if (vita.isCollidingwithObject(object)) life -= 1;

			//Set direction
			object.SetDirection(_dir);
			vita.SetDirection(dir);

			//update

			object.Update(dt);
			vita.Update(dt);

			// Clear screen
			window.clear();

			window.draw(sBackground);		//Draw background
			window.draw(text);				//Draw text

											// Draw the sprite
			vita.Draw(window);
			object.Draw(window);
		}
		// Update the window
		else gameovermsg.draw(window);
		window.display();
	}
	return EXIT_SUCCESS;
}
