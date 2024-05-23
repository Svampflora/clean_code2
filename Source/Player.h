#pragma once

#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)

#include "Utilities.h"
#include "Resources.h"



class Player
{
	Animator animator;
	Vector2 size = { 70.0f, 70.0f };
	Vector2 position = { GetScreenWidthF() * 0.5f, GetScreenHeightF() - size.y};
	float speed = 7;
	float radius = 50;
	int lives = 3;
	int direction = 0;

public:
	Player();
	void Update() noexcept;
	void Render() const noexcept;
	void Hurt(int damage) noexcept;
	void Reset() noexcept;
	Vector2 GetSize() const noexcept;
	Vector2 GetPosition() const noexcept;
	float GetRadius() const noexcept;
	int GetLives() const noexcept;

};