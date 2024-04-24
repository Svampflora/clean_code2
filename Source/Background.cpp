#include "Background.h"
#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#include "raymath.h"
#pragma warning(pop)



Star::Star(Vector2 _start_position, Color _color, float _size) noexcept
{
	initPosition = _start_position;
	position = { 0, 0 };
	color = _color;
	size = _size;
	radius = size;
}

void Star::Update(float starOffset) noexcept
{
	position.x = initPosition.x + starOffset;
	position.y = initPosition.y;

}

void Star::Render() const noexcept
{
	DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), size, color);
}

Background::Background(int starAmount) noexcept
{
	for (int i = 0; i < starAmount; i++)
	{
		const Vector2 start_position{ static_cast<float>(GetRandomValue(-150, GetScreenWidth() + 150)), static_cast<float>(GetRandomValue(0, GetScreenHeight())) };
		const float size = static_cast<float>(GetRandomValue(1, 4) / 2);
		Star newStar{start_position, SKYBLUE, size};

		stars.emplace_back(newStar);
	}
}

void Background::Update(const Player& player) 
{
	playerPos = { player.GetPosition().x, static_cast<float>(player.GetSize().y) };
	cornerPos = { 0, static_cast<float>(player.GetSize().y) };
	offset = Vector2Distance(playerPos, cornerPos) * -1;

	for (auto &star : stars)
	{
		star.Update(offset / 15);
	}
}

void Background::Render() const noexcept
{

	for (auto& star : stars)
	{
		star.Render();
	}
}