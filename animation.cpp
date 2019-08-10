
#include "Animation.h"

Animation::Animation(int x, int y, int width, int height)
{
	texture.loadFromFile("vita5.png");
	for (int i = 0; i < nFrames; i++)
	{
		frames[i] = { x + i * width,y,width,height };
	}
}
void Animation::ApplyToSprite(sf::Sprite& s) const
{
	s.setTexture(texture);
	s.setTextureRect(frames[iFrame]);
}
void Animation::Update(float dt)
{
	time += dt;
	while (time >= holdTime)
	{
		time -= holdTime;
		Advance();
	}
}

void Animation::Advance()
{
	if (++iFrame >= nFrames)
	{
		iFrame = 0;
	}
}