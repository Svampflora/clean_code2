#pragma once
#include "raylib.h"



class Alien //TODO: make regular
{

	Color color;
	Vector2 position;
	float radius;
	int x;					 //TODO: x, y?
	int y;
	int speed;
	bool moveRight;
	bool active; 

public:

	Alien(Vector2 _position);
	Vector2 GetPosition() const;
	float GetRadius() const;
	bool Active() const;
	void SetActive(bool _status);
	void ChangeDirection();
	void Update();
	void Render(const Texture2D& _texture) const;
};