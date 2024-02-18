#pragma once
#include "raylib.h"

class Wall
{
	Vector2 position;
	Rectangle rec;
	Color color;
	int health;
	int radius;
	bool active;

public:
	Wall(Vector2 position);
	Vector2 GetPosition() const;
	float GetRadius() const;
	bool Active() const;
	void Damage(int damage);
	void Render(const Texture2D& texture) const;
	void Update();
};