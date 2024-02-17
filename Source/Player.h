#pragma once
#include "raylib.h"



class Player //TODO: make regular
{
	Vector2 size = { 70.0f, 70.0f };
	Vector2 position = { GetScreenWidth() * 0.5f, GetScreenHeight() - size.y};
	float speed = 7;
	float radius = 50;
	int lives = 3;
	int direction = 0;

public:
	Player();
	void Update();
	void Render(const Texture2D& texture) const;
	void Hurt(int damage);
	void Reset();
	Vector2 GetSize() const;
	Vector2 GetPosition() const;
	float GetRadius() const;
	int GetLives() const;

};