#pragma once
#include "raylib.h"



class Player
{
	Vector2 size = { 70.0f, 70.0f };
	Vector2 position = { 0, GetScreenHeight() - size.y };
	float speed = 7;
	float radius = 50;
	int lives = 3;
	int direction = 0;

public:
	Player();
	void Update();
	void Render(const Texture2D& texture) const;
	void Hurt(int damage);
	Vector2 GetSize() const;
	Vector2 GetPosition() const;
	float GetRadius() const;
	int GetLives() const;

};