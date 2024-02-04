#pragma once
#include "raylib.h"



struct Projectile  //TODO: make class  C.8: Use class rather than struct if any member is non-public
{
	Vector2 position = { 0,0 };
	Vector2 lineStart = { 0, 0 };
	Vector2 lineEnd = { 0, 0 };
	int speed = 15;
	bool active = true;

public:

	Projectile(Vector2 _position, int _speed);
	void Update();
	void Impact();
	void Render(const Texture2D& texture) const;//TODO: should pass in a const ref for texture
};
