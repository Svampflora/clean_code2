#pragma once

#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)


//#include "raylib.h"



class Player
{
	Vector2 size = { 70.0f, 70.0f };
	Vector2 position = { GetScreenWidth() * 0.5f, GetScreenHeight() - size.y};
	float speed = 7;
	float radius = 50;
	int lives = 3;
	int direction = 0;

public:
	Player() noexcept;
	void Update() noexcept;
	void Render(const Texture2D& texture) const noexcept;
	void Hurt(int damage) noexcept;
	void Reset() noexcept;
	Vector2 GetSize() const noexcept;
	Vector2 GetPosition() const noexcept;
	float GetRadius() const noexcept;
	int GetLives() const noexcept;

};