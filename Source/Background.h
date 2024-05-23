#pragma once
#include "Player.h"
#include <vector>


class Star
{
	Color color = SKYBLUE;
	Vector2i start_position = { GetRandomValue(-150, GetScreenWidth() + 150), GetRandomValue(0, GetScreenHeight()) };
	Vector2i position = { 0, 0 };
	float size = (GetRandomValueF(1, 4) / 2);

public:

	void Update(float _starOffset) noexcept;
	void Render() const noexcept;
};

class Background
{
	std::vector<Star> stars;
	Vector2 playerPos{ 0,0 };
	Vector2 cornerPos{ 0,0 };
	float offset = 0;

public:

	Background(int star_amount) noexcept;
	void Update(const float _offset) noexcept;
	void Render() const noexcept;

};