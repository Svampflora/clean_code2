#include "Background.h"
#include "raylib.h"
#include "raymath.h"


Star::Star(Vector2 _start_position, Color _color, float _size)
{
	initPosition = _start_position;
	position = { 0, 0 };
	color = _color;
	size = _size;
	radius = size;
}

void Star::Update(float starOffset)
{
	position.x = initPosition.x + starOffset;
	position.y = initPosition.y;

}

void Star::Render() const
{
	DrawCircle((int)position.x, (int)position.y, size, color);
}

Background::Background(int starAmount)
{
	for (int i = 0; i < starAmount; i++)
	{
		Vector2 start_position{ static_cast<float>(GetRandomValue(-150, GetScreenWidth() + 150)), static_cast<float>(GetRandomValue(0, GetScreenHeight())) };
		float size = static_cast<float>(GetRandomValue(1, 4) / 2);
		Star newStar{start_position, SKYBLUE, size};

		Stars.emplace_back(newStar);
	}
}

void Background::Update(const Player& player)
{
	playerPos = { player.GetPosition().x, (float)player.GetSize().y };
	cornerPos = { 0, (float)player.GetSize().y };
	offset = Vector2Distance(playerPos, cornerPos) * -1;
	for (int i = 0; i < Stars.size(); i++)
	{
		Stars[i].Update(offset / 15);
	}
}

void Background::Render()
{
	for (int i = 0; i < Stars.size(); i++)
	{
		Stars[i].Render();
	}
}