#pragma once
#include "Player.h"
#include <vector>

class Star
{
	Vector2 initPosition;
	Vector2 position;
	Color color;
	float size;
	float radius;

public:
	Star(Vector2 _start_position, Color _color, float _size) noexcept;
	void Update(float _starOffset) noexcept;
	void Render() const noexcept;
};

class Background
{
	std::vector<Star> stars;
	Vector2 playerPos{ 0.0f, 0.0f };
	Vector2 cornerPos{ 0.0f,0.0f };
	float offset = 0.0f;

public:

	Background(int starAmount) noexcept;
	void Update(const Player& player) noexcept;
	void Render() const noexcept;

};