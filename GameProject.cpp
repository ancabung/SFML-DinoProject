#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>

using namespace std;

class Animation
{
public:
	Animation() = default;
	Animation(int x, int y, int width, int height)
	{
		texture.loadFromFile("DinoSprites - vita.png");
		for (int i = 0; i < nFrames; i++)
		{
			frames[i] = { x + i * width,y,width,height };
			flipFrames[i] = { x + i * width + width,y,-width,height };
		}
	}
	void ApplyToSprite(sf::Sprite& s) const
	{
		s.setTexture(texture);
		s.setTextureRect(frames[iFrame]);
	}
	void Update(float dt)
	{
		time += dt;
		while (time >= holdTime)
		{
			time -= holdTime;
			Advance();
		}
	}
private:
	void Advance()
	{
		if (++iFrame >= nFrames)
		{
			iFrame = 0;
		}
	}

private:
	static constexpr int nFrames = 4;
	static constexpr float holdTime = 0.1f;
	sf::Texture texture;
	sf::IntRect frames[nFrames], flipFrames[nFrames];
	int iFrame = 0;
	float time = 0.0f;
};

class Dino
{
//public:
	//static constexpr float gravity = 1;
	//int groundHeight = 600.0f;
private:
	enum class AnimationIndex
	{	StandingLeft,
		StandingRight,
		SprintRight,
		SprintLeft,
		WalkingUp,
		WalkingDown,
		WalkingLeft,
		WalkingRight,
		Count,
		breakLeft,
		breakRight
	};
public:
	Dino(const sf::Vector2f& pos)
		:
		pos(pos)
	{
			//Set sprite at specific position
			sprite.setTextureRect({ 0,0,24,24 });
			animation[int(AnimationIndex::StandingLeft)] = Animation(24*4, 0, -24, 24);
			animation[int(AnimationIndex::StandingRight)] = Animation(0, 0, 24, 24);
			animation[int(AnimationIndex::WalkingUp)] = Animation(24 * 3, 0, 24, 24);
			animation[int(AnimationIndex::WalkingDown)] = Animation(24 * 3, 0, 24, 24);
			animation[int(AnimationIndex::WalkingLeft)] = Animation(24 * 7, 0, -24, 24);
			animation[int(AnimationIndex::WalkingRight)] = Animation(24 * 3, 0, 24, 24);
			animation[int(AnimationIndex::SprintRight)] = Animation(24 * 18, 0, 24, 24);
			animation[int(AnimationIndex::SprintLeft)] = Animation(24 * 22, 0, -24, 24);


		//Scale sprite
		sprite.setScale(sf::Vector2f(1.f, 1.f)); // absolute scale factor
		sprite.scale(sf::Vector2f(4.f, 4.f)); // factor relative to the current scale
	}
	void Draw(sf::RenderTarget& rt) const 
	{	
		rt.draw(sprite);
	}
	void SetDirection(const sf::Vector2f& dir)
	{
		vel = dir * speed;
		//Swiching between animations
		if (dir.x > 0.0f && dir.x < 3.0f)
		{
			state = AnimationIndex::breakRight;
			curAnimation = AnimationIndex::WalkingRight;
		}
		else if (dir.x < 0.0f && dir.x > -3.0f)
		{
			state = AnimationIndex::breakLeft;
			curAnimation = AnimationIndex::WalkingLeft;

		}
		else if (dir.y < 0.0f)
		{
			curAnimation = AnimationIndex::WalkingUp;

		}
		else if (dir.y > 0.0f)
		{
			curAnimation = AnimationIndex::WalkingDown;
		}
		else if (dir.x > 3.0f)
		{
			curAnimation = AnimationIndex::SprintRight;
		}
		else if (dir.x < -3.0f)
		{
			curAnimation = AnimationIndex::SprintLeft;
		}
		else if (dir.x == 0 && dir.y == 0)
		{
			if (state == AnimationIndex::breakRight)
				curAnimation = AnimationIndex::StandingRight;
			else curAnimation = AnimationIndex::StandingLeft;
		}

	}
	void SetPosition(sf::Vector2f newPos) {
		sprite.setPosition(newPos);
	}
	void Update(float dt) {
		pos += vel * dt;	
		animation[int (curAnimation)].Update(dt);
		animation[int(curAnimation)].ApplyToSprite(sprite);
		sprite.setPosition(pos);
	}
	float getY() {
		return sprite.getPosition().y;
	}
private:
	static constexpr float speed = 125.0f;
	sf::Vector2f pos;
	sf::Vector2f vel = {0.0f,0.0f};
	sf::Sprite sprite;
	Animation animation[int(AnimationIndex::Count)] ;
	AnimationIndex curAnimation = AnimationIndex::StandingRight;
	AnimationIndex state = AnimationIndex::breakRight;
};

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(1600, 800), "VitaTheDino");
	sf::Texture bg;
	bg.loadFromFile("background.png");
	sf::Sprite sBackground(bg);
	Dino vita({ 100.0f, 100.0f });
	
	//Gravity Variables
	//const int groundHeight = 600.0f;
	//const float gravity = 30.0f;
	//bool isJumping = false;
	
	//Font
	sf::Font font;
	if (!font.loadFromFile("Monogram.ttf"))
		return EXIT_FAILURE;
	sf::Text text("VitaTheDino", font, 50);

	// timepoint for delta time measurement
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

		//Handle input
		sf::Vector2f dir = { 0.0f,0.0f };
		//if (sf::Event::KeyReleased) isJumping = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			dir.y -= 2.0f;
			//isJumping = true;
		//} else if (vita.getY() < groundHeight && isJumping == false) {
		//	dir.y += 5.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			dir.y += 2.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			dir.x -= 2.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			dir.x += 2.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			dir.x += 5.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			dir.x -= 5.0f;
		}
		vita.SetDirection(dir);
		//update
		vita.Update(dt);
		//Gravity Logic
		//if (vita.getY() < groundHeight && isJumping == false) {
		//	dir.y += gravity;
		//}
		
		// Clear screen
		window.clear();
		window.draw(sBackground);		//Draw background
		window.draw(text);				//Draw text
		// Draw the sprite
		vita.Draw(window);
		
		// Update the window
		window.display();
	}
	return EXIT_SUCCESS;
}