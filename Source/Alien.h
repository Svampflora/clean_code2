#pragma once
#include "raylib.h"



class Alien
{

	Color color;
	Vector2 position;
	float radius;
	int x;					 //TODO: x, y?
	int y;
	int speed;
	bool moveRight;

public:
	bool active; //TODO: stupid stupid 
	Alien(Vector2 _position);
	Vector2 GetPosition() const;
	float GetRadius() const;
	bool IsActive();
	void SetActive(bool _status);
	void ChangeDirection();
	void Update();
	void Render(const Texture2D& _texture) const;
};