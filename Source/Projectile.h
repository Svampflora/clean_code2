#pragma once
#include "raylib.h"
#include <utility>

constexpr static int projectile_height = 50;

class Projectile
{
	Vector2 position = { 0,0 };
	int speed = 15;
	bool active = true;

public:

	Projectile(Vector2 _position, int _speed) noexcept;
	std::pair<Vector2, Vector2> GetEdges() const noexcept;
	bool Active() const noexcept;
	void Update() noexcept;
	void Impact() noexcept;
	void Render(const Texture2D& texture) const noexcept;
};
