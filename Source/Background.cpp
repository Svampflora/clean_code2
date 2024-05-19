#include "Background.h"
#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#include "raymath.h"
#pragma warning(pop)
#include <algorithm>



Star::Star() noexcept
{
	initPosition={ GetRandomValueF(-150, GetScreenWidth() + 150), GetRandomValueF(0, GetScreenHeight()) };
	position = { 0, 0 };
	size = (GetRandomValueF(1, 4) / 2);
	color = SKYBLUE;
}

void Star::Update(float starOffset) noexcept
{
	position.x = initPosition.x + starOffset;
	position.y = initPosition.y;

}

void Star::Render() const noexcept
{
	DrawCircleF(position.x, position.y, size, color);
}

Background::Background(int starAmount) noexcept
{
	stars.resize(starAmount);
	std::generate(stars.begin(), stars.end(), [this]() noexcept { return Star(); } );
}

void Background::Update(const float _offset) noexcept
{
	for (auto& star : stars)
	{
		star.Update(_offset / 15);
	}
}

void Background::Render() const noexcept
{

	for (auto& star : stars)
	{
		star.Render();
	}
}