#pragma once

#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)

#include "Utilities.h"
#include "Resources.h"

static constexpr int start_lives = 3;

class Player
{
	Animator animator{ std::vector{ "./Assets/Ship1.png"sv,
									"./Assets/Ship2.png"sv,
									"./Assets/Ship3.png"sv } };
	Vector2 size = { 70.0f, 70.0f };
	Vector2 position = { GetScreenWidthF() * 0.5f, GetScreenHeightF() - size.y};
	float speed = 7;
	float radius = 50;
	int lives = start_lives;
	int direction = 0;

public:

	Vector2 GetSize() const noexcept;
	Vector2 GetPosition() const noexcept;
	float GetHeight() const noexcept;
	float GetXPosition() const noexcept;
	float GetRadius() const noexcept;
	int GetLives() const noexcept;
	void Update() noexcept;
	void Render() const noexcept;
	void Hurt(int damage) noexcept;
	void Reset() noexcept;

};