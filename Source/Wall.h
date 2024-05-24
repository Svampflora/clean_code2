#pragma once
#include "raylib.h" //TODO: suppress


class Wall
{
	Vector2 position;
	Rectangle rectangle;
	Color color;
	float radius;
	int health;
	bool active;

public:
	Wall(Vector2 position) noexcept;
	Vector2 GetPosition() const noexcept;
	float GetRadius() const noexcept;
	bool Active() const noexcept;
	void Damage(int damage) noexcept;
	void Render(const Texture2D& texture) const noexcept;
	void Update() noexcept;
};