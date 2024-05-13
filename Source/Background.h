#pragma once
#include "Player.h"
#include <vector>


class Star
{
	Vector2 initPosition;
	Vector2 position;
	Color color;
	float size;
	//int radius;

public:
	Star(Vector2 _start_position, Color _color, float _size) noexcept;
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

	Background(int starAmount);
	void Update(const Player& player);
	void Render() const noexcept;

};