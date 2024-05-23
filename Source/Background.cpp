#include "Background.h"
#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#include "raymath.h"
#pragma warning(pop)
#include <algorithm>



void Star::Update(float star_offset) noexcept
{
	position.x = start_position.x + narrow_cast<int>(star_offset);
	position.y = start_position.y;

}

void Star::Render() const noexcept
{
	DrawCircle(position.x, position.y, size, color);
}

Background::Background(int star_amount) noexcept
{
	stars.resize(star_amount);
	std::generate(stars.begin(), stars.end(), [this]() noexcept { return Star(); } );
}

void Background::Update(const float _offset) noexcept
{
	for (auto& star : stars)
	{
		star.Update(_offset);
	}
}

void Background::Render() const noexcept
{

	for (auto& star : stars)
	{
		star.Render();
	}
}