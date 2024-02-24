#pragma once
#include "raylib.h"
#include <utility>



class Projectile
{
	Vector2 position = { 0,0 };
	Vector2 lineStart = { 0, 0 };
	Vector2 lineEnd = { 0, 0 };
	int speed = 15;
	bool active = true;

public:

	Projectile(Vector2 _position, int _speed);
	std::pair<Vector2, Vector2> GetEdges() const;
	bool Active() const;
	void Update();
	void Impact();
	void Render(const Texture2D& texture) const;
};
