#pragma once
#include <SFML/Graphics.hpp>
#include "animation.h"
#include "Obstacles.h"
class Player
{
private:
	enum class AnimationIndex
	{
		StandingLeft,
		StandingRight,
		SprintRight,
		SprintLeft,
		SprintUp,
		SprintDown,
		WalkingUp,
		WalkingDown,
		WalkingLeft,
		WalkingRight,
		Count,
		breakLeft,
		breakRight
	};
public:
	Player(const sf::Vector2f& pos);
	void Draw(sf::RenderTarget& rt) const;
	void SetDirection(const sf::Vector2f& dir);
	void SetPosition(sf::Vector2f newPos);
	void Update(float dt);
	float getY();
	float getX();
	bool isCollidingwithObject(Obstacles object);
private:
	static constexpr float speed = 150.0f;
	sf::Vector2f pos;
	sf::Vector2f vel = { 0.0f,0.0f };
	sf::Sprite sprite;
	Animation animation[int(AnimationIndex::Count)];
	AnimationIndex curAnimation = AnimationIndex::StandingRight;
	AnimationIndex state = AnimationIndex::breakRight;
};

