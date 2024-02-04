#pragma once
#include "raylib.h"



struct Alien  //TODO:class  C.8: Use class rather than struct if any member is non-public
{

	Color color = WHITE;
	Vector2 position = { 0, 0 };
	float radius = 30;
	int x = 0;					 //TODO: x, y?
	int y = 0;
	int speed = 2;
	bool active = true;
	bool moveRight = true;

public:
	Vector2 GetPosition() const;
	float GetRadius() const;
	void ChangeDirection();
	void Update();
	void Render(const Texture2D& texture) const; //TODO: should pass in a const ref texture
};