#pragma once
#include "raylib.h"



class Alien
{
	Color color;
	Vector2 position;
	float radius;
	int x;
	int y;
	int speed;
	bool active; 

	void ChangeDirection();
public:

	Alien(Vector2 _position);
	Vector2 GetPosition() const;
	float GetRadius() const;
	bool Active() const;
	void SetActive(bool _status);
	void Update();
	void Render(const Texture2D& _texture) const;
};