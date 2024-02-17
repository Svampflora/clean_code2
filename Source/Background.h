#pragma once
#include "Player.h"
#include <vector>

class Star  //TODO:make regular
{
	Vector2 initPosition;
	Vector2 position;
	Color color;
	float size;
	float radius;

public:
	Star(Vector2 _start_position, Color _color, float _size);
	void Update(float _starOffset);
	void Render() const;
};

class Background
{
	std::vector<Star> Stars;
	Vector2 playerPos{ 0.0f, 0.0f };
	Vector2 cornerPos{ 0.0f,0.0f };
	float offset = 0.0f;

public:

	Background(int starAmount);
	void Update(const Player& player);
	void Render();  //TODO: const ref

};